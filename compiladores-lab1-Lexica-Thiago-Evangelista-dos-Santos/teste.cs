using System;

public struct Ponto {
    public int x;
    public int y;
}

class Program {
    static double Func(Ponto[] v, int n) {
        if (n <= 0) {
            return 1.0;
        } else if (n == 1) {
            return 1.01 + v[0].x / 1e2 + v[0].y / 0.001;
        }

        double res = 0.25e-13;

        for (int i = n - 1; i >= 0 && v[i].x > 0; --i) {
            double temp = v[i].y * v[i].x % 123;

            if (temp < 0.0) {
                res -= res * 0.02 + Func(v, n - 1) * temp;
            } else {
                res += res * 300 + Func(v, n - 2) * temp;
                Console.WriteLine("Estranho, ne?");
            }
        }

        return res;
    }

    static void Main() {
        Ponto[] pontos = new Ponto[] {
            new Ponto { x = 5, y = 10 },
            new Ponto { x = 2, y = 3 },
            new Ponto { x = -1, y = 4 }  // Esse ponto fará o loop parar por causa do x < 0
        };

        double resultado = Func(pontos, pontos.Length);
        Console.WriteLine("Resultado: " + resultado);
    }
}
