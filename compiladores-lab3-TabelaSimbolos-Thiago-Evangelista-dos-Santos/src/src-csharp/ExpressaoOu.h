#ifndef EXPRESSAOOU_H
#define EXPRESSAOOU_H
#include "Expressao.h"

class ExpressaoOu final : public Expressao {
public:
  static ExpressaoOu* extrair(No_arv_parse *no);
  void debug(int t) override;
  Valor* simular_execucao(TabelaDeSimbolos *tabela_de_simbolos) override;
  Valor *analisar_semantica(TabelaDeSimbolos *tabela_de_simbolos) override;
};

#endif
