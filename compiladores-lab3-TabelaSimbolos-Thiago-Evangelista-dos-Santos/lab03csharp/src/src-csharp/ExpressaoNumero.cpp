#include "ExpressaoNumero.h"
#include "Valor.h"
#include <iostream>
#include <ostream>

using namespace std;

ExpressaoNumero *ExpressaoNumero::extrair(No_arv_parse *no) {
  auto *e = new ExpressaoNumero();
  auto no_number = no->filhos[0];
  bool signal = false;

  if (no->regra == 66) {
    signal = true;
    no_number = no->filhos[1];
  }

  // Verificação segura
  if (no_number->filhos.empty()) {
    cerr << "[ExpressaoNumero::extrair] ERRO: no_number não tem filhos." << endl;
    delete e;
    return nullptr;
  }

  cerr << "[ExpressaoNumero::extrair] Regra: " << no->regra
     << " | no_number->filhos.size(): " << no_number->filhos.size() << endl;


  const string &token = no_number->filhos[0]->simb;
  const string &lexema = no_number->filhos[0]->dado_extra;

  if (token == "LITERAL_INTEGER") {
    int v = stoi(lexema);
    if (signal) v *= -1;
    e->valor = new Int(v);
  } else if (token == "REAL_LITERAL") {
    float v = stof(lexema);
    if (signal) v *= -1.0f;
    e->valor = new Float(v);
  } else {
    cerr << "[ExpressaoNumero::extrair] Token inesperado: " << token << endl;
    delete e;
    return nullptr;
  }

  return e;
}

Valor *ExpressaoNumero::simular_execucao(TabelaDeSimbolos *tabela_de_simbolos) {
  return valor;
}

Valor *ExpressaoNumero::analisar_semantica(TabelaDeSimbolos *tabela_de_simbolos) {
  return Valor::valor_para_analise(valor->tipo());
}

void ExpressaoNumero::debug(int t) {
  cerr << string(t, ' ') << "[Numero] ";
  if (valor)
    cerr << valor->tipo() << "(" << valor->toString() << ")";
  else
    cerr << "<valor nulo>";
  cerr << endl;
}
