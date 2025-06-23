#ifndef TABELADESIMBOLOS_H
#define TABELADESIMBOLOS_H

#include <map>

#include "Simbolo.h"
#include "Valor.h"


class TabelaDeSimbolos {
public:
  Valor* ultimoValorAtribuido = new Valor();
  vector<map<string, Simbolo*>> pilha_de_tabelas;

  TabelaDeSimbolos();

  Valor* buscarVariavel(const string& simbolo);
  Funcao* buscarFuncao(const string& simbolo);
  void adicionarSimbolo(const string& simbolo, Valor *val);
  void adicionarSimbolo(const string& simbolo, Funcao *val);
  bool podeAdicionar(const string& simbolo);
  void atualizarSimbolo(const string& simbolo, Valor *val);
  void pushTabela();
  void popTabela();
};



#endif
