#include "CodeBlock.h"
#include "../debug-util.hpp"
#include <iostream>

using namespace std;

CodeBlock::CodeBlock() {
  this->statements = vector<Comando*>();
}

// Regra esperada: BLOCK -> LBRACE STATEMENTS RBRACE
CodeBlock* CodeBlock::extrair(No_arv_parse *no) {
  if (!no || no->filhos.size() < 3) return nullptr;

  auto *block = new CodeBlock();
  No_arv_parse* stmts = no->filhos[1];

  // STATEMENTS -> STATEMENT STATEMENTS | ε
  while (stmts) {
    if (!stmts->filhos.empty()) {
      No_arv_parse* stmt = stmts->filhos[0];
      if (stmt) {
        auto* comando = Comando::extrair(stmt);
        if (comando) {
          block->statements.push_back(comando);
        } else {
          cerr << "[CodeBlock::extrair] comando nulo extraído da regra " << stmt->regra << endl;
        }
      }
    }

    if (stmts->filhos.size() > 1)
      stmts = stmts->filhos[1]; // próximo STATEMENTS
    else
      break;
  }

  return block;
}

Valor* CodeBlock::simular_execucao(TabelaDeSimbolos *tabela_de_simbolos) {
  tabela_de_simbolos->pushTabela();

  Valor *v = nullptr;
  for (auto *stmt : statements) {
    v = stmt->simular_execucao(tabela_de_simbolos);
    if (v != nullptr) break; // encontrou um return
  }

  tabela_de_simbolos->popTabela();
  return v;
}

vector<Valor*> CodeBlock::analisar_semantica(TabelaDeSimbolos *tabela_de_simbolos) {
  vector<Valor *> res;
  tabela_de_simbolos->pushTabela();

  for (auto *stmt : statements) {
    if (!stmt) {
      cerr << "[CodeBlock::analisar_semantica] Ignorando comando nulo." << endl;
      continue;
    }

    cerr << "[CodeBlock::analisar_semantica] Analisando comando:" << endl;
    stmt->debug(4);

    try {
      auto v = stmt->analisar_semantica(tabela_de_simbolos);
      if (!v.empty()) res.insert(res.end(), v.begin(), v.end());
    } catch (const std::exception& e) {
      cerr << "[ERRO] Durante análise semântica: " << e.what() << endl;
      throw;
    }
  }

  tabela_de_simbolos->popTabela();
  return res;
}

void CodeBlock::debug(int t) {
  cerr << string(t, ' ') << "DO {" << endl;
  for (auto *stmt : statements) {
    if (stmt) stmt->debug(t + 2);
    else cerr << string(t + 2, ' ') << "[Comando nulo]" << endl;
  }
  cerr << string(t, ' ') << "}" << endl;
}
