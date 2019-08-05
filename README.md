What is JTK?
------------

JTK is a library designed for writing applications and libraries in C. It provides
the core utilities such as collections, unit testing, I/O streams, and much more.

Initially, the development of the library began within an other project, a
compiler for Zen. Zen is a programming language currently under development
at OneCube Software Solutions. We observed a need for a library that could be
reused in other projects. Therefore, we refactored the reusable components
and called it JTK.

Installation
------------

[Windows]

1. For compiling JTK on Windows, you first need to install MSYS2. The steps required  
   to install MSYS2 are beyond the scope of this documentation. Although, you can find  
   tutorials on installing MSYS2 on the Internet.  
2. Extract the source code to any directory of your choice, for the sake of this  
   documentation we will refer this location as 'C:\jtk-1.0'.  
3. Change the directory to 'C:\jtk-1.0'.  
    ```
    cd 'C:/jtk-1.0'
    ```
4. Create a temporary directory for compiling the source code. For the sake of this  
   documentation we will refer to this directory as 'build'.
   ```
   mkdir build
   ```
5. Change directory to the newly created directory.
   ```
   cd build
   ```
6. Invoke CMake to generate make files. In this documentation, we show the  
   commands to generate GNU Makefiles. You can easily generate other makefiles  
   similarly.
   ```
   cmake .. -G 'MSYS Makefiles'
   ```
7. Invoke the GNU Make program. The command may be different on your system,  
   if you have not setup an alias.
   ```
   make
   ```
   This should compile the framework. Archives and executable files should be  
   produced in your current working directory. You can link the library to  
   your project. As of this version, a plethora of warnings are generated.  
   We are working to eradicate these warnings.

Structure of JTK
----------------

The various components of JTK are grouped together under modules. Each module  
compiles into a library archive. As of version 1.0, there are three components.  

### [Core]
The core module provides the basic necessities such as loggers, memory  
allocation/deallocation, string utilities, integer utilities, etc.  


### [Collection]
This module consists of various data structures and algorithms, which include  
lists, maps, sets, bags, etc.


### [Unit]
A module designed for writing unit tests.  

Further, each module is again divided into classes. Not that, a class in JTK  
simply refers to a group of functions which manipulate instances of a specific  
structure. For example, the TestCase class simply refers a group of functions  
which work on an instance of the jtk_TestCase_t structure.  


Every component declared within JTK use the following name scheme:  

    jtk_Class_function

The name of a component is divided into three parts separated by an underscore:  
    * jtk - This prefix is added to all the components in JTK. We are simply  
      trying to simulate a name space (as in C++) or packages (as in Java).  
    * Class - The class in which the function belongs.  
    * function - The name of the function.  

Example (in Java):

```
class TestCase {

    ...

    public boolean isSuccessful() {
        ...
    }
}
```

The above class translate to the following snippet in C. It follows the naming
scheme as described above.

```
bool jtk_TestCase_isSuccessful(jtk_TestCase_t* testCase) {
    ...
}
```

Style Guidelines
----------------

### Files (relative to the root of the source code)


#### [example]
This directory consists of example programs. It is intended for beginners,
intermidiate users, and advanced users. It showcases a variety of examples of
using the framework.

#### [include]
This directory consists of all the header files exported by the JTK Framework.

#### [share]
This directory consists of misc files for tools such as pkg-config, etc.

#### [source]
This directory consists of all the source files that is compiled into library
archives.

#### [test]
This directory consits of unit tests for the framework.

#### [CMakeLists.txt]
The rules for compiling the library, unit tests, etc. Feed this file to CMake
in order to generate make files. Currently, it is tested only for MinGW Make.

#### [README.md]
A brief document to get you started. A more detailed document is yet to be written.


### Overload Suffixes


 - v - void pointer
 - b - byte
 - s - short
 - i - integer
 - l - long
 - f - float
 - d - double
 - utf8 - uint8_t*
 - z - boolean
 - c - char
 - cz - char*

Certain functions within the library are overloaded, that is, they perform the  
same operation but on different data types. Such functions share a same name  
with a unique suffix. The suffixes are listed above.


### TODO.txt


It lists all the features yet to be implemented by the framework.


## License

Copyright 2018-2019 OneCube

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
