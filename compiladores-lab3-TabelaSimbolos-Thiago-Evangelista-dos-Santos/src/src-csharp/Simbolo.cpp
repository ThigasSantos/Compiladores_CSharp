#include "Simbolo.h"


Simbolo *Simbolo::Var(const string& nome, Valor* valor) {
  auto * s = new Simbolo();

  s->nome_simbolo = nome;
  s->valor = valor;
  s->tipo_de_simbolo = TipoDeSimbolo::VAR;

  return s;
}


Simbolo *Simbolo::Func(const string& nome, Funcao *funcao) {
  auto * s = new Simbolo();

  s->nome_simbolo = nome;
  s->funcao = funcao;
  s->tipo_de_simbolo = TipoDeSimbolo::FUNC;

  return s;
}