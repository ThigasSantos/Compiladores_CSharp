#ifndef EXPRESSAOMULTIPLICACAO_H
#define EXPRESSAOMULTIPLICACAO_H
#include "Expressao.h"

class ExpressaoMultiplicacao final : public Expressao {
public:
  static ExpressaoMultiplicacao* extrair(No_arv_parse *no);
  void debug(int t) override;
  Valor* simular_execucao(TabelaDeSimbolos *tabela_de_simbolos) override;
  Valor *analisar_semantica(TabelaDeSimbolos *tabela_de_simbolos) override;
};

#endif
