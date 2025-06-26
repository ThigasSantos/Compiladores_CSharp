#ifndef EXPRESSION_H
#define EXPRESSION_H
#include "Valor.h"
#include "TabelaDeSimbolos.h"

class Expressao {
public:
  virtual ~Expressao() = default;
  Expressao * l_expr = nullptr;
  Expressao* r_expr = nullptr;
  static Expressao* extrair(No_arv_parse *no);
  virtual void debug(int t);
  virtual Valor* simular_execucao(TabelaDeSimbolos *tabela_de_simbolos);
  virtual Valor* analisar_semantica(TabelaDeSimbolos *tabela_de_simbolos);
};

#endif
