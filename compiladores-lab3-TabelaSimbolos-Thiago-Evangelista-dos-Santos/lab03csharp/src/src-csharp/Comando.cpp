#include "Comando.h"

#include <iostream>
#include <ostream>

#include "ComandoExpressao.h"
#include "ComandoIf.h"
#include "ComandoReturn.h"
#include "DeclaracaoVariavel.h"
#include "ComandoAtribuicao.h"
#include "ComandoWhile.h"
#include "Funcao.h"

vector<Comando *> Comando::extrair_comandos(No_arv_parse *no) {
  vector<Comando*> res;
  if (!no || no->filhos.empty()) return res;

  Comando* cmd = extrair(no->filhos[0]);
  if (cmd) res.push_back(cmd);

  if (no->filhos.size() > 1) {
    vector<Comando*> restante = extrair_comandos(no->filhos[1]);
    res.insert(res.end(), restante.begin(), restante.end());
  }

  return res;
}

Comando* Comando::extrair(No_arv_parse *no) {
  switch (no->regra) {
    case 30: // STATEMENT -> BLOCK
      return CodeBlock::extrair(no->filhos[0]);
    case 29: // STATEMENT -> IF LPAREN EXPRESSION RPAREN STATEMENT ELSE_STATEMENT
      return ComandoIf::extrair(no);
    case 31: // STATEMENT -> WHILE_RULE STATEMENT
      return ComandoWhile::extrair(no);
    case 32: // STATEMENT -> RETURN_RULE SEMI
      return ComandoReturn::extrair(no->filhos[0]);
    case 33: // STATEMENT -> FIELD_DECL
      return DeclaracaoVariavel::extrair(no->filhos[0]);
    case 34: // STATEMENT -> VARIABLE_ASSIGN SEMI
      return ComandoAtribuicao::extrair(no->filhos[0]);
    case 35: // STATEMENT -> EXPRESSION SEMI
      return ComandoExpressao::extrair(no->filhos[0]);
    default:
      cerr << "[Comando::extrair] Regra inesperada (STATEMENT): " << no->regra << endl;
  }

  return nullptr;
}

Valor *Comando::simular_execucao(TabelaDeSimbolos *tabela_de_simbolos) {
  throw std::runtime_error("simular execucao não implementada");
}

vector<Valor *> Comando::analisar_semantica(TabelaDeSimbolos *tabela_de_simbolos) {
  throw std::runtime_error("Analise semantica não implementada");
}

