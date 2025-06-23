#ifndef CODEBLOCK_H
#define CODEBLOCK_H
#include <iostream>
#include "Comando.h"

class CodeBlock : public Comando {
public:
  vector<Comando*> statements;
  CodeBlock();
  static CodeBlock* extrair(No_arv_parse *no);
  Valor * simular_execucao(TabelaDeSimbolos *tabela_de_simbolos) override;
  vector<Valor*> analisar_semantica(TabelaDeSimbolos *tabela_de_simbolos) override;
  void debug(int t) override;
};



#endif //CODEBLOCK_H
