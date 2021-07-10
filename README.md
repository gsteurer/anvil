# Anvil

Anvil is a collection of algorithms, data structures, and utilities commonly found in standard libraries.  

Anvil pprovides easier-to-grok-and-test implementations of amenities commonly provided by standard libraries. While Anvil tries to provide the "best" implementation possible, sacrifices are made to preserve readability. Anvil is written to promote human readbility of its code. No guarantee is made, however, that any of this has actually been accomplished. 

Anvil is not reccomended for use outside of hobby projects as more optimized and idiomatic implementations exist elsewhere. 

I do not own any of the actual math and science the library implements unless it is original work. The license this library uses applies to the interfaces provided and original code. The license also provides a warranty which to my understanding effectively means "use this library at your own peril". If you are the original author of any of the pen-and-paper theory used within I am happy to cite your work and apply whatever licensing you desire. I have no financial stake in this project. 

Should any contributors join this project the expectation of the community is that all communication is cordial and dispassionate. Please be kind to anyone that participates. 

## Header Only
Anvil currently requires static linking for some functionality. This is considered tech debt and anvil should eventually migrate to a header only implementation. 


## Overview
### Utilities
- Smart Pointer
- Optional/Nullable
### Containers
- Hash Map
- Linked List
- Dynamic Array
- Graph
### Math
- Vectors
- Matricies
### Strings
- Object Oriented C String Wrapper

## Notes

### Visual Studio 2019 Project Structure
A `solution` contains multiple `project`s. Each `project` contains code.

### These notes belong elsewhere:
lua - pull down the git submodule
sqlite - requires tcl installation

must wrap include in `extern c`
sqlite requires

cd sqlite\sqlite
mkdir bld
nmake /f ..\Makefile.msc TOP=..\ FOR_WINRT=1

```

C:\Users\jsteurer\Code\cpp_workbench\tcl\__INSTALL\bin

cd C:\Users\jsteurer\Code\cpp_workbench\anvil\sqlite\sqlite
mkdir bld
cd bld
set PATH=%PATH%;C:\Users\jsteurer\Code\cpp_workbench\tcl\__INSTALL\bin
nmake /f ..\Makefile.msc sqlite3.c TOP=..\..\sqlite
```

* add project to solution - static lib, UWP
* remove pch, targetver, generated file and disable pch in properties
* add git sumodule to new project via CLI
  * ```git submodule add https://github.com/sqlite/sqlite.git .\sqlite\sqlite```
* fetch the submodule and perform any necessary build steps
* in vs2019, in the static lib project for the dependency, add all relevant code and header files
* add any requisite preprocessor definitions; right click > properties > preprocessor 
* right click to build the new static lib
* right click target project > add > references 
* build 

WINRT requires c++ 17
Right click Project > C++ > Language
https://docs.microsoft.com/en-us/windows/uwp/cpp-and-winrt-apis/troubleshooting

#### Frustrations

* The Microsoft CppUnitTest is, in practice, worthless because you're limited to one assert per test. It seems like some sneering time wasting pedantic dipshit at microsoft thinks tests should be written this way.  
#### Links
https://docs.microsoft.com/en-us/windows/uwp/files/file-access-permissions
https://github.com/google/googletest/blob/master/docs/primer.md
https://docs.oracle.com/cd/E19957-01/806-3568/ncg_goldberg.html
https://stackoverflow.com/questions/275004/timer-function-to-provide-time-in-nano-seconds-using-c high resolution timestamps
#### SDK Includes
C:\Program Files (x86)\Windows Kits\10\Include\10.0.19041.0

#### Leak Finding
`leaks -atExit -- bin/tests --gtest_filter=SliceTests.InsertPrimitive`

