#include "ExpressaoSoma.h"

#include <iostream>
#include <ostream>


ExpressaoSoma *ExpressaoSoma::extrair(No_arv_parse *no) {
  auto *e = new ExpressaoSoma();

  e->l_expr = Expressao::extrair(no->filhos[0]);
  e->r_expr = Expressao::extrair(no->filhos[2]);

  return e;
}

Valor* ExpressaoSoma::simular_execucao(TabelaDeSimbolos *tabela_de_simbolos) {
  const auto vl = l_expr->simular_execucao(tabela_de_simbolos);
  const auto vr = r_expr->simular_execucao(tabela_de_simbolos);

  return *vl + *vr;
}

Valor *ExpressaoSoma::analisar_semantica(TabelaDeSimbolos *tabela_de_simbolos) {
  const auto vl = l_expr->analisar_semantica(tabela_de_simbolos);
  const auto vr = r_expr->analisar_semantica(tabela_de_simbolos);

  return Valor::valor_para_analise((*vl + *vr)->tipo());
}


void ExpressaoSoma::debug(int t) {
  l_expr->debug(t);
  std::cerr << " + ";
  r_expr->debug(t);
}
