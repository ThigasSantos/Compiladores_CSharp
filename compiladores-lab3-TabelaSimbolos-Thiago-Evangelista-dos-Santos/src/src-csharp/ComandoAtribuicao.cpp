#include "ComandoAtribuicao.h"
#include "../debug-util.hpp"
#include <iostream>

using namespace std;

ComandoAtribuicao::ComandoAtribuicao() : expressao(nullptr) {}

ComandoAtribuicao::~ComandoAtribuicao() {
    delete expressao;
}

ComandoAtribuicao* ComandoAtribuicao::extrair(No_arv_parse* no) {
    if (!no) return nullptr;
    auto* cmd = new ComandoAtribuicao();
    // cerr << "[ComandoAtribuicao::extrair] Tentando extrair expressao de atribuição..." << endl;
    cmd->expressao = ExpressaoAtribuicao::extrair(no);
    if (!cmd->expressao) {
        cerr << "[ComandoAtribuicao::extrair] ERRO: expressão de atribuição retornou nulo" << endl;
        delete cmd;
        return nullptr;
    }
    return cmd;
}

Valor* ComandoAtribuicao::simular_execucao(TabelaDeSimbolos* tabela) {
    if (expressao) {
        expressao->simular_execucao(tabela);
    } else {
        cerr << "[ComandoAtribuicao::simular_execucao] Expressão nula" << endl;
    }
    return nullptr;
}

vector<Valor*> ComandoAtribuicao::analisar_semantica(TabelaDeSimbolos* tabela) {
    if (expressao) {
        Valor* resultado = expressao->analisar_semantica(tabela);
        if (!resultado) {
            cerr << "[ComandoAtribuicao::analisar_semantica] Falha: retorno nulo da análise" << endl;
        }
    }
    return {};
}

void ComandoAtribuicao::debug(int t) {
    for (int i = 0; i < t; ++i) std::cerr << "  ";
    cerr << "[Atrib] ";
    if (expressao) {
        expressao->debug(0);
    } else {
        cerr << "<expressao invalida>";
    }
    cerr << endl;
}
