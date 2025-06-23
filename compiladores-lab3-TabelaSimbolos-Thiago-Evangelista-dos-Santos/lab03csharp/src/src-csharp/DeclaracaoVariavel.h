#ifndef VARDECLARATION_H
#define VARDECLARATION_H
#include "Comando.h"
#include "Expressao.h"
#include "Variavel.h"


class DeclaracaoVariavel : public Comando {
public:
  Variavel *var;
  Expressao *expr;
  static DeclaracaoVariavel* extrair(No_arv_parse *no);
  void debug(int t) override;
  Valor * simular_execucao(TabelaDeSimbolos *tabela_de_simbolos) override;
  vector<Valor *> analisar_semantica(TabelaDeSimbolos *tabela_de_simbolos) override;
};



#endif //VARDECLARATION_H
