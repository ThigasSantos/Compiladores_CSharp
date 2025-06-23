#include "ComandoAtribuicao.h"
#include "../debug-util.hpp"
#include <iostream>

using namespace std;

ComandoAtribuicao::ComandoAtribuicao() : expressao(nullptr) {}
ComandoAtribuicao::~ComandoAtribuicao() {
    delete expressao;
}

ComandoAtribuicao* ComandoAtribuicao::extrair(No_arv_parse* no) {
    // no é o nó VARIABLE_ASSIGN -> ID_RULE ASSIGN EXPRESSION
    if (!no) return nullptr;
    auto* cmd = new ComandoAtribuicao();
    cmd->expressao = ExpressaoAtribuicao::extrair(no);
    if (!cmd->expressao) {
        delete cmd;
        return nullptr;
    }
    return cmd;
}

Valor* ComandoAtribuicao::simular_execucao(TabelaDeSimbolos* tabela) {
    // Executa a expressão de atribuição (que já faz o update na tabela)
    if (expressao) {
        expressao->simular_execucao(tabela);
    }
    // Comando de atribuição não retorna Valor*, só atualiza ultimoValor
    return nullptr;
}

void ComandoAtribuicao::debug(int t) {
    for(int i = 0; i < t; ++i) std::cerr << "  ";
    cerr << "[Atrib] ";
    if (expressao) {
        expressao->debug(0);
    } else {
        cerr << "<expressao invalida>";
    }
    cerr << endl;
}
