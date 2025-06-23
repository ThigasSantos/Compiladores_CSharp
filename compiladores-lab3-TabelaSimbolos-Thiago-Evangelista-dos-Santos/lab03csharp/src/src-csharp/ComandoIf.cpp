#include "ComandoIf.h"

#include "../debug-util.hpp"

ComandoIf *ComandoIf::extrair(No_arv_parse *no) {
  auto * s = new ComandoIf();

  s->expr = Expressao::extrair(no->filhos[1]->filhos[0]);
  s->if_block = CodeBlock::extrair(no->filhos[2]);

  if (no->regra == 13) {
    s->else_block = CodeBlock::extrair(no->filhos[3]->filhos[1]);
  }

  return s;
}

Valor * ComandoIf::simular_execucao(TabelaDeSimbolos *tabela_de_simbolos) {
  auto *res = expr->simular_execucao(tabela_de_simbolos);

  if(res->valor->boolVal) return if_block->simular_execucao(tabela_de_simbolos);
  if(else_block != nullptr) return else_block->simular_execucao(tabela_de_simbolos);

  return nullptr;
}

vector<Valor*> ComandoIf::analisar_semantica(TabelaDeSimbolos *tabela_de_simbolos) {

  const auto *valor_condicao = expr->analisar_semantica(tabela_de_simbolos);

  if(!valor_condicao->isBool()) {
    cerr << "Condição If precisa ser do tipo Bool" << endl;
    throw std::runtime_error("TypeMismatch");
  }

  auto res = if_block->analisar_semantica(tabela_de_simbolos);

  if(else_block != nullptr) {
    auto valores_else = else_block->analisar_semantica(tabela_de_simbolos);
    res.insert(res.end(), valores_else.begin(), valores_else.end());
  }

  return res;
}

void ComandoIf::debug(int t) {
  cerr << "IF [cond=("; expr->debug(t); cerr << ")] ";
  if_block->debug(t);
  if(else_block != nullptr) {
    cerr << endl; tab2(t); cerr << "ELSE ";
    else_block->debug(t);
  }
}

