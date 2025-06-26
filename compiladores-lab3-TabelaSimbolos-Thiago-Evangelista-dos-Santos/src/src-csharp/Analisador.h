#ifndef ANALISADOR_H
#define ANALISADOR_H

#include <vector>
#include "Funcao.h"

using namespace std;

class Analisador {
public:
  static Valor* calcula_ultimo_valor(Funcao *f, const vector<Valor *> &params);
  static void validar_parametros(Funcao *f, vector<Valor*> params);
};
  
#endif
