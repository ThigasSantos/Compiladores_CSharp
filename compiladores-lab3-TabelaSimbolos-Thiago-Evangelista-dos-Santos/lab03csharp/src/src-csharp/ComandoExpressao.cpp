#include "ComandoExpressao.h"

ComandoExpressao *ComandoExpressao::extrair(No_arv_parse *no) {
  auto* s = new ComandoExpressao();
  s->expr = Expressao::extrair(no);

  return s;
}

Valor *ComandoExpressao::simular_execucao(TabelaDeSimbolos *tabela_de_simbolos) {
  expr->simular_execucao(tabela_de_simbolos);

  return nullptr;
}

vector<Valor *> ComandoExpressao::analisar_semantica(TabelaDeSimbolos *tabela_de_simbolos) {
  expr->analisar_semantica(tabela_de_simbolos);

  return {};
}


void ComandoExpressao::debug(int t) {
  expr->debug(t);
}
