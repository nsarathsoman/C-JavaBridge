# CSharpJavaBridge


 How to compile the libjavabidge in macos? 
    g++ -I. -I /opt/homebrew/Cellar/openjdk/20.0.1/include -L /opt/homebrew/Cellar/openjdk/20.0.1/libexec/openjdk.jdk/Contents/Home/lib/server -ljvm  -shared -o libjavabridge.dylib JavaBridge.cpp JavaVirtualMachine.cpp
