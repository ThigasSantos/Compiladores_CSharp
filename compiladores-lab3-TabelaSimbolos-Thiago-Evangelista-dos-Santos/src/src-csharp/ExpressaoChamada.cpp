#include "ExpressaoChamada.h"
#include "Funcao.h"
#include <iostream>

using namespace std;

vector<Expressao*> ExpressaoChamada::extrair_argumentos(No_arv_parse* no) {
    // 91: ARG_LIST → ARG_LIST , EXPRESSION
    // 92: ARG_LIST → EXPRESSION
    // 93: ARG_LIST → vazio

    vector<Expressao*> res;
    if (!no) return res;
    if (no->regra == 93) {
        // Regra de lista de argumentos vazia
        return res;
    }

    if (no->regra == 92) {
        // ARG_LIST → EXPRESSION
        res.push_back(Expressao::extrair(no->filhos[0]));
    } else if (no->regra == 91) {
        // ARG_LIST → ARG_LIST , EXPRESSION
        res = extrair_argumentos(no->filhos[0]); // parte antes da vírgula
        res.push_back(Expressao::extrair(no->filhos[2])); // último argumento
    } else {
        std::cerr << "[ExpressaoChamada::extrair_argumentos] Regra inesperada: " << no->regra << std::endl;
    }

    return res;
}

// Adaptação para sua gramática: PRIMARY -> ID_RULE LPAREN ARG_LIST RPAREN
ExpressaoChamada* ExpressaoChamada::extrair(No_arv_parse* no) {
    if (!no || no->regra != 79 || no->filhos.size() != 4) return nullptr; // PRIMARY

    auto* chamada = new ExpressaoChamada();

    chamada->nome_funcao = ID::extrai_ID(no->filhos[0]->filhos[0]); // ID_RULE -> ID ...
    chamada->args = extrair_argumentos(no->filhos[2]); // ARG_LIST

    return chamada;
}

Valor* ExpressaoChamada::simular_execucao(TabelaDeSimbolos* tabela) {
    const auto* func = tabela->buscarFuncao(nome_funcao->nome);
    if (!func) {
        cerr << "Função " << nome_funcao->nome << " não encontrada" << endl;
        throw std::runtime_error("FuncaoNaoDeclarada");
    }

    vector<Valor*> params;
    for (auto* arg : args) {
        params.push_back(arg->simular_execucao(tabela));
    }

    tabela->pushTabela();
    for (int i = 0; i < func->parametros.size(); ++i) {
        tabela->adicionarSimbolo(func->parametros[i]->nome->nome, params[i]);
    }

    auto* retorno = func->code_block->simular_execucao(tabela);
    tabela->popTabela();

    return retorno;
}

Valor* ExpressaoChamada::analisar_semantica(TabelaDeSimbolos* tabela) {
    const auto* func = tabela->buscarFuncao(nome_funcao->nome);
    if (!func) {
        cerr << "Função " << nome_funcao->nome << " não declarada" << endl;
        throw std::runtime_error("FuncaoNaoDeclarada");
    }

    if (func->parametros.size() != args.size()) {
        cerr << "Função " << nome_funcao->nome << " espera " << func->parametros.size()
             << " argumento(s), mas recebeu " << args.size() << endl;
        throw std::runtime_error("NumeroIncorretoDeParametros");
    }

    for (int i = 0; i < args.size(); ++i) {
        auto* esperado = Valor::valor_para_analise(func->parametros[i]->tipo->nome);
        auto* recebido = args[i]->analisar_semantica(tabela);

        try {
            esperado->atribuir(recebido);
        } catch (...) {
            cerr << "Tipo incompatível no argumento " << i + 1 << " da função "
                 << nome_funcao->nome << endl;
            throw;
        }
    }

    return Valor::valor_para_analise(func->tipo_retorno->nome);
}

void ExpressaoChamada::debug(int t) {
    cerr << string(t, ' ') << "FuncCall " << nome_funcao->nome << "(";
    for (size_t i = 0; i < args.size(); ++i) {
        args[i]->debug(0);
        if (i != args.size() - 1) cerr << ", ";
    }
    cerr << ")";
}
