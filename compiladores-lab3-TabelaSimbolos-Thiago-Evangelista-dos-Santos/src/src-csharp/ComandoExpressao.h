#ifndef STATEMENTEXPRESSAO_H
#define STATEMENTEXPRESSAO_H

#include "Comando.h"
#include "Expressao.h"


class ComandoExpressao : public Comando {
public:
  Expressao* expr;

  static ComandoExpressao *extrair(No_arv_parse *no);
  Valor * simular_execucao(TabelaDeSimbolos *tabela_de_simbolos) override;
  vector<Valor *> analisar_semantica(TabelaDeSimbolos *tabela_de_simbolos) override;
  void debug(int t) override;
};



#endif
