#ifndef EXPRESSAONUMERO_H
#define EXPRESSAONUMERO_H
#include "Expressao.h"

class ExpressaoNumero final : public Expressao {
public:
  Valor* valor = nullptr;
  static ExpressaoNumero* extrair(No_arv_parse *no);
  Valor* simular_execucao(TabelaDeSimbolos *tabela_de_simbolos) override;
  Valor *analisar_semantica(TabelaDeSimbolos *tabela_de_simbolos) override;
  void debug(int t) override;
};

#endif
