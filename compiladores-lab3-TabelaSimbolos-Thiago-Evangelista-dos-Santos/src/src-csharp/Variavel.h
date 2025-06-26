#ifndef VARIAVEL_H
#define VARIAVEL_H
#include "ID.h"
#include "Tipo.h"


class Variavel {
public:
  Variavel();
  Tipo* tipo;
  ID* nome;

  static vector<Variavel *> extrair_parametros(No_arv_parse *no);
  static Variavel *extrair(No_arv_parse *no);
  void debug_com_tab(int i);
};


#endif
