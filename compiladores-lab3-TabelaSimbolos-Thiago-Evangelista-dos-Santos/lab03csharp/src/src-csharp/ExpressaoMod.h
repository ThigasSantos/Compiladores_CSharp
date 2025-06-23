#ifndef EXPRESSAOMOD_H
#define EXPRESSAOMOD_H
#include "Expressao.h"

class ExpressaoMod final : public Expressao {
public:
  static ExpressaoMod* extrair(No_arv_parse *no);
  void debug(int t) override;
  Valor* simular_execucao(TabelaDeSimbolos *tabela_de_simbolos) override;
  Valor *analisar_semantica(TabelaDeSimbolos *tabela_de_simbolos) override;
};

#endif //EXPRESSAOMOD_H
