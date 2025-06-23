#ifndef SIMBOLO_H
#define SIMBOLO_H
#include "Valor.h"

class Funcao;

enum class TipoDeSimbolo { FUNC, VAR };

class Simbolo {
public:
  Simbolo() = default;
  static Simbolo* Var(const string& nome, Valor *valor);
  static Simbolo* Func(const string& nome, Funcao *funcao);
  string nome_simbolo{};
  TipoDeSimbolo tipo_de_simbolo{};
  Valor *valor{};
  Funcao *funcao{};
};


#endif //SIMBOLO_H
