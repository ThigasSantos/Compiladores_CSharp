#include <iostream>
#include <ostream>

#include "ExpressaoAtribuicao.h"

ExpressaoAtribuicao *ExpressaoAtribuicao::extrair(No_arv_parse *no) {
  auto *e = new ExpressaoAtribuicao();

  e->id = ID::extrai_ID(no->filhos[0]->filhos[0]);
  e->r_expr = Expressao::extrair(no->filhos[2]);

  return e;
}

Valor * ExpressaoAtribuicao::simular_execucao(TabelaDeSimbolos *tabela_de_simbolos) {
  Valor * v = tabela_de_simbolos->buscarVariavel(id->nome);
  auto* v2 = r_expr->simular_execucao(tabela_de_simbolos);

  v->atribuir(v2);
  tabela_de_simbolos->atualizarSimbolo(id->nome, v);

  return nullptr;
}

Valor * ExpressaoAtribuicao::analisar_semantica(TabelaDeSimbolos *tabela_de_simbolos) {
  Valor * v = tabela_de_simbolos->buscarVariavel(id->nome);
  auto* v2 = r_expr->analisar_semantica(tabela_de_simbolos);

  if (v == nullptr) {
    cerr << "Variavel " << id->nome << " Não declarada" << endl;
    throw std::runtime_error("InvalidValue");
  }

  v->atribuir(Valor::valor_para_analise(v2->tipo()));
  tabela_de_simbolos->atualizarSimbolo(id->nome, v);

  return nullptr;
}

void ExpressaoAtribuicao::debug(int t) {
  std::cerr << "Atribuir [" << id->nome << "] = ";
  r_expr->debug(t);
}
