#include "Tipo.h"
#include <iostream>

using namespace std;

Tipo::Tipo() = default;

Tipo* Tipo::extrair(No_arv_parse *no) {
    if (!no || no->filhos.size() < 1) {
        cerr << "[Tipo::extrair] ERRO: no nulo ou com filhos insuficientes\n";
        return nullptr;
    }

    // TYPE → SIMPLE_TYPE TYPE_DIMENSION
    No_arv_parse* simple_type_node = no->filhos[0];
    if (!simple_type_node || simple_type_node->filhos.empty()) {
        cerr << "[Tipo::extrair] ERRO: SIMPLE_TYPE inválido\n";
        return nullptr;
    }

    No_arv_parse* terminal_token = simple_type_node->filhos[0];
    if (!terminal_token || terminal_token->regra != -1) {
        cerr << "[Tipo::extrair] ERRO: tipo terminal inválido\n";
        return nullptr;
    }

    auto* res = new Tipo();
    res->nome = terminal_token->dado_extra;  // Ex: "int", "float", etc.

    if (res->nome.empty()) {
        cerr << "[Tipo::extrair] AVISO: tipo com nome vazio\n";
    }

    return res;
}
