#include "Expressao.h"
#include "ExpressaoAtribuicao.h"
#include "ExpressaoE.h"
#include "ExpressaoOu.h"
#include "ExpressaoIgualdade.h"
#include "ExpressaoMenorQue.h"
#include "ExpressaoSoma.h"
#include "ExpressaoSubtracao.h"
#include "ExpressaoMultiplicacao.h"
#include "ExpressaoDivisao.h"
#include "ExpressaoMod.h"
#include "ExpressaoNot.h"
#include "ExpressaoNumero.h"
#include "ExpressaoVariavel.h"
#include "ExpressaoChamada.h"
#include "ExpressaoBooleana.h"

#include <iostream>

using namespace std;

// Extrai uma expressão de acordo com a produção da sua gramática
Expressao* Expressao::extrair(No_arv_parse* no) {
    if (!no) return nullptr;
    switch (no->regra) {
        // Reduções transitivas: vá descendo
        case 40: case 43: case 45: case 47: case 50: case 55: case 58: case 62: case 66:
            return Expressao::extrair(no->filhos[0]);

        // Atribuição
        case 34: // VARIABLE_ASSIGN -> ID_RULE = EXPRESSION
            return ExpressaoAtribuicao::extrair(no);

        // Operadores lógicos
        case 44: // LOGICAL_OR -> LOGICAL_OR || LOGICAL_AND
            return ExpressaoOu::extrair(no);
        case 46: // LOGICAL_AND -> LOGICAL_AND && EQUALITY
            return ExpressaoE::extrair(no);

        // Igualdade e relacionais
        case 48: case 49: // == ou !=
            return ExpressaoIgualdade::extrair(no);
        case 51: case 52: case 53: case 54: // <, <=, >, >=
            return ExpressaoMenorQue::extrair(no);

        // Aritméticos
        case 56: // +
            return ExpressaoSoma::extrair(no);
        case 57: // -
            return ExpressaoSubtracao::extrair(no);
        case 59: // *
            return ExpressaoMultiplicacao::extrair(no);
        case 60: // /
            return ExpressaoDivisao::extrair(no);
        case 61: // %
            return ExpressaoMod::extrair(no);

        // Unários
        case 63: // !
            return ExpressaoNot::extrair(no);

        // Literais e variáveis
        case 71: case 77: // primitivos
            return ExpressaoNumero::extrair(no);
        case 75: case 76:
            return ExpressaoBooleana::extrair(no);
        case 78: // ID_RULE
            return ExpressaoVariavel::extrair(no);
        case 79: // chamada de função
            return ExpressaoChamada::extrair(no->filhos[0]);
        case 80: // parênteses
            return Expressao::extrair(no->filhos[1]);

        default:
            cerr << "[Expressao::extrair] Regra não suportada: " << no->regra << endl;
            return nullptr;
    }
}

void Expressao::debug(int t) {
    cerr << string(t, ' ') << "<Expressao genérica>\n";
}

Valor* Expressao::simular_execucao(TabelaDeSimbolos* tabela_de_simbolos) {
    return nullptr;
}

Valor* Expressao::analisar_semantica(TabelaDeSimbolos* tabela_de_simbolos) {
    return simular_execucao(tabela_de_simbolos);
}
