#include "ExpressaoIgualdade.h"

#include <iostream>
#include <stdexcept>


ExpressaoIgualdade *ExpressaoIgualdade::extrair(No_arv_parse *no) {
  auto *e = new ExpressaoIgualdade();

  e->l_expr = Expressao::extrair(no->filhos[0]);
  e->r_expr = Expressao::extrair(no->filhos[2]);

  return e;
}

Valor *ExpressaoIgualdade::simular_execucao(TabelaDeSimbolos *tabela_de_simbolos) {
  const auto vl = l_expr->simular_execucao(tabela_de_simbolos);
  const auto vr = r_expr->simular_execucao(tabela_de_simbolos);

  return *vl == *vr;
}

Valor *ExpressaoIgualdade::analisar_semantica(TabelaDeSimbolos *tabela_de_simbolos) {
  const auto vl = l_expr->analisar_semantica(tabela_de_simbolos);
  const auto vr = r_expr->analisar_semantica(tabela_de_simbolos);

  return Valor::valor_para_analise((*vl == *vr)->tipo());
}

void ExpressaoIgualdade::debug(int t) {
  l_expr->debug(t);
  std::cerr << " == ";
  r_expr->debug(t);
}
