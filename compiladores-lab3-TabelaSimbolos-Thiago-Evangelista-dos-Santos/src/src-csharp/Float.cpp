#include <iomanip>
#include <iostream>
#include <sstream>

#include "Valor.h"

Float::Float(const float v) {
  valor = new UValor();
  valor->floatVal = v;
}

Float::Float(const int v) {
  valor = new UValor();
  valor->floatVal = static_cast<float>(v);
}


Float::Float(const string& str) {
  valor = new UValor();
  valor->floatVal = static_cast<float>(atof(str.c_str()));
}


string Float::toString() const {
  std::ostringstream oss;
  oss << std::fixed << std::setprecision(2) << valor->floatVal;
  return oss.str();
}

void Float::atribuir(Valor *v) {
  valor = new UValor();
  if(v->tipo() == tipo()) valor->floatVal = v->valor->floatVal;
  else if(v->tipo() == "int") valor->floatVal = v->valor->intVal;
  else {
    throw runtime_error(tipo() + " não pode receber valor do tipo " + v->tipo());
  }
}


Valor* Float::operator+(const Valor &v) const {
  if(v.tipo() == "float") return new Float(valor->floatVal + v.valor->floatVal);
  if(v.tipo() == "int") return new Float(valor->floatVal + static_cast<float>(v.valor->intVal));

  std::cerr << "\n!!!" << tipo() << " + " << v.tipo() << " não é valido" << std::endl;
  throw std::invalid_argument("ArgumentoInvalido");
}


Valor* Float::operator-(const Valor &v) const {
  if(v.tipo() == "float") return new Float(valor->floatVal - v.valor->floatVal);
  if(v.tipo() == "int") return new Float(valor->floatVal - static_cast<float>(v.valor->intVal));

  std::cerr << "\n!!!" << tipo() << " - " << v.tipo() << " não é valido" << std::endl;
  throw std::invalid_argument("ArgumentoInvalido");
}


Valor* Float::operator*(const Valor &v) const {
  if(v.tipo() == "float") return new Float(valor->floatVal * v.valor->floatVal);
  if(v.tipo() == "int") return new Float(valor->floatVal * static_cast<float>(v.valor->intVal));

  std::cerr << "\n!!!" << tipo() << " * " << v.tipo() << " não é valido" << std::endl;
  throw std::invalid_argument("ArgumentoInvalido");
}


Valor* Float::operator/(const Valor &v) const {
  if(v.tipo() == "float") return new Float(valor->floatVal / v.valor->floatVal);
  if(v.tipo() == "int") return new Float(valor->floatVal / v.valor->intVal);

  std::cerr << "\n!!!" << tipo() << " / " << v.tipo() << " não é valido" << std::endl;
  throw std::invalid_argument("ArgumentoInvalido");
}


Valor* Float::operator==(const Valor &v) const {
  if(v.tipo() == "float") return new Bool(valor->floatVal == v.valor->floatVal);

  std::cerr << "\n!!!" << tipo() << " == " << v.tipo() << " não é valido" << std::endl;
  throw std::invalid_argument("ArgumentoInvalido");
}

Valor* Float::operator<(const Valor &v) const {
  if(v.tipo() == "float") return new Bool(valor->floatVal < v.valor->floatVal);
  if(v.tipo() == "int") return new Bool(valor->floatVal < static_cast<float>(v.valor->intVal));

  std::cerr << "\n!!!" << tipo() << " < " << v.tipo() << " não é valido" << std::endl;
  throw std::invalid_argument("ArgumentoInvalido");
}
