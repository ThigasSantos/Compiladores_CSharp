#include "ComandoWhile.h"
#include "Comando.h"
#include "../debug-util.hpp"
#include <iostream>

using namespace std;

ComandoWhile::ComandoWhile() : condicao(nullptr), bloco(nullptr) {}

ComandoWhile::~ComandoWhile() {
    delete condicao;
    delete bloco;
}

ComandoWhile* ComandoWhile::extrair(No_arv_parse* no) {
    if (!no || no->regra != 31) {
        cerr << "[ComandoWhile::extrair] Regra esperada 31, recebida: " << (no ? no->regra : -1) << endl;
        return nullptr;
    }

    auto* while_cmd = new ComandoWhile();
    No_arv_parse* while_rule = no->filhos[0];  // WHILE_RULE (regra 38)

    if (!while_rule || while_rule->regra != 38 || while_rule->filhos.size() < 5) {
        cerr << "[ComandoWhile::extrair] Regra WHILE_RULE (38) malformada" << endl;
        delete while_cmd;
        return nullptr;
    }

    // Expressão está no filho 2, corpo está no filho 4
    while_cmd->condicao = Expressao::extrair(while_rule->filhos[2]);
    while_cmd->bloco = dynamic_cast<CodeBlock*>(Comando::extrair(while_rule->filhos[4]));

    if (!while_cmd->condicao || !while_cmd->bloco) {
        cerr << "[ComandoWhile::extrair] Erro ao extrair condição ou bloco do while" << endl;
        delete while_cmd;
        return nullptr;
    }

    return while_cmd;
}

Valor* ComandoWhile::simular_execucao(TabelaDeSimbolos* tabela_de_simbolos) {
    while (true) {
        Valor* cond = condicao->simular_execucao(tabela_de_simbolos);
        if (!cond || !cond->valor->boolVal)
            break;

        bloco->simular_execucao(tabela_de_simbolos);
    }

    return nullptr;
}

std::vector<Valor*> ComandoWhile::analisar_semantica(TabelaDeSimbolos* tabela_de_simbolos) {
    const auto* tipo_cond = condicao->analisar_semantica(tabela_de_simbolos);
    if (!tipo_cond->isBool()) {
        cerr << "[ComandoWhile] Condição precisa ser do tipo booleano" << endl;
        throw std::runtime_error("TipoInvalidoWhile");
    }

    return bloco->analisar_semantica(tabela_de_simbolos);
}

void ComandoWhile::debug(int t) {
    tab2(t); cerr << "WHILE [cond=(";
    condicao->debug(0);
    cerr << ")]" << endl;
    bloco->debug(t + 2);
}
