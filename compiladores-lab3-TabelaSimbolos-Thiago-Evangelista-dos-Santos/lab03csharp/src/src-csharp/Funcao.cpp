#include "Funcao.h"
#include <iostream>
#include <stdexcept>

using namespace std;

/*
  12) MEMBER_DECL -> METHOD_DECL
  15) METHOD_DECL -> METHOD_ACCESS BLOCK
  16) METHOD_ACCESS -> PUBLIC METHOD_MODIFIER
  17) METHOD_ACCESS -> PRIVATE METHOD_MODIFIER
  18) METHOD_ACCESS -> METHOD_MODIFIER
  19) METHOD_MODIFIER -> STATIC METHOD_HEADER
  20) METHOD_MODIFIER -> METHOD_HEADER
  21) METHOD_HEADER -> TYPE ID LPAREN PARAM_LIST RPAREN
*/

Funcao::Funcao() = default;
Funcao::~Funcao() = default;

Funcao* Funcao::extrair(No_arv_parse* no) {
    // cerr << "[Funcao::extrair] Regra recebida: " << (no ? no->regra : -999) << endl;
    // cerr << "[Funcao::extrair] Número de filhos: " << (no ? no->filhos.size() : 0) << endl;

    if (!no) return nullptr;

    // Se for regra 12: MEMBER_DECL -> METHOD_DECL
    if (no->regra == 12) {
        return Funcao::extrair(no->filhos[0]); // entra no METHOD_DECL
    }

    // Se for regra 15: METHOD_DECL -> METHOD_ACCESS BLOCK
    if (no->regra == 15) {
        // Ignora tudo e busca por METHOD_HEADER e BLOCK

        No_arv_parse* method_access = no->filhos[0];
        No_arv_parse* method_modifier = nullptr;

        // METHOD_ACCESS -> PUBLIC/PRIVATE METHOD_MODIFIER (16, 17)
        // METHOD_ACCESS -> METHOD_MODIFIER (18)
        if (method_access->filhos.size() == 2)
            method_modifier = method_access->filhos[1];
        else
            method_modifier = method_access->filhos[0];

        // METHOD_MODIFIER -> STATIC METHOD_HEADER (19)
        // METHOD_MODIFIER -> METHOD_HEADER (20)
        No_arv_parse* method_header = method_modifier->filhos.back();

        // METHOD_HEADER -> TYPE ID ( PARAM_LIST ) (21)
        if (method_header->regra != 21) return nullptr;

        auto* func = new Funcao();

        func->tipo_retorno = Tipo::extrair(method_header->filhos[0]);
        func->nome_funcao = ID::extrai_ID(method_header->filhos[1]);
        func->parametros = Variavel::extrair_parametros(method_header->filhos[3]);

        func->code_block = CodeBlock::extrair(no->filhos[1]); // BLOCK
        return func;
    }

    return nullptr;
}

Valor* Funcao::simular_execucao(TabelaDeSimbolos* tabela_de_simbolos) {
    tabela_de_simbolos->adicionarSimbolo(nome_funcao->nome, this);
    return nullptr;
}

vector<Valor*> Funcao::analisar_semantica(TabelaDeSimbolos* tabela_de_simbolos) {
    tabela_de_simbolos->adicionarSimbolo(nome_funcao->nome, this);
    tabela_de_simbolos->pushTabela();

    // cerr << "[Funcao::analisar_semantica] Adicionando parametros..." << endl;
    for (auto* param : parametros) {
        cerr << "  - " << param->nome->nome << " : " << param->tipo->nome << endl;
        tabela_de_simbolos->adicionarSimbolo(
            param->nome->nome,
            Valor::valor_para_analise(param->tipo->nome)
        );
    }

    // ✅ Agora sim analisamos o corpo
    vector<Valor*> possiveis_retornos = code_block->analisar_semantica(tabela_de_simbolos);

    tabela_de_simbolos->popTabela();

    auto func_ret = Valor::valor_para_analise(tipo_retorno->nome);
    for (auto* ret : possiveis_retornos) {
        try {
            func_ret->atribuir(ret);
        } catch (const runtime_error& e) {
            throw runtime_error(
                "Função " + nome_funcao->nome +
                " precisa retornar o tipo " + tipo_retorno->nome +
                " e não " + ret->tipo()
            );
        }
    }

    return {};
}


void Funcao::debug(int t) {
    cerr << string(t, ' ') << "Funcao: [retorno=" << tipo_retorno->nome
         << "][nome=" << nome_funcao->nome << "] [Params:";
    for (auto* parametro : parametros) {
        cerr << " " << parametro->nome->nome << " : " << parametro->tipo->nome << ",";
    }
    cerr << "]" << endl;
    code_block->debug(t + 2);
}
