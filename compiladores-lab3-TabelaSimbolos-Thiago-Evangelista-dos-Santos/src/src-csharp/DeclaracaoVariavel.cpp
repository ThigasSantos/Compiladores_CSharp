#include "DeclaracaoVariavel.h"
#include <iostream>

DeclaracaoVariavel* DeclaracaoVariavel::extrair(No_arv_parse* no) {
  if (!no) return nullptr;

  auto* res = new DeclaracaoVariavel();
  int regra = no->regra;
  
  // 40: FIELD_DECL -> TYPE ID SEMI
  // 41: FIELD_DECL -> TYPE ID ASSIGN EXPRESSION SEMI
  if (regra == 13 || regra == 14) {
    res->var = Variavel::extrair(no);
    if (regra == 14 && no->filhos.size() >= 4) {
      res->expr = Expressao::extrair(no->filhos[3]); // expressão após ASSIGN
    }
    return res;
  }

  std::cerr << "[DeclaracaoVariavel::extrair] Regra inesperada: " << regra << std::endl;
  delete res;
  return nullptr;
}

Valor* DeclaracaoVariavel::simular_execucao(TabelaDeSimbolos* tabela_de_simbolos) {
  if (!var || !var->nome || !var->tipo) return nullptr;

  Valor* v = Valor::of(var->tipo->nome);
  if (expr) v->atribuir(expr->simular_execucao(tabela_de_simbolos));

  tabela_de_simbolos->adicionarSimbolo(var->nome->nome, v);
  return nullptr;
}

vector<Valor*> DeclaracaoVariavel::analisar_semantica(TabelaDeSimbolos* tabela_de_simbolos) {
  if (!var || !var->nome || !var->tipo) return {};

  if (!tabela_de_simbolos->podeAdicionar(var->nome->nome)) {
    throw std::runtime_error("Identificador \"" + var->nome->nome + "\" já declarado nesse escopo");
  }

  Valor* v = Valor::of(var->tipo->nome);
  if (expr) v->atribuir(expr->analisar_semantica(tabela_de_simbolos));

  tabela_de_simbolos->adicionarSimbolo(var->nome->nome, v);
  return {};
}

void DeclaracaoVariavel::debug(int t) {
  std::cerr << std::string(t, ' ') << "DeclVar: [";
  if (var && var->nome) std::cerr << var->nome->nome;
  if (var && var->tipo) std::cerr << ":" << var->tipo->nome;
  std::cerr << "]";
  if (expr) {
    std::cerr << " = ";
    expr->debug(t);
  } else {
    std::cerr << std::endl;
  }
}
