# rayturbo
Android studio native project template using cross platform raylib graphics library.
https://www.raylib.com/

This project use Android Studio with gradle and cmake to easily build apk files for arm, arm63, x86, x86_64.

/app/src/main/cpp/libs folder contain prebuilt version of debug static raylib for all mobile platforms.
But beware because the library is built with different options for the compiler:

raylib makefile:
----------------

this line:  ifeq ($(ANDROID_ARCH),arm64)

              ORG: CFLAGS += -target aarch64 -mfix-cortex-a53-835769
              
              NEW: CFLAGS += -m64
              

To build apk you need Android Studio software and ndk configured and installed.
I tested this under linux debian frankenstein version:) environment.


example paths in my .bashrc, XYZ is username or home folder name:

export PATH="$PATH:/sbin:/usr/sbin:usr/local/sbin:/bin:/usr/bin:/usr/local/bin:/home/XYZ/Android/Sdk/build-tools/30.0.3:/home/XYZ/Android/Sdk/cmdline-tools/latest/bin:/home/XYZ/.local/bin:/home/XYZ/Android/Sdk/emulator:/home/XYZ/Android/Sdk/tools:/home/XYZ/Android/Sdk/platform-tools:/home/XYZ/JDK/graalvm-ce-java16/bin:/home/XYZ/llvm/bin"


export JAVA_HOME="/home/XYZ/JDK/graalvm-ce-java16"

export ANDROID_SDK_ROOT=/home/XYZ/Android/Sdk

export ANDROID_HOME=/home/XYZ/Android/Sdk 



Set yours ndk version under build.gradle module file, for me is new: android.ndkVersion "23.0.7599858".


Important! consider change java version under project structure settings to java >= 11 , for build this project i use java 16.



