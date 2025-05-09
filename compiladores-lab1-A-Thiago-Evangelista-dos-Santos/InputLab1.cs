using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

#nullable enable

namespace ComplexCSharpExample
{
    [AttributeUsage(AttributeTargets.All)]
    public class CustomAttribute : Attribute
    {
        public string Description { get; set; }
        public CustomAttribute(string description) => Description = description;
    }

    public enum Status { Active, Inactive, Pending }

    public interface IProcessable
    {
        void Process();
    }

    public delegate int MathOperation(int x, int y);

    public struct Coordinates
    {
        public double X, Y;
        public Coordinates(double x, double y) => (X, Y) = (x, y);
    }

    public record Person(string Name, int Age);

    public class Container<T>
    {
        private List<T> items = new();
        public void Add(T item) => items.Add(item);
        public T this[int index] => items[index];
        public IEnumerable<T> GetAll() => items;
    }

    public class SampleClass : IProcessable
    {
        public int Id { get; set; }
        private string? _name;
        public string Name
        {
            get => _name ?? "Unnamed";
            set => _name = value;
        }

        public event EventHandler? OnProcessed;

        public static async Task<string> ReadFileAsync(string path)
        {
            using StreamReader reader = new(path);
            return await reader.ReadToEndAsync();
        }

        public void Process()
        {
            OnProcessed?.Invoke(this, EventArgs.Empty);
        }

        public (int sum, int product) Calculate(int a, int b)
        {
            return (a + b, a * b);
        }

        public void PatternExample(object obj)
        {
            switch (obj)
            {
                case int i when i > 0:
                    Console.WriteLine($"Positive integer: {i}");
                    break;
                case string s:
                    Console.WriteLine($"String: {s}");
                    break;
                case null:
                    Console.WriteLine("Null");
                    break;
                default:
                    Console.WriteLine("Other type");
                    break;
            }
        }

        public string GetInterpolated() => $"ID: {Id}, Name: {Name}";
    }

    public static class Utilities
    {
        public static void RunMathOperation(MathOperation op)
        {
            Console.WriteLine($"Result: {op(10, 5)}");
        }

        public static void ReflectProperties<T>(T obj)
        {
            foreach (var prop in typeof(T).GetProperties())
            {
                Console.WriteLine($"{prop.Name} = {prop.GetValue(obj)}");
            }
        }

        public static unsafe void UnsafeMethod()
        {
            int value = 42;
            int* ptr = &value;
            Console.WriteLine($"Pointer value: {*ptr}");
        }

        public static dynamic GetDynamicObject()
        {
            dynamic obj = new System.Dynamic.ExpandoObject();
            obj.Name = "Dynamic Name";
            obj.Age = 30;
            return obj;
        }

        public static IEnumerable<string> FilterNames(IEnumerable<string> names)
        {
            return names.Where(n => n.Length > 3).Select(n => n.ToUpper());
        }

        public static void TryCatchExample()
        {
            try
            {
                int x = int.Parse("abc");
            }
            catch (FormatException ex)
            {
                Console.WriteLine($"Caught exception: {ex.Message}");
            }
            finally
            {
                Console.WriteLine("Finally block executed.");
            }
        }
    }

    class Program
    {
        static async Task Main()
        {
            Console.WriteLine("==== Iniciando Execução ====");

            // Coordenadas
            Coordinates coord = new(10.5d, 20.3D);
            Console.WriteLine($"Coordenadas: X = {coord.X}, Y = {coord.Y}");
            Console.WriteLine($"Status: {Status.Active}");

            var person = new Person("Alice", 25LU);
            var container = new Container<Person>();
            container.Add(person);
            Console.WriteLine(container[0]);

            var sample = new SampleClass { Id = 1, Name = "Test" };
            sample.OnProcessed += (sender, e) => Console.WriteLine("Processed event fired!");
            sample.Process();
            sample.PatternExample(123);
            sample.PatternExample("hello");

            Console.WriteLine(sample.GetInterpolated());

            var (sum, product) = sample.Calculate(3, 4);
            Console.WriteLine($"Sum: {sum}, Product: {product}");

            Utilities.RunMathOperation((x, y) => x + y);
            Utilities.ReflectProperties(person);

            dynamic dyn = Utilities.GetDynamicObject();
            Console.WriteLine($"{dyn.Name}, {dyn.Age}");

            var names = new[] { "Ana", "Bob", "Charles", "David" };
            foreach (var n in Utilities.FilterNames(names))
                Console.WriteLine(n);

            Utilities.TryCatchExample();

            // File I/O
            string path = "sample.txt";
            await File.WriteAllTextAsync(path, "Exemplo de conteúdo.");
            string content = await SampleClass.ReadFileAsync(path);
            Console.WriteLine($"Arquivo: {content}");

            // Unsafe block (precisa de /unsafe)
            // unsafe { Utilities.UnsafeMethod(); }

            Console.WriteLine("==== Fim da Execução ====");
        }
    }
}
