#include "ComandoIf.h"

#include "../debug-util.hpp"

ComandoIf *ComandoIf::extrair(No_arv_parse *no) {
  if (!no || no->regra != 29 || no->filhos.size() != 6) {
    cerr << "[ComandoIf::extrair] ERRO: Regra inválida ou estrutura inesperada. Regra=" 
         << (no ? no->regra : -1) << endl;
    return nullptr;
  }

  auto *s = new ComandoIf();

  // filhos: IF, LPAREN, EXPRESSION, RPAREN, STATEMENT, ELSE_STATEMENT
  s->expr = Expressao::extrair(no->filhos[2]);
  s->if_block = Comando::extrair(no->filhos[4]);

  No_arv_parse *else_stmt = no->filhos[5];
  if (else_stmt->regra == 36 && else_stmt->filhos.size() == 2) {
    s->else_block = Comando::extrair(else_stmt->filhos[1]); // STATEMENT
  } else if (else_stmt->regra == 37) {
    s->else_block = nullptr; // Vazio
  } else {
    cerr << "[ComandoIf::extrair] ERRO: ELSE_STATEMENT inesperado. Regra=" << else_stmt->regra << endl;
    delete s;
    return nullptr;
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

