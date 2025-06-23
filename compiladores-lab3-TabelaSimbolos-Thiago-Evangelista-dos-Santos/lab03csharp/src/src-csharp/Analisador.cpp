#include "Analisador.h"

Valor * Analisador::calcula_ultimo_valor(Funcao *f, const vector<Valor *> &params) {

  f->analisar_semantica(new TabelaDeSimbolos());

  validar_parametros(f, params);


  const auto T = new TabelaDeSimbolos();

  T->pushTabela();

  for (int i = 0; i < f->parametros.size(); ++i) {
    T->adicionarSimbolo(f->parametros[i]->nome->nome, params[i]);
  }

  f->simular_execucao(T);
  const auto res = f->code_block->simular_execucao(T);

  T->popTabela();

  if(res && res->valor) return res;

  return T->ultimoValorAtribuido;
}

void Analisador::validar_parametros(Funcao *f, vector<Valor *> params) {

  if( f->parametros.size() != params.size() ) {
    cerr << f->nome_funcao->nome << " deveria receber " << f->parametros.size() << " mas recebeu " << params.size() << " parametros" << endl;
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
}

