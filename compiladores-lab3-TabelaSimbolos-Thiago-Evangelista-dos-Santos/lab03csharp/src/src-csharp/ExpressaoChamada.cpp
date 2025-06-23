#include <iostream>

#include "ExpressaoChamada.h"
#include "Funcao.h"


Expressao *ExpressaoChamada::extrair_argumento(No_arv_parse *no) {
  // 87) ARG -> ID : EXPR
  // 88) ARG -> EXPR
  return Expressao::extrair(no->regra == 87 ? no->filhos[2] : no->filhos[0]);
}


vector<Expressao *> ExpressaoChamada::extrair_argumentos(No_arv_parse *no) {
  // 85) ARG_LIST -> ARG
  // 86) ARG_LIST -> ARG , ARG_LIST

  vector<Expressao*> res;
  res.push_back(extrair_argumento(no->filhos[0]));
  if (no->regra == 85) return res;
  vector<Expressao*> restante = extrair_argumentos(no->filhos[2]);
  res.insert(res.end(), restante.begin(), restante.end());

  return res;
}


ExpressaoChamada *ExpressaoChamada::extrair(No_arv_parse *no) {
  // 83) FUNC_CALL -> ID ( )
  // 84) FUNC_CALL -> ID ( ARG_LIST )
  auto e = new ExpressaoChamada();

  e->nome_funcao = ID::extrai_ID(no->filhos[0]);

  if(no->regra == 84) e->args = extrair_argumentos(no->filhos[2]);


  return e;
}


Valor *ExpressaoChamada::simular_execucao(TabelaDeSimbolos *tabela_de_simbolos) {
  const auto f = tabela_de_simbolos->buscarFuncao(nome_funcao->nome);

  vector<Valor *> params;
  for(const auto e: args) {
    params.push_back(e->simular_execucao(tabela_de_simbolos));
  }

  tabela_de_simbolos->pushTabela();

  for (int i = 0; i < f->parametros.size(); ++i) {
    tabela_de_simbolos->adicionarSimbolo(f->parametros[i]->nome->nome, params[i]);
  }
  auto res = Valor::of(f->tipo_retorno->nome);

  res->atribuir(f->code_block->simular_execucao(tabela_de_simbolos));

  tabela_de_simbolos->popTabela();

  return res;
}


Valor *ExpressaoChamada::analisar_semantica(TabelaDeSimbolos *tabela_de_simbolos) {
  const auto f = tabela_de_simbolos->buscarFuncao(nome_funcao->nome);

  if (f == nullptr) {
    cerr << "Função " << nome_funcao->nome << " nao existe" << endl;
    throw std::exception();
  }

  vector<Valor *> params;
  for(const auto e: args) {
    params.push_back(e->analisar_semantica(tabela_de_simbolos));
  }

  if( f->parametros.size() != params.size() ) {
    cerr <<"Função " << f->nome_funcao->nome << " deveria receber " << f->parametros.size() << " mas recebeu " << params.size() << " parametros" << endl;
    throw std::invalid_argument("Quantidade de Parametros Invalida");
  }

  for ( int i = 0; i < f->parametros.size(); ++i ) {
    auto * param_passado = params[i];
    auto * param_esperado = f->parametros[i];

    if ( param_esperado->tipo->nome != param_passado->tipo() ) {
      cerr << "Tipo Invalido para o parametro " << param_esperado->nome->nome << ": \"" << param_passado->tipo() << "\"" << endl;
      throw std::invalid_argument("Tipo Invalido de Parametro");
    }
  }

  return Valor::valor_para_analise(f->tipo_retorno->nome);
}



void ExpressaoChamada::debug(int t) {
  cerr << "FuncCall " << nome_funcao->nome << "(";
  for (auto e : args) {
    e->debug(t);
    cerr << ", ";
  }

  cerr << ")";
}
