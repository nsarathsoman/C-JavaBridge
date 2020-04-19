using System;
using System.Runtime.InteropServices;

namespace CSharpToJavaBridge
{
    class Program
    {
        [DllImport(".\\libjavabridge.so", EntryPoint = "Add")]
        private static extern int Add(int a, int b);
        static void Main(string[] args)
        {
            Console.WriteLine($"1 + 2 from Java = {Add(1, 2)}");
        }
    }
}
