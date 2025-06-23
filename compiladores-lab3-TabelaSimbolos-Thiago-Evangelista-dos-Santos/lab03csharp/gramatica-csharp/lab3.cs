using System;

class Teste {
    int calcula_ultimo_valor(int a, float b, bool condicao) {
        int contador = 0;
        float soma = a + b;
        bool ativado = condicao && (soma > 10.0);

        while (contador < 3) {
            if (ativado) {
                soma = soma + 1.5;
            } else {
                soma = soma - 1.0;
            }
            contador = contador + 1;
        }

        return soma > 15.0;
    }
}
