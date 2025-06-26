#ifndef EXPRESSAOBOOLEANA_H
#define EXPRESSAOBOOLEANA_H
#include "Expressao.h"

class ExpressaoBooleana final : public Expressao {
public:
  Valor* valor = nullptr;
  static ExpressaoBooleana* extrair(No_arv_parse *no);
  Valor* simular_execucao(TabelaDeSimbolos *tabela_de_simbolos) override;
  Valor *analisar_semantica(TabelaDeSimbolos *tabela_de_simbolos) override;
  void debug(int t) override;
};

#endif
