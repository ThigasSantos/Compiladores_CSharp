#include "Valor.h"
#include <iomanip>
#include <iostream>

using namespace std;

Valor *Valor::of(const string &tipo) {
  if (tipo == "int") return new Int();
  if (tipo == "float") return new Float();
  if (tipo == "bool") return new Bool();

  throw runtime_error("Tipo " + tipo + " não existe");
}

Valor *Valor::valor_para_analise(const string &tipo) {
  if (tipo == "int") return new Int(1);
  if (tipo == "float") return new Float(1.0f);
  if (tipo == "bool") return new Bool(true);

  throw runtime_error("Tipo " + tipo + " não existe");
}

void Valor::atribuir(Valor *v) {
  cerr << tipo() << " não pode receber valor do tipo " << v->tipo() << endl;
  throw runtime_error("Valor::atribuicao");
}

Valor *Valor::operator+(const Valor& v) const {
  cerr << tipo() << " não possui a operação '+'" << endl;
  throw runtime_error("Valor::operator");
}

Valor *Valor::operator-(const Valor& v) const {
  cerr << tipo() << " não possui a operação '-'" << endl;
  throw runtime_error("Valor::operator");
}

Valor *Valor::operator*(const Valor& v) const {
  cerr << tipo() << " não possui a operação '*'" << endl;
  throw runtime_error("Valor::operator");
}

Valor *Valor::operator/(const Valor& v) const {
  cerr << tipo() << " não possui a operação '/'" << endl;
  throw runtime_error("Valor::operator");
}

Valor *Valor::operator%(const Valor& v) const {
  cerr << tipo() << " não possui a operação '%'" << endl;
  throw runtime_error("Valor::operator");
}

Valor *Valor::operator==(const Valor &v) const {
  cerr << tipo() << " não possui a operação '=='" << endl;
  throw runtime_error("Valor::operator");
}

Valor *Valor::operator<(const Valor &v) const {
  cerr << tipo() << " não possui a operação '<'" << endl;
  throw runtime_error("Valor::operator");
}

Valor *Valor::operator&&(const Valor &v) const {
  cerr << tipo() << " não possui a operação '&&'" << endl;
  throw runtime_error("Valor::operator");
}

Valor *Valor::operator||(const Valor &v) const {
  cerr << tipo() << " não possui a operação '||'" << endl;
  throw runtime_error("Valor::operator");
}

Valor *Valor::operator!() const {
  cerr << tipo() << " não possui a operação '!'" << endl;
  throw runtime_error("Valor::operator");
}

ostream &operator<<(ostream &os, const Valor& v) {
  os << v.toString();
  return os;
}

ostream &operator<<(ostream &os, const Valor* v) {
  return operator<<(os, *v);
}

bool Valor::isNumber() const {
  return tipo() == "int" || tipo() == "float";
}

bool Valor::isBool() const {
  return tipo() == "bool";
}

string Valor::toString() const {
  return "ValorGenerico";
}
