#include "ExpressaoVariavel.h"

#include <iostream>
#include <ostream>


ExpressaoVariavel *ExpressaoVariavel::extrair(No_arv_parse *no) {
  auto* e = new ExpressaoVariavel();

  No_arv_parse* node = no;

  // Desce até o ID_RULE se necessário
  if (no->simb == "PRIMARY" && !no->filhos.empty()) {
    node = no->filhos[0]; // ID_RULE
  }

  if (node->simb == "ID_RULE" && !node->filhos.empty()) {
    node = node->filhos[0]; // ID
  }

  if (node->simb != "ID" || node->dado_extra.empty()) {
    std::cerr << "[ExpressaoVariavel::extrair] ERRO: id->nome vazio" << std::endl;
    return e;
  }

  e->id = ID::extrai_ID(node);
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

Valor* ExpressaoVariavel::analisar_semantica(TabelaDeSimbolos *tabela_de_simbolos) {
  Valor* v = tabela_de_simbolos->buscarVariavel(id->nome);

  if (v == nullptr) {
    std::cerr << "[ExpressaoVariavel::analisar_semantica] Variável não declarada: " << id->nome << std::endl;
    throw std::runtime_error("VariavelNaoDeclarado");
  }

  // Retorna uma cópia  do valor apenas para verificação de tipo
  return Valor::valor_para_analise(v->tipo());
}


void ExpressaoVariavel::debug(int t) {
  std::cerr << "Var(" << id->nome << ")";
}
