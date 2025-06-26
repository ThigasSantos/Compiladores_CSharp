#ifndef EXPRESSAOMENORQUE_H
#define EXPRESSAOMENORQUE_H
#include "Expressao.h"

class ExpressaoMenorQue final : public Expressao {
public:
  static ExpressaoMenorQue* extrair(No_arv_parse *no);
  void debug(int t) override;
  Valor* simular_execucao(TabelaDeSimbolos *tabela_de_simbolos) override;
  Valor *analisar_semantica(TabelaDeSimbolos *tabela_de_simbolos) override;
};

#endif
