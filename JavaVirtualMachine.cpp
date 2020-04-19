#include <exception>
#include <stdexcept>
#include <string>
#include <jni.h>
#include <JavaVirtualMachine.hpp>
#include <iostream>

JavaVirtualMachine::JavaVirtualMachine()
{
    JavaVMOption jvmopt[1];
    jvmopt[0].optionString = "-Djava.class.path=.";

    JavaVMInitArgs vmArgs;
    vmArgs.version = JNI_VERSION_1_2;
    vmArgs.nOptions = 1;
    vmArgs.options = jvmopt;
    vmArgs.ignoreUnrecognized = JNI_TRUE;
    long flag = JNI_CreateJavaVM(&this->javaVM, (void **)&this->jniEnv, &vmArgs);
    if (flag == JNI_ERR)
    {
        throw std::runtime_error("Unable to create VM");
    }
}

JavaVirtualMachine::~JavaVirtualMachine()
{
    this->javaVM->DestroyJavaVM();
}

int JavaVirtualMachine::executeStaticIntMethod(std::string className, std::string methodName, std::string methodSignature, int x, int y)
{
    jclass jcls = this->jniEnv->FindClass(className.c_str());
    if (jcls == NULL)
    {
        this->jniEnv->ExceptionDescribe();
        throw std::runtime_error("Unable to load class");
    }

    if (jcls != NULL)
    {
        jmethodID methodId = this->jniEnv->GetStaticMethodID(jcls, methodName.c_str(), methodSignature.c_str());
        if (methodId != NULL)
        {
            std::cout << "JNIAdd: " << x << ", " << y << std::endl;
            jint result = this->jniEnv->CallStaticIntMethod(jcls, methodId, x, y);
            std::cout << "JNIResult: " << result << std::endl;
            if (this->jniEnv->ExceptionCheck())
            {
                this->jniEnv->ExceptionDescribe();
                this->jniEnv->ExceptionClear();
            }
            return result;
        }
        throw std::runtime_error("Unable to find the method");
    }
}

void JavaVirtualMachine::executeStaticVoidMethod(std::string className, std::string methodName, std::string methodSignature, std::string number)
{
    jclass jcls = this->jniEnv->FindClass(className.c_str());
    if (jcls == NULL)
    {
        this->jniEnv->ExceptionDescribe();
        this->javaVM->DestroyJavaVM();
        throw std::runtime_error("Unable to load class");
    }

    if (jcls != NULL)
    {
        jmethodID methodId = this->jniEnv->GetStaticMethodID(jcls, methodName.c_str(), methodSignature.c_str());
        if (methodId != NULL)
        {
            jstring str = this->jniEnv->NewStringUTF(number.c_str());
            this->jniEnv->CallStaticVoidMethod(jcls, methodId, str);
            if (this->jniEnv->ExceptionCheck())
            {
                this->jniEnv->ExceptionDescribe();
                this->jniEnv->ExceptionClear();
            }
        }
        // throw std::runtime_error("Unable to get the method");
    }
}
