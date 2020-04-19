#include <string>
#include<jni.h>

class JavaVirtualMachine
{
public:
    JavaVirtualMachine();
    ~JavaVirtualMachine();
    int executeStaticIntMethod(std::string className, std::string methodName, std::string methodSignature, int x, int y);
    void executeStaticVoidMethod(std::string className, std::string methodName, std::string methodSignature, std::string number);

private:
    JavaVM *javaVM;
    JNIEnv *jniEnv;
};
