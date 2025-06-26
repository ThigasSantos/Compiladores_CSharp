#ifndef STATEMENTIF_H
#define STATEMENTIF_H
#include "CodeBlock.h"
#include "Comando.h"
#include "Expressao.h"

class ComandoIf: public Comando {
public:
  Expressao *expr;
  Comando *if_block;
  Comando *else_block;
  static ComandoIf *extrair(No_arv_parse *no);
  Valor * simular_execucao(TabelaDeSimbolos *tabela_de_simbolos) override;
  vector<Valor*> analisar_semantica(TabelaDeSimbolos *tabela_de_simbolos) override;
  void debug(int t) override;
};



#endif
