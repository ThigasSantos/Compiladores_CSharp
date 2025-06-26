#include "ExpressaoSubtracao.h"

#include <iostream>


ExpressaoSubtracao *ExpressaoSubtracao::extrair(No_arv_parse *no) {
  auto *e = new ExpressaoSubtracao();

  e->l_expr = Expressao::extrair(no->filhos[0]);
  e->r_expr = Expressao::extrair(no->filhos[2]);

  return e;
}

Valor *ExpressaoSubtracao::simular_execucao(TabelaDeSimbolos *tabela_de_simbolos) {
  const auto vl = l_expr->simular_execucao(tabela_de_simbolos);
  const auto vr = r_expr->simular_execucao(tabela_de_simbolos);

  return *vl - *vr;
}

Valor *ExpressaoSubtracao::analisar_semantica(TabelaDeSimbolos *tabela_de_simbolos) {
  const auto vl = l_expr->analisar_semantica(tabela_de_simbolos);
  const auto vr = r_expr->analisar_semantica(tabela_de_simbolos);

  return Valor::valor_para_analise((*vl - *vr)->tipo());
}

void ExpressaoSubtracao::debug(int t) {
  l_expr->debug(t);
  std::cerr << " - ";
  r_expr->debug(t);
}

