#include "TabelaDeSimbolos.h"

#include <iostream>


TabelaDeSimbolos::TabelaDeSimbolos() {
  pilha_de_tabelas = vector<map<string, Simbolo*>>();
  pushTabela();
}

void TabelaDeSimbolos::adicionarSimbolo(const string& nome, Valor *val) {
  if (!podeAdicionar(nome)) return;
  ultimoValorAtribuido = val;
  pilha_de_tabelas.back()[nome] = Simbolo::Var(nome, val);
}

void TabelaDeSimbolos::adicionarSimbolo(const string& nome, Funcao *val) {
  if (!podeAdicionar(nome)) return;
  pilha_de_tabelas.back()[nome] = Simbolo::Func(nome, val);
}

void TabelaDeSimbolos::atualizarSimbolo(const string &simbolo, Valor *val) {
  Simbolo *aux = nullptr;

  for(auto tabela : pilha_de_tabelas)
    aux = tabela[simbolo] ? tabela[simbolo] : aux;

  if(!aux || !(aux->tipo_de_simbolo == TipoDeSimbolo::VAR)) return;
  *aux->valor = *val;
  ultimoValorAtribuido = val;
}

Valor *TabelaDeSimbolos::buscarVariavel(const string &simbolo) {
  Simbolo *res = nullptr;

  for(auto tabela : pilha_de_tabelas)
    res = tabela[simbolo] ? tabela[simbolo] : res;

  if (res && res->tipo_de_simbolo == TipoDeSimbolo::VAR) return res->valor;
  return nullptr;
}

Funcao *TabelaDeSimbolos::buscarFuncao(const string &simbolo) {
  Simbolo *res = nullptr;

  for(auto tabela : pilha_de_tabelas)
    res = tabela[simbolo] ? tabela[simbolo] : res;

  if (res && res->tipo_de_simbolo == TipoDeSimbolo::FUNC) return res->funcao;
  return nullptr;
}

void TabelaDeSimbolos::pushTabela() {
  pilha_de_tabelas.emplace_back();
}

void TabelaDeSimbolos::popTabela() {
  pilha_de_tabelas.pop_back();
}

bool TabelaDeSimbolos::podeAdicionar(const string &simbolo) {
  return pilha_de_tabelas.back()[simbolo] == nullptr;
}

