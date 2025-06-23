#ifndef EXPRESSAOSUBTRACAO_H
#define EXPRESSAOSUBTRACAO_H
#include "Expressao.h"

class ExpressaoSubtracao final : public Expressao {
public:
  static ExpressaoSubtracao* extrair(No_arv_parse *no);
  void debug(int t) override;
  Valor* simular_execucao(TabelaDeSimbolos *tabela_de_simbolos) override;
  Valor *analisar_semantica(TabelaDeSimbolos *tabela_de_simbolos) override;
};

#endif
