#include "ComandoReturn.h"
#include <iostream>
#include "Funcao.h"
#include "Expressao.h"

/*
  39) RETURN_RULE -> RETURN EXPRESSION_OPT
  40) EXPRESSION_OPT -> EXPRESSION
  41) EXPRESSION_OPT ->
*/

ComandoReturn* ComandoReturn::extrair(No_arv_parse* no) {
    if (!no) return nullptr;
    auto* s = new ComandoReturn();

    if (no->filhos.size() > 1 && no->filhos[1]->filhos.size() > 0) {
        s->expr = Expressao::extrair(no->filhos[1]->filhos[0]);
    } else {
        s->expr = nullptr;
    }
    return s;
}

Valor* ComandoReturn::simular_execucao(TabelaDeSimbolos* tabela_de_simbolos) {
    if (!expr) return nullptr;
    return expr->simular_execucao(tabela_de_simbolos);
}

vector<Valor*> ComandoReturn::analisar_semantica(TabelaDeSimbolos* tabela_de_simbolos) {
    vector<Valor*> retorno;
    if (expr)
        retorno.push_back(expr->analisar_semantica(tabela_de_simbolos));
    return retorno;
}

void ComandoReturn::debug(int t) {
    std::cerr << std::string(t, ' ') << "Return ";
    if (expr) expr->debug(0);
    else std::cerr << "<vazio>";
    std::cerr << std::endl;
}
