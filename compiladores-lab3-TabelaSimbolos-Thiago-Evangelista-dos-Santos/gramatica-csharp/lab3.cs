using System;

class Teste {
    float calcula_ultimo_valor(int a, float b, bool condicao) {
        // Declarações de variáveis
        int contador = 0;
        float soma = a + b;
        bool resultado = false;

        // Atribuições
        a = a + 5;
        b = b * 2.5f;
        resultado = (a < 10) && condicao;

        // IF-THEN-ELSE com operadores relacionais e lógicos
        if ((a == 10 || b < 20.0f) && !resultado) {
            soma = soma + 1.0f;
        } else {
            soma = soma - 1.0f;
        }

        // WHILE com operadores aritméticos e booleanos
        while (contador < 5 && resultado) {
            soma = soma + contador * 1.5f;
            contador = contador + 1;
        }

        // Expressão com resto (%)
        a = a % 2;

        // Return final
        return soma;
    }
}
