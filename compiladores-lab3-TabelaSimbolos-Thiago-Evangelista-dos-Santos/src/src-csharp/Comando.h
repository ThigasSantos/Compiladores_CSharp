#ifndef STATEMENT_H
#define STATEMENT_H

#include "TabelaDeSimbolos.h"
#include "../Arvore.hpp"

class Comando {
public:
  virtual ~Comando() = default;

  static vector<Comando*> extrair_comandos(No_arv_parse *no);
  static Comando* extrair(No_arv_parse *no);
  virtual Valor* simular_execucao(TabelaDeSimbolos * tabela_de_simbolos);
  virtual vector<Valor*> analisar_semantica(TabelaDeSimbolos * tabela_de_simbolos);
  virtual void debug(int t) {}
};

#endif //STATEMENT_H
