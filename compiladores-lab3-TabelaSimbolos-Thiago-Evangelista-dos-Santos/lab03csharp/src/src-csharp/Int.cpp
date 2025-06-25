#include <iostream>
#include "Valor.h"

Int::Int(const int v) {
  valor = new UValor();
  valor->intVal = v;
}

Int::Int(const string& str) {
  valor = new UValor();
  valor->intVal = atoi(str.c_str());
}

string Int::toString() const {
  return to_string(valor->intVal);
}

void Int::atribuir(Valor *v) {
  if(v->tipo() == tipo()) {
    valor = new UValor();
    valor->intVal = v->valor->intVal;
  }
  else {
    throw runtime_error(tipo() + " não pode receber valor do tipo " + v->tipo());
  }
}

Valor * Int::operator+(const Valor &v) const {
  if(v.tipo() == "float") return new Float(valor->intVal + v.valor->floatVal);
  if(v.tipo() == "int") return new Int(valor->intVal + v.valor->intVal);

  std::cerr << "\n!!!" << tipo() << " + " << v.tipo() << " não é valido" << std::endl;
  throw std::invalid_argument("ArgumentoInvalido");
}

Valor * Int::operator-(const Valor &v) const {
  if(v.tipo() == "float") return new Float(valor->intVal - v.valor->floatVal);
  if(v.tipo() == "int") return new Int(valor->intVal - v.valor->intVal);

  std::cerr << "\n!!!" << tipo() << " - " << v.tipo() << " não é valido" << std::endl;
  throw std::invalid_argument("ArgumentoInvalido");
}

Valor * Int::operator*(const Valor &v) const {
  if(v.tipo() == "float") return new Float(valor->intVal * v.valor->floatVal);
  if(v.tipo() == "int") return new Int(valor->intVal * v.valor->intVal);

  std::cerr << "\n!!!" << tipo() << " * " << v.tipo() << " não é valido" << std::endl;
  throw std::invalid_argument("ArgumentoInvalido");
}


Valor * Int::operator/(const Valor &v) const {
  if(v.tipo() == "float") return new Float(valor->intVal / v.valor->floatVal);
  if(v.tipo() == "int") return new Int(valor->intVal / v.valor->intVal);

  std::cerr << "\n!!!" << tipo() << " / " << v.tipo() << " não é valido" << std::endl;
  throw std::invalid_argument("ArgumentoInvalido");
}


Valor * Int::operator%(const Valor &v) const {
  if(v.tipo() == "int") return new Int(valor->intVal % v.valor->intVal);

  std::cerr << "\n!!!" << tipo() << " / " << v.tipo() << " não é valido" << std::endl;
  throw std::invalid_argument("ArgumentoInvalido");
}


Valor * Int::operator==(const Valor &v) const {
  if(v.tipo() == "int") return new Bool(valor->intVal == v.valor->intVal);

  std::cerr << "\n!!!" << tipo() << " == " << v.tipo() << " não é valido" << std::endl;
  throw std::invalid_argument("ArgumentoInvalido");
}


Valor * Int::operator<(const Valor &v) const {
  if(v.tipo() == "float") return new Bool(valor->intVal < v.valor->floatVal);
  if(v.tipo() == "int") return new Bool(valor->intVal < v.valor->intVal);

  std::cerr << "\n!!!" << tipo() << " < " << v.tipo() << " não é valido" << std::endl;
  throw std::invalid_argument("ArgumentoInvalido");
}
