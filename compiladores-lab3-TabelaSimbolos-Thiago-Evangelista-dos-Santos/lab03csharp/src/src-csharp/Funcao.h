#ifndef FUNCAO_H
#define FUNCAO_H

#include "../Arvore.hpp"     // Para No_arv_parse se ainda for usado ou para Arvore::Node
#include "Comando.h"      // Para herdar de Comando
#include "ID.h"           // Para o nome da função e parâmetros
#include "Tipo.h"         // Para os tipos
#include "Variavel.h"     // Para os parâmetros da função
#include "CodeBlock.h"    // Para o corpo da função
#include "TabelaDeSimbolos.h" // Para a análise semântica e simulação
#include "Valor.h"        // Para os valores retornados

// Forward declaration para No_arv_parse (se não estiver em Arvore.hpp)
class No_arv_parse; // Se Arvore::Node é o No_arv_parse, remova esta linha

class Funcao : public Comando { // Funcao herda de MemberDecl agora
public:
    // ATENÇÃO: Se No_arv_parse é o mesmo que Arvore::Node,
    //          você pode usar Arvore::Node direto.
    //          Se No_arv_parse é uma classe separada, mantenha assim.
    //          Estou assumindo que No_arv_parse é o tipo base que seu parser manipula.
    static Funcao* extrair(No_arv_parse *no); // Método estático para extrair da árvore de parse

    // Construtor padrão (pode ser private se você só usa o extrair)
    Funcao();

    // Membros da classe (renomeados para consistência)
    ID* nome_funcao; // Mantido o nome original para evitar mais quebras por agora
    Tipo* tipo_retorno; // Mantido o nome original
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