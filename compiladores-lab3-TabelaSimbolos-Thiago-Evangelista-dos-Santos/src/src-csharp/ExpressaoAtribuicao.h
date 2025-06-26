#ifndef EXPRESSAOATRIBUICAO_H
#define EXPRESSAOATRIBUICAO_H
#include "Expressao.h"
#include "ID.h"

// Expressao de Atribuição
class ExpressaoAtribuicao final : public Expressao {
public:
  ID* id = nullptr;
  static ExpressaoAtribuicao* extrair(No_arv_parse *no);
  void debug(int t) override;
  Valor* simular_execucao(TabelaDeSimbolos *tabela_de_simbolos) override;
  Valor *analisar_semantica(TabelaDeSimbolos *tabela_de_simbolos) override;
};


#endif
