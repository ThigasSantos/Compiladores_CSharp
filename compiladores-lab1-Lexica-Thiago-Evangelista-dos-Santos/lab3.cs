using System;

class Teste {
    int calcula_ultimo_valor(int a, float b, bool condicao) {
        a = 5;
        b = 3;
        int contador = 0;
        float soma = a + b;
        a = 10;
        bool ativado = condicao && (soma > 10.0);

        return soma;
    }
}
