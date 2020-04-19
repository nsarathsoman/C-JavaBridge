#include <jni.h>
#include <JavaVirtualMachine.hpp>

#define EXPORT_FUNC 
#define CALL_CONV

#include <iostream>


extern "C" EXPORT_FUNC int CALL_CONV Add(int a, int b ) 
{
    JavaVirtualMachine jvm;
    std::cout << "BAdd: " << a << ", " << b << std::endl;
    jint result = jvm.executeStaticIntMethod("Calculator", "add", "(II)I", a, b);
    std::cout << "BResult:" << result << std::endl;
    return result; 
}