# rayturbo
Android studio native project template using cross platform raylib graphics library.
https://www.raylib.com/

This project use gradle and cmake to easily build apk files for arm, arm63, x86, x86_64.

/app/src/main/cpp/libs folder contain prebuilt version of debug static raylib for all mobile platforms.

Set yours version of ndk under build.gradle file, for me is: android.ndkVersion "23.0.7599858".

Consider change java version under project structure settings to java >= 11 , for build this project i use java 16.


