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

Requirements:
Linux pc machine
Railib library prebuild for android , is included inside project libs folder.
Android Studio: https://developer.android.com/studio/index.html
Android NDK & SDK: (available for download in Android Studio)


You need some system configuration for additional paths and enviroment variables:

Well, add lines to yours file .bashrc or .profile one of this hidden files inside home directory
replace build tools version, mine: 31.0.0
replace ndk version to fit, mine: 23.0.7599858
replace java path and version, mine: /home/$USER/JDK/graalvm-ce-java16
replace android sdk path to match you needs mine:  /home/$USER/Android/Sdk

export JAVA_HOME="/home/$USER/JDK/graalvm-ce-java16"
export ANDROID_SDK_ROOT=/home/$USER/Android/Sdk
export ANDROID_HOME=$ANDROID_SDK_ROOT 
export ANDROID_NDK_HOME=/home/$USER/Android/Sdk/ndk/23.0.7599858

export PATH="$PATH:$ANDROID_SDK_ROOT/build-tools/31.0.0:\
$ANDROID_SDK_ROOT/cmdline-tools/latest/bin:\
$ANDROID_SDK_ROOT/emulator:\
$ANDROID_SDK_ROOT/tools:\
$ANDROID_SDK_ROOT/platform-tools:\
$JAVA_HOME/bin:\
$ANDROID_NDK_HOME:\
$ANDROID_HOME/bin"


Important!💣🧨 Tips for Android studio:  consider change java version from 1.8 under project structure settings to java >= 11 , for build this project i use java 16 from:  https://www.graalvm.org/
You can successfully use java provided by android studio or from debian repositories. 



