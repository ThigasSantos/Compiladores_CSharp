#ifndef FUNCAO_H
#define FUNCAO_H

#include "../Arvore.hpp"    
#include "Comando.h"      
#include "ID.h"           
#include "Tipo.h"        
#include "Variavel.h"     
#include "CodeBlock.h"    
#include "TabelaDeSimbolos.h" 
#include "Valor.h"        


class No_arv_parse; 

class Funcao : public Comando { 
public:

    static Funcao* extrair(No_arv_parse *no); 

    Funcao();

    ID* nome_funcao; 
    Tipo* tipo_retorno; 
    std::vector<Variavel*> parametros;
    CodeBlock* code_block;

    // Métodos para análise semântica e simulação
    Valor* simular_execucao(TabelaDeSimbolos *tabela_de_simbolos);
    std::vector<Valor *> analisar_semantica(TabelaDeSimbolos *tabela_de_simbolos);

    void debug(int t);

    // Getters para compatibilidade com outras partes do código
    ID* getNome() const { return nome_funcao; }
    Tipo* getTipoRetorno() const { return tipo_retorno; }
    const std::vector<Variavel*>& getParametros() const { return parametros; }
    CodeBlock* getCorpo() const { return code_block; }

    // Destrutor virtual para liberar a memória dos membros
    virtual ~Funcao(); // Implementar no .cpp
};

#endif // FUNCAO_H