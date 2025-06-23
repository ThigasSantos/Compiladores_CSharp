#include "ExpressaoOu.h"

#include <iostream>

ExpressaoOu *ExpressaoOu::extrair(No_arv_parse *no) {
  auto *e = new ExpressaoOu();

  e->l_expr = Expressao::extrair(no->filhos[0]);
  e->r_expr = Expressao::extrair(no->filhos[2]);

  return e;
}

Valor *ExpressaoOu::simular_execucao(TabelaDeSimbolos *tabela_de_simbolos) {
  const auto vl = l_expr->simular_execucao(tabela_de_simbolos);
  const auto vr = r_expr->simular_execucao(tabela_de_simbolos);

  return *vl || *vr;
}

Valor *ExpressaoOu::analisar_semantica(TabelaDeSimbolos *tabela_de_simbolos) {
  const auto vl = l_expr->analisar_semantica(tabela_de_simbolos);
  const auto vr = r_expr->analisar_semantica(tabela_de_simbolos);

  return Valor::valor_para_analise((*vl || *vr)->tipo());
}

void ExpressaoOu::debug(int t) {
  l_expr->debug(t);
  std::cerr << " || ";
  r_expr->debug(t);
}
