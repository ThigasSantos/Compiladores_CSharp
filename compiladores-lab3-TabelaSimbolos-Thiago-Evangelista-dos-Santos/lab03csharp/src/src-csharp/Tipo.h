#ifndef TIPO_H
#define TIPO_H
#include "ID.h"


class Tipo {
public:
  string nome;
  Tipo();

  static Tipo* extrair(No_arv_parse *no);
};



#endif
