#include <iostream>

#include "ExpressaoBooleana.h"

ExpressaoBooleana *ExpressaoBooleana::extrair(No_arv_parse *no) {
  auto *e = new ExpressaoBooleana();
  e->valor = new Bool(no->filhos[0]->dado_extra);

  return e;
}

Valor *ExpressaoBooleana::simular_execucao(TabelaDeSimbolos *tabela_de_simbolos) {
  return valor;
}

Valor *ExpressaoBooleana::analisar_semantica(TabelaDeSimbolos *tabela_de_simbolos) {
  return Valor::valor_para_analise(valor->tipo());
}


void ExpressaoBooleana::debug(int t) {
  cerr << "Bool(" << *valor << ")";
}


