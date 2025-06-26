#include <algorithm>
#include<vector>
#include<string>
#include<iostream>
#include <fstream>   
#include<sstream>
#include<map>
#include<stack>
using namespace std;

#include "Arvore.hpp"
#include "Gramatica.hpp"
#include "Parser.hpp"
#include "TabelaLR1.hpp"
#include "src-csharp/Analisador.h"
#include "src-csharp/Funcao.h"


int main(int argc, char * argv[]) {
  if (argc != 3 && argc != 1) {
    cerr << "Parametros nomes dos arquivos: 1) csv com gramática e 2) csv com tabela LR1" << endl;
    return 1;
  }
  string nome_gramatica, nome_tab_lr1;
  if (argc == 1) {
    //cerr << "Valores padrao utilizados: gramatica.conf e tabela_lr1.conf" << endl;
    nome_gramatica = string("gramatica.conf");
    nome_tab_lr1 = string("tabela_lr1.conf");
  } else {
    nome_gramatica = string(argv[1]);
    nome_tab_lr1 = string(argv[2]);
  }

  ifstream arq_gramatica(nome_gramatica);
  ifstream arq_tabela_lr1(nome_tab_lr1);
  if (arq_tabela_lr1.fail() || arq_gramatica.fail()) {
    cerr << "Falha ao abrir arquivos: " << 
      ((arq_gramatica.fail()) ? nome_gramatica : "") << ", " << 
      ((arq_tabela_lr1.fail()) ? nome_tab_lr1 : "") << endl;
    return 1;    
  }
  Parser parser(arq_gramatica, arq_tabela_lr1);
  parser.tabela.debug();
  parser.gram.debug();

  
  Arvore_parse arv = parser.executa_parse(cin);
  cerr << "Parse executado" << endl;
  arv.debug();

  auto* program = arv.raiz;
  if (!program || program->regra != 1 || program->filhos.size() < 2) {
      cerr << "Erro: programa mal formado\n";
      return 1;
  }

  auto* classDecl = program->filhos[1];
  if (!classDecl || classDecl->regra != 8 || classDecl->filhos.size() < 4) {
      cerr << "Erro: classDecl inválido\n";
      return 1;
  }

  auto* memberDecls = classDecl->filhos[3];
  if (!memberDecls || memberDecls->regra != 9 || memberDecls->filhos.empty()) {
      cerr << "Erro: memberDecls inválido ou vazio\n";
      return 1;
  }

  auto* memberDecl = memberDecls->filhos[0];  // regra 12: MEMBER_DECL
  // cerr << "[main] Extraindo função a partir do nó regra " << memberDecl->regra << endl;

  // cerr << "[main] Chamando Funcao::extrair...\n";
  auto* func = Funcao::extrair(memberDecl);
  if (!func) {
      cerr << "Erro: Funcao::extrair retornou nullptr (regra = "
          << memberDecl->regra << ")\n";
      return 1;
  }

  func->debug(0);

  cerr << "[main] Preparando parametros de teste\n";
  // Exemplo de chamada do analisador semantico.
  vector<Valor*> parametros_passados;
  for (auto* paramDef : func->parametros) {
      const string &tipo = paramDef->tipo->nome;
      if (tipo == "int") {
          parametros_passados.push_back(new Int(4));
      } else if (tipo == "float") {
          parametros_passados.push_back(new Float(1.8f));
      } else if (tipo == "bool") {
          parametros_passados.push_back(new Bool(true));
      } else {
          cerr << "Tipo de parâmetro não suportado: " << tipo << endl;
          return 1;
      }
  }

  
  Analisador::calcula_ultimo_valor(func, parametros_passados);

  return 0;
}
