#ifndef COMANDO_WHILE_H
#define COMANDO_WHILE_H

#include "Comando.h"
#include "Expressao.h"
#include "CodeBlock.h"

class ComandoWhile : public Comando {
public:
    Expressao* condicao;
    CodeBlock* bloco;

    ComandoWhile();
    ~ComandoWhile();

    static ComandoWhile* extrair(No_arv_parse* no);
    Valor* simular_execucao(TabelaDeSimbolos* tabela_de_simbolos) override;
    std::vector<Valor*> analisar_semantica(TabelaDeSimbolos* tabela_de_simbolos) override;
    void debug(int t) override;
};

#endif
