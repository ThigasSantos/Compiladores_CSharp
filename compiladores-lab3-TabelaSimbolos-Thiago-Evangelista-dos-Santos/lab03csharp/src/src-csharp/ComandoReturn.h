#ifndef RETURNSTATEMENT_H
#define RETURNSTATEMENT_H
#include "Comando.h"
#include "Expressao.h"


class ComandoReturn final : public Comando {
public:
  Expressao* expr;
  static ComandoReturn* extrair(No_arv_parse *no);
  void debug(int t) override;
  Valor * simular_execucao(TabelaDeSimbolos *tabela_de_simbolos) override;
  vector<Valor *> analisar_semantica(TabelaDeSimbolos *tabela_de_simbolos) override;
};


#endif
