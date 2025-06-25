#include "ExpressaoNumero.h"
#include "Valor.h"
#include <iostream>
#include <ostream>

using namespace std;

ExpressaoNumero *ExpressaoNumero::extrair(No_arv_parse *no) {
  auto *e = new ExpressaoNumero();
  auto no_number = no->filhos[0];
  bool signal = false;

  if (no->regra == 65) {  // número negativo
    signal = true;
    no_number = no->filhos[1];
  }

  string token, lexema;

  // CASO 1: no_number é um terminal
  if (no_number->regra == -1) {
    token = no_number->simb;
    lexema = no_number->dado_extra;
  }
  // CASO 2: no_number tem filhos e o terminal está dentro
  else if (!no_number->filhos.empty()) {
    token = no_number->filhos[0]->simb;
    lexema = no_number->filhos[0]->dado_extra;
  }
  else {
    cerr << "[ExpressaoNumero::extrair] ERRO: nó sem filhos e não-terminal." << endl;
    delete e;
    return nullptr;
  }

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
