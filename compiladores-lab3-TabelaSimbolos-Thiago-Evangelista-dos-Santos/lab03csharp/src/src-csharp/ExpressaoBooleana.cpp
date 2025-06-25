#include "ExpressaoBooleana.h"
#include "Valor.h"
#include <iostream>
#include <ostream>

using namespace std;

ExpressaoBooleana *ExpressaoBooleana::extrair(No_arv_parse *no) {
  auto *e = new ExpressaoBooleana();
  auto no_bool = no->filhos[0];

  string token, lexema;

  // CASO 1: nó terminal direto
  if (no_bool->regra == -1) {
    token = no_bool->simb;
    lexema = no_bool->dado_extra;
  }
  // CASO 2: terminal está dentro do filho
  else if (!no_bool->filhos.empty()) {
    token = no_bool->filhos[0]->simb;
    lexema = no_bool->filhos[0]->dado_extra;
  } else {
    cerr << "[ExpressaoBooleana::extrair] ERRO: nó sem filhos e não-terminal." << endl;
    delete e;
    return nullptr;
  }

  if (token == "TRUE") {
    e->valor = new Bool(true);
  } else if (token == "FALSE") {
    e->valor = new Bool(false);
  } else {
    cerr << "[ExpressaoBooleana::extrair] Token inesperado: " << token << endl;
    delete e;
    return nullptr;
  }

  return e;
}

Valor *ExpressaoBooleana::simular_execucao(TabelaDeSimbolos *tabela_de_simbolos) {
  return valor;
}

Valor *ExpressaoBooleana::analisar_semantica(TabelaDeSimbolos *tabela_de_simbolos) {
  return Valor::valor_para_analise(valor->tipo());
}

void ExpressaoBooleana::debug(int t) {
  cerr << string(t, ' ') << "[Bool] ";
  if (valor)
    cerr << valor->tipo() << "(" << valor->toString() << ")";
  else
    cerr << "<valor nulo>";
  cerr << endl;
}
