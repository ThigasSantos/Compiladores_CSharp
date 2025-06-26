#include "Variavel.h"
#include "../debug-util.hpp"
#include <iostream>

using namespace std;

Variavel::Variavel() = default;

vector<Variavel*> Variavel::extrair_parametros(No_arv_parse* no) {
    vector<Variavel*> res;

    if (!no) {
        cerr << "[extrair_parametros] ERRO: no == nullptr\n";
        return res;
    }

    switch (no->regra) {
        case 22: // PARAM_LIST -> PARAM_LIST COMMA PARAM
            if (no->filhos.size() < 3) {
                cerr << "[extrair_parametros] ERRO: regra 22 com menos de 3 filhos\n";
                return res;
            }
            {
                auto anterior = extrair_parametros(no->filhos[0]);
                auto novo = Variavel::extrair(no->filhos[2]);
                if (novo) anterior.push_back(novo);
                return anterior;
            }

        case 23: // PARAM_LIST -> PARAM
            if (no->filhos.empty()) {
                cerr << "[extrair_parametros] ERRO: regra 23 com 0 filhos\n";
                return res;
            }
            {
                auto v = Variavel::extrair(no->filhos[0]);
                if (v) res.push_back(v);
                return res;
            }

        case 24: // PARAM_LIST -> vazio
            return res;

        default:
            cerr << "[extrair_parametros] ERRO: regra inesperada (" << no->regra << ")\n";
            return res;
    }
}

Variavel* Variavel::extrair(No_arv_parse* no) {
    if (!no) {
        cerr << "[Variavel::extrair] ERRO: no == nullptr\n";
        return nullptr;
    }

    int regra = no->regra;

    // Pode ser: PARAM -> TYPE ID (25), ou FIELD_DECL -> TYPE ID ; (13) ou TYPE ID = EXP (14)
    if (regra != 25 && regra != 13 && regra != 14) {
        cerr << "[Variavel::extrair] ERRO: regra inesperada (esperado 25, 13 ou 14), veio " << regra << "\n";
        return nullptr;
    }

    if (no->filhos.size() < 2) {
        cerr << "[Variavel::extrair] ERRO: regra " << regra << " com filhos insuficientes\n";
        return nullptr;
    }

    auto* var = new Variavel();
    var->tipo = Tipo::extrair(no->filhos[0]);   // TYPE
    var->nome = ID::extrai_ID(no->filhos[1]);   // ID

    if (!var->tipo || !var->nome) {
        cerr << "[Variavel::extrair] ERRO: tipo ou nome nulos\n";
        delete var;
        return nullptr;
    }

    return var;
}

void Variavel::debug_com_tab(int tab) {
    tab3(tab);
    if (nome && tipo)
        cerr << "[" << nome->nome << ":" <<  tipo->nome << "]";
    else
        cerr << "[Variável incompleta]";
}
