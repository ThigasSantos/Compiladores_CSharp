#ifndef EXPRESSAOCHAMADA_H
#define EXPRESSAOCHAMADA_H
#include "Expressao.h"

class ExpressaoChamada final : public Expressao {
public:
  vector<Expressao *> args;
  ID* nome_funcao;
  static vector<Expressao *> extrair_argumentos(No_arv_parse *no);
  static Expressao * extrair_argumento(No_arv_parse *no);
  static ExpressaoChamada* extrair(No_arv_parse *no);
  Valor* simular_execucao(TabelaDeSimbolos *tabela_de_simbolos) override;
  Valor *analisar_semantica(TabelaDeSimbolos *tabela_de_simbolos) override;
  void debug(int t) override;
};

#endif
