using System;

class Program {
    static double Func(double[][] v, int n) {
        if (n <= 0) {
            return 1.0;
        } else if (n == 1) {
            return 1.01 + v[0][0] / 1e2 + v[0][1] / 0.001;
        }

        double res = 0.25e-13;
        int i = n - 1;

        while (i >= 0 && v[i][0] >= 0) {
            double temp = v[i][1] * v[i][0] % 123;

            if (temp < 0.0) {
                res = res * 0.02 + Func(v, n - 1) * temp;
            } else {
                res = res * 300 + Func(v, n - 2) * temp;
                Console.WriteLine("Estranho, ne?");
            }

            i = i-1;
        }

        return res;
    }

    static void Main() {

        double[][] pontos = new double[][] {
            new double[] { 5, 10 },
            new double[] { 2, 3 },
            new double[] { -1, 4 } 
        };

        double[] teste;
        teste = new double[3];

        double resultado = Func(pontos, pontos.Length);
        Console.WriteLine("Resultado: " + resultado);
    }
}
