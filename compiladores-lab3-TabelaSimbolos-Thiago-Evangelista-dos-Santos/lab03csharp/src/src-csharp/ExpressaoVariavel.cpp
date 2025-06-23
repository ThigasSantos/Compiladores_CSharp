#include "ExpressaoVariavel.h"

#include <iostream>
#include <ostream>


ExpressaoVariavel *ExpressaoVariavel::extrair(No_arv_parse *no) {
  auto* e = new ExpressaoVariavel();

  e->id = ID::extrai_ID(no->filhos[0]);

  return e;
}

Valor* ExpressaoVariavel::simular_execucao(TabelaDeSimbolos *tabela_de_simbolos) {
  Valor * v = tabela_de_simbolos->buscarVariavel(id->nome);

  if (v == nullptr) {
    cerr << "Variavel " << id->nome << " Não declarada" << endl;
    throw std::runtime_error("VariavelNaoDeclarado");
  }

  if (v->valor == nullptr) {
    cerr << "Variavel " << id->nome << " Não Inicializada" << endl;
    throw std::runtime_error("VariavelNaoInicializada");
  }

  return v;
}


void ExpressaoVariavel::debug(int t) {
  std::cerr << "Var(" << id->nome << ")";
}
