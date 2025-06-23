#ifndef EXPRESSAOIGUALDADE_H
#define EXPRESSAOIGUALDADE_H
#include "Expressao.h"

class ExpressaoIgualdade final : public Expressao {
public:
  static ExpressaoIgualdade* extrair(No_arv_parse *no);
  void debug(int t) override;
  Valor* simular_execucao(TabelaDeSimbolos *tabela_de_simbolos) override;
  Valor *analisar_semantica(TabelaDeSimbolos *tabela_de_simbolos) override;
};

#endif
