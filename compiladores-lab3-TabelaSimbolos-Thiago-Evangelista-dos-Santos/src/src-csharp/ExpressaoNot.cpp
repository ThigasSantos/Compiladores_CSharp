#include "ExpressaoNot.h"
#include <iostream>


ExpressaoNot *ExpressaoNot::extrair(No_arv_parse *no) {
  auto *e = new ExpressaoNot();

  e->r_expr = Expressao::extrair(no->filhos[1]);

  return e;
}

Valor *ExpressaoNot::simular_execucao(TabelaDeSimbolos *tabela_de_simbolos) {
  const auto vr = r_expr->simular_execucao(tabela_de_simbolos);

  return !*vr;
}

Valor *ExpressaoNot::analisar_semantica(TabelaDeSimbolos *tabela_de_simbolos) {
  const auto vr = r_expr->analisar_semantica(tabela_de_simbolos);

  return Valor::valor_para_analise((! *vr)->tipo());
}



void ExpressaoNot::debug(int t) {
  std::cerr << " ! [ ";
  r_expr->debug(t);
  std::cerr << " ]";
}
