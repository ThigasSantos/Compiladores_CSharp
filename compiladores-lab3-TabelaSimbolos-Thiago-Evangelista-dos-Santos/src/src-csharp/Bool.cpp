#include <iostream>

#include "Valor.h"

Bool::Bool(const bool v) {
  valor = new UValor();
  valor->intVal = v;
}

Bool::Bool(const string& str) {
  valor = new UValor();
  valor->boolVal = str == "true";
}

string Bool::toString() const {
  return valor->boolVal ? "true" : "false";
}

void Bool::atribuir(Valor *v) {
  valor = new UValor();
  if(v->isBool()) valor->boolVal = v->valor->boolVal;
  else {
    throw runtime_error(tipo() + " não pode receber valor do tipo " + v->tipo());
  }
}

Valor *Bool::operator==(const Valor &v) const {
if(v.tipo() == "bool") return new Bool(valor->boolVal == v.valor->boolVal);

  std::cerr << "\n!!!" << tipo() << " == " << v.tipo() << " Não é uma Operação Valida" << std::endl;
  throw std::invalid_argument("ArgumentoInvalido");
}

Valor *Bool::operator&&(const Valor &v) const {
  if(v.tipo() == "bool") return new Bool(valor->boolVal && v.valor->boolVal);

  std::cerr << "\n!!!" << tipo() << " && " << v.tipo() << " Não é uma Operação Valida" << std::endl;
  throw std::invalid_argument("ArgumentoInvalido");
}

Valor *Bool::operator||(const Valor &v) const {
  if(v.tipo() == "bool") return new Bool(valor->boolVal || v.valor->boolVal);

  std::cerr << "\n!!!" << tipo() << " || " << v.tipo() << " Não é uma Operação Valida" << std::endl;
  throw std::invalid_argument("ArgumentoInvalido");
}

Valor *Bool::operator!() const{
  return new Bool(!valor->boolVal);
}
