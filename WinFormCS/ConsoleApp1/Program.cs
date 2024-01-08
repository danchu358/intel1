using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    internal class Program
    {
        static void Main(string[] args)
        {
            Test test = new Test();
            test.Main();
        }
    }
    class Test
    {
        void func1()
        {
            Console.WriteLine("long type의 크기는 " + sizeof(long) + "(byte) 범위" + long.MinValue + "," + long.MaxValue);
            Console.WriteLine("float type의 크기는 " + sizeof(float) + "(byte) 범위" + float.MinValue + "," + float.MaxValue);
            Console.WriteLine("double type의 크기는 " + sizeof(double) + "(byte) 범위" + double.MinValue + "," + double.MaxValue);
        }
        void func2()
        {
            char a = 'A';
            Console.WriteLine("char a = " + a);
            Console.WriteLine("char a + 1 = " + (a + 1));
            Console.WriteLine("char a + 2 = " + (a + 2));
        }
        void func3()
        {
            var a = 20;
            Console.WriteLine($"var a = {a}");
            a = 10;
            Console.WriteLine($"var a = {a}");
            Object o = a;
            Console.WriteLine($"Object o = {o}");
            o = "string";
            Console.WriteLine($"Object o = {o}");
            string s = (string)o;
            Console.WriteLine($"string s = {s}");
        }
        void func4()
        {
            int[] arr1 = { 1, 2, 3 };  //new int[100];
            for (int i = 0; i < arr1.Length; i++)
            {
                Console.WriteLine(arr1[i]);
            }

            char[] arr2 = { 'h', 'e', 'l', 'l', 'o' };  //new int[100];
            for (int i = 0; i < arr2.Length; i++)
            {
                Console.Write(arr2[i]);
            }
            Console.WriteLine("");
            string s = new string(arr2); Console.WriteLine(s);
            s = new string(arr2, 1, 2); Console.WriteLine(s);
        }
        public void Main()
        {
            //Console.WriteLine("      int type의 크기는 " + sizeof(int) + "(byte) 범위" + int.MinValue + "," + int.MaxValue);
            //Console.WriteLine("(표준)int type의 크기는 {0}(byte). 범위 {1}, {2}", sizeof(int), int.MinValue, int.MaxValue);
            //Console.WriteLine($"(보간)int type의 크기는 {sizeof(int)}(byte). 범위 {int.MinValue}, {int.MaxValue}");
            //func1();
            //func2();
            //func3();
            func4();
            Console.ReadKey();
        }
    }
} 
