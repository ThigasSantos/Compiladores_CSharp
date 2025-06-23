#ifndef COMANDO_ATRIBUICAO_H
#define COMANDO_ATRIBUICAO_H

#include "Comando.h"
#include "ExpressaoAtribuicao.h"

// Representa o comando de atribuição: VARIABLE_ASSIGN ';'
class ComandoAtribuicao : public Comando {
public:
    // A expressão de atribuição (ID_RULE = EXPRESSION)
    ExpressaoAtribuicao* expressao;

    ComandoAtribuicao();
    ~ComandoAtribuicao() override;

    // Extrai a partir do nó VARIABLE_ASSIGN (regra específica)
    static ComandoAtribuicao* extrair(No_arv_parse* no);

    // Simula execução: realiza a atribuição e não interrompe o fluxo
    Valor* simular_execucao(TabelaDeSimbolos* tabela) override;

    // Debug imprime a atribuição com indentação
    void debug(int t) override;
};

#endif // COMANDO_ATRIBUICAO_H
