#ifndef VALOR_H
#define VALOR_H
#include "Tipo.h"

union UValor {
  int intVal;
  float floatVal;
  bool boolVal;
};

class Valor {
public:
  UValor* valor = nullptr;

  static Valor* of(const string & tipo);
  static Valor* valor_para_analise(const string & tipo);
  virtual ~Valor() = default;
  Valor() = default;
  //
  bool isNumber() const;
  bool isBool() const;
  //
  virtual string tipo() const { return "void"; }
  virtual string toString() const;
  //
  virtual void atribuir(Valor* valor);
  virtual Valor* operator+(const Valor& v) const;
  virtual Valor* operator-(const Valor& v) const;
  virtual Valor* operator*(const Valor& v) const;
  virtual Valor* operator/(const Valor& v) const;
  virtual Valor* operator%(const Valor& v) const;
  virtual Valor* operator==(const Valor& v) const;
  virtual Valor* operator<(const Valor& v) const;
  virtual Valor* operator&&(const Valor& v) const;
  virtual Valor* operator||(const Valor& v) const;
  virtual Valor* operator!() const;
  friend ostream &operator<<(ostream &os, const Valor &v);
  friend ostream &operator<<(ostream &os, const Valor*v);
};



class Float final : public Valor {
public:
  Float() = default;
  explicit Float(float v);
  explicit Float(int v);
  explicit Float(const string& str);

  string toString() const override;
  string tipo() const override { return "float"; }

  void atribuir(Valor* valor) override;
  Valor * operator+(const Valor &v) const override;
  Valor* operator-(const Valor& v) const override;
  Valor* operator*(const Valor& v) const override;
  Valor* operator/(const Valor& v) const override;
  Valor* operator==(const Valor& v) const override;
  Valor* operator<(const Valor& v) const override;

};



class Int final : public Valor {
public:
  Int() = default;
  explicit Int(int v);
  explicit Int(const string& str);

  string toString() const override;
  string tipo() const override{ return "int"; }

  void atribuir(Valor *valor) override;
  Valor* operator+(const Valor &v) const override;
  Valor* operator-(const Valor& v) const override;
  Valor* operator*(const Valor& v) const override;
  Valor* operator/(const Valor& v) const override;
  Valor* operator==(const Valor& v) const override;
  Valor* operator<(const Valor& v) const override;
  Valor* operator%(const Valor& v) const override;
};

class Bool final : public Valor {
public:
  string toString() const override;
  string tipo() const override { return "bool"; }

  Bool() = default;
  explicit Bool(bool v);
  explicit Bool(const string& str);

  void atribuir(Valor *valor) override;
  Valor* operator==(const Valor &v) const override;
  Valor* operator&&(const Valor &v) const override;
  Valor* operator||(const Valor &v) const override;
  Valor* operator!() const override;
};

#endif //VALOR_H
