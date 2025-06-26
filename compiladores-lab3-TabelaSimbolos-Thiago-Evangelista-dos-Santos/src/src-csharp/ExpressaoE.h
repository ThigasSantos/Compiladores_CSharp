#ifndef EXPRESSAOE_H
#define EXPRESSAOE_H
#include "Expressao.h"

class ExpressaoE final : public Expressao {
public:
  static ExpressaoE* extrair(No_arv_parse *no);
  void debug(int t) override;
  Valor* simular_execucao(TabelaDeSimbolos *tabela_de_simbolos) override;
  Valor *analisar_semantica(TabelaDeSimbolos *tabela_de_simbolos) override;
};

#endif
