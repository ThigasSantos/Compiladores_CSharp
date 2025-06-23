#ifndef EXPRESSAOVARIAVEL_H
#define EXPRESSAOVARIAVEL_H
#include "Expressao.h"
#include "ID.h"

class ExpressaoVariavel final : public Expressao {
public:
  ID* id = nullptr;
  static ExpressaoVariavel* extrair(No_arv_parse *no);
  void debug(int t) override;
  Valor* simular_execucao(TabelaDeSimbolos *tabela_de_simbolos) override;
};

#endif
