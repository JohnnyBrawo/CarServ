# CarServ
The Beginning

LINUX : 
http://qtnbeyond.blogspot.com/2011/03/statically-building-with-qt-creator-in.html


WINDOWS : 
amin-ahmadi.com/2017/11/01/how-to-build-qt-5-9-2-static-using-mingw/
 
amin-ahmadi.com
How to Build Qt 5.9.2 Static Using MinGW - Amin
You can follow the instructions below to build Qt 5.9.2 from sources using MinGW, and statically. To be able to proceed further, you need to make sure you have all the prerequisites on your PC, which are mentioned in this post, then return here.Assuming that you have taken care of all the requirements, you can … Continue reading "How to Build Qt 5.9.2 Static Using MinGW"

не знам защо но при мен не е станало баш по тая инструкция и след това се е наложила да правя промени по qmake.conf който при мен се намира C:\Qt\Qt5.6.3\5.6.3\mingw49_32_static\mkspecs\win32-g++
поне мисля че в тоя тоториял не е описано да се правят тея промени но се е наложило
промените с 2 реда
DEFINES += QT_STATIC_BUILD



wiki.qt.io/Building_a_static_Qt_for_Windows_using_MinGW
wiki.qt.io
Building a static Qt for Windows using MinGW - Qt Wiki


