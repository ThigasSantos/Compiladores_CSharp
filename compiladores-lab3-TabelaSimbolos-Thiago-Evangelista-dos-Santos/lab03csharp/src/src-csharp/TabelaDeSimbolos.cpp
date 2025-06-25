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
  for (auto it = pilha_de_tabelas.rbegin(); it != pilha_de_tabelas.rend(); ++it) {
    if (it->count(simbolo)) {
      Simbolo* aux = it->at(simbolo);
      if (aux->tipo_de_simbolo == TipoDeSimbolo::VAR) {
        *aux->valor = *val;
        ultimoValorAtribuido = val;
        return;
      }
    }
  }
}

Valor *TabelaDeSimbolos::buscarVariavel(const string &simbolo) {
//  cerr << "[TabelaDeSimbolos::buscarVariavel] Buscando: " << simbolo << endl;
  for (auto it = pilha_de_tabelas.rbegin(); it != pilha_de_tabelas.rend(); ++it) {
    if (it->count(simbolo)) {
      Simbolo* res = it->at(simbolo);
      if (res->tipo_de_simbolo == TipoDeSimbolo::VAR)
        return res->valor;
    }
  }
  return nullptr;
}

Funcao *TabelaDeSimbolos::buscarFuncao(const string &simbolo) {
  for (auto it = pilha_de_tabelas.rbegin(); it != pilha_de_tabelas.rend(); ++it) {
    if (it->count(simbolo)) {
      Simbolo* res = it->at(simbolo);
      if (res->tipo_de_simbolo == TipoDeSimbolo::FUNC)
        return res->funcao;
    }
  }
  return nullptr;
}

void TabelaDeSimbolos::pushTabela() {
  pilha_de_tabelas.emplace_back();
}

void TabelaDeSimbolos::popTabela() {
  pilha_de_tabelas.pop_back();
}

bool TabelaDeSimbolos::podeAdicionar(const string &simbolo) {
  return pilha_de_tabelas.back().count(simbolo) == 0;
}
