using System;
using System.Runtime.InteropServices;

namespace CSharpToJavaBridge
{
    class ProgramCrossPlatform
    {
        delegate int AddDelegate(int a, int b);

        static void Main(string[] args)
        {
            var libraryName = GetLibraryName();
            var library = NativeLibrary.Load(libraryName);
            var addFunctionPtr = NativeLibrary.GetExport(library, "Add");
            var addFunction = Marshal.GetDelegateForFunctionPointer<AddDelegate>(addFunctionPtr);

            Console.WriteLine($"1 + 2 from Java = {addFunction(1, 2)}");
        }

        static string GetLibraryName()
        {
            if (RuntimeInformation.IsOSPlatform(OSPlatform.Windows))
            {
                return "libjavabridge.dll";
            }
            else if (RuntimeInformation.IsOSPlatform(OSPlatform.Linux))
            {
                return "libjavabridge.so";
            }
            else if (RuntimeInformation.IsOSPlatform(OSPlatform.OSX))
            {
                return "libjavabridge.dylib";
            }
            else
            {
                throw new PlatformNotSupportedException();
            }
        }
    }
}
