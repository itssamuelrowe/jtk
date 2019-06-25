# Modules

The various components of JTK are grouped together under modules. Each module
compiles into a library archive. As of version 1.0, there are **four primary modules**
and **two secondary modules**. A _primary module_ is a fully-featured module with many
classes. Whereas, a _secondary module_ is a module with fewer classes which
supports one or more primary modules. In any case, both the modules can be
used by the user.

If you don't fully understand these concepts, don't worry. You can use JTK anyway.

Further, each module is again divided into classes. Note that, a class in JTK
simply refers to a group of related functions. The name of a class is dervied
from the type it is associated with primarily. Each class occupies a single header
file. A class may manipulate instances of a specific structure, declared in the
same header file. For example, the `TestCase` class simply refers to a group of
functions which work on an instance of the `jtk_TestCase_t` structure declared
in the `jtk/unit/TestCase.h` header file.

## The Core Module

The core module provides the basic necessities such as loggers, memory
allocation/deallocation utilities, string utilities, integer utilities, etc.

All the header files in this module are located in the `jtk/core` directory.

## The Collection Module
The collection module consists of various data structures and algorithms, which
include lists, maps, stacks, queues, etc.

All the header files in this module are located in the `jtk/collection` directory.

## The Unit Test Module

The unit module provides a simple interface for writing unit tests.

All the header files in this module are located in the `jtk/unit` directory.