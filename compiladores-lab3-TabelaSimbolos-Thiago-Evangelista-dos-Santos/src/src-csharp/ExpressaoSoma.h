#ifndef EXPRESSAOSOMA_H
#define EXPRESSAOSOMA_H
#include "Expressao.h"

class ExpressaoSoma final : public Expressao {
public:
  static ExpressaoSoma* extrair(No_arv_parse *no);
  void debug(int t) override;
  Valor* simular_execucao(TabelaDeSimbolos *tabela_de_simbolos) override;
  Valor *analisar_semantica(TabelaDeSimbolos *tabela_de_simbolos) override;
};

#endif
