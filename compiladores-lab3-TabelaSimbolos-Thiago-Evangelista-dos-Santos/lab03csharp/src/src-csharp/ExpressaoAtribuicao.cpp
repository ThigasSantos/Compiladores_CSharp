#include <iostream>
#include <ostream>

#include "ExpressaoAtribuicao.h"
#include "Valor.h"

using namespace std;

ExpressaoAtribuicao* ExpressaoAtribuicao::extrair(No_arv_parse* no) {
    auto* e = new ExpressaoAtribuicao();

    if (!no || no->filhos.size() < 3) {
        cerr << "[ExpressaoAtribuicao::extrair] ERRO: nó inválido ou incompleto." << endl;
        delete e;
        return nullptr;
    }

    e->id = ID::extrai_ID(no->filhos[0]->filhos[0]);
    e->r_expr = Expressao::extrair(no->filhos[2]);

    return e;
}

Valor* ExpressaoAtribuicao::simular_execucao(TabelaDeSimbolos* tabela_de_simbolos) {
    Valor* v = tabela_de_simbolos->buscarVariavel(id->nome);
    Valor* v2 = r_expr->simular_execucao(tabela_de_simbolos);

    if (!v) {
        cerr << "[ExpressaoAtribuicao::simular_execucao] Variável não declarada: " << id->nome << endl;
        throw runtime_error("VariavelNaoDeclarada");
    }

    v->atribuir(v2);
    tabela_de_simbolos->atualizarSimbolo(id->nome, v);

    return v;
}

Valor* ExpressaoAtribuicao::analisar_semantica(TabelaDeSimbolos* tabela_de_simbolos) {
    Valor* v = tabela_de_simbolos->buscarVariavel(id->nome);
    Valor* v2 = r_expr->analisar_semantica(tabela_de_simbolos);

    if (!v) {
        cerr << "[ExpressaoAtribuicao::analisar_semantica] Variável não declarada: " << id->nome << endl;
        throw runtime_error("VariavelNaoDeclarada");
    }

    try {
        v->atribuir(Valor::valor_para_analise(v2->tipo()));
    } catch (const std::exception& e) {
        cerr << "[ExpressaoAtribuicao::analisar_semantica] Erro de tipo: " << e.what() << endl;
        throw;
    }

    return v;
}

void ExpressaoAtribuicao::debug(int t) {
    cerr << string(t, ' ') << "Atribuir [" << id->nome << "] = ";
    if (r_expr) r_expr->debug(t + 2);
    else cerr << "<expressão nula>";
}
