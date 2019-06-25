#Installation

## Installing JTK on Windows

1. On Windows, JTK uses the MSYS2 environment. Therefore, for compiling JTK on
   Windows, you need to install MSYS2. The steps required to install MSYS2 are
   beyond the scope of this documentation. Although, you can find tutorials on
   installing MSYS2 on the Internet.
2. Extract the source code to any directory of your choice, for the sake of this
   documentation we will refer to this location as `C:\jtk-1.0`.
3. Change the directory to 'C:\jtk-1.0'.
    ```
    cd 'C:/jtk-1.0'
    ```
4. Create a temporary directory for compiling the source code. We will refer to
   this directory as `build`.
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
7. Invoke the GNU Make program, or any other program for which you have generated
   the makefiles for. The `make` command may be different on your system, if you have
   not setup an alias.
   ```
   make
   ```
   This should compile the framework. Archives and executable files should be
   produced in your current working directory. You can link the library to
   your project. As of this version, a plethora of warnings are generated, when
   unsuppressed. We are working to eradicate these warnings.

Your console should look something like this as you execute each command.
```
Samuel@Samuel-PC MINGW32 ~
$ cd 'C:/jtk-1.0'

Samuel@Samuel-PC MINGW32 ~
$ mkdir build

Samuel@Samuel-PC MINGW32 ~
$ cd build

Samuel@Samuel-PC MINGW32 ~
$ cmake .. -G 'MSYS Makefiles'
* CMake output *

Samuel@Samuel-PC MINGW32 ~
$ make
* GNU Make output *

```

The following snippet shows the actual output generated on my system.
```
Samuel@Samuel-PC MINGW32 ~
$ cd 'F:\Project\jtk-1.0\release\jtk-1.0-beta'

Samuel@Samuel-PC MINGW32 /f/Project/jtk-1.0/release/jtk-1.0-beta
$ mkdir build

Samuel@Samuel-PC MINGW32 /f/Project/jtk-1.0/release/jtk-1.0-beta
$ cd build

Samuel@Samuel-PC MINGW32 /f/Project/jtk-1.0/release/jtk-1.0-beta/build
$ cmake .. -G 'MSYS Makefiles'
-- The C compiler identification is GNU 7.3.0
-- The CXX compiler identification is GNU 7.3.0
-- Check for working C compiler: D:/msys64/mingw32/bin/gcc.exe
-- Check for working C compiler: D:/msys64/mingw32/bin/gcc.exe -- works
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Detecting C compile features
-- Detecting C compile features - done
-- Check for working CXX compiler: D:/msys64/mingw32/bin/g++.exe
-- Check for working CXX compiler: D:/msys64/mingw32/bin/g++.exe -- works
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Detecting CXX compile features
-- Detecting CXX compile features - done
CMake Warning at CMakeLists.txt:34 (message):
  Build type not specified, falling back to 'Release' mode.  To specify build
  type use: -DCMAKE_BUILD_TYPE=<mode> where <mode> is Debug or Release.


-- Configuring done
-- Generating done
-- Build files have been written to: F:/Project/jtk-1.0/release/jtk-1.0-beta/build

Samuel@Samuel-PC MINGW32 /f/Project/jtk-1.0/release/jtk-1.0-beta/build
$ make
Scanning dependencies of target jtk-core
[  2%] Building C object CMakeFiles/jtk-core.dir/source/jtk/Configuration.c.obj
[  4%] Building C object CMakeFiles/jtk-core.dir/source/jtk/core/Double.c.obj
[  6%] Building C object CMakeFiles/jtk-core.dir/source/jtk/core/Float.c.obj
[  8%] Building C object CMakeFiles/jtk-core.dir/source/jtk/core/Integer.c.obj
[ 10%] Building C object CMakeFiles/jtk-core.dir/source/jtk/core/String.c.obj
[ 13%] Building C object CMakeFiles/jtk-core.dir/source/jtk/core/StringObjectAdapter.c.obj
[ 15%] Building C object CMakeFiles/jtk-core.dir/source/jtk/core/PointerObjectAdapter.c.obj
[ 17%] Building C object CMakeFiles/jtk-core.dir/source/jtk/math/Math.c.obj
[ 19%] Linking C static library libjtk-core.a
[ 19%] Built target jtk-core
Scanning dependencies of target jtk-collection
[ 21%] Building C object CMakeFiles/jtk-collection.dir/source/jtk/collection/CollectionHelper.c.obj
[ 23%] Building C object CMakeFiles/jtk-collection.dir/source/jtk/collection/Iterator.c.obj
[ 26%] Building C object CMakeFiles/jtk-collection.dir/source/jtk/collection/array/Array.c.obj
[ 28%] Building C object CMakeFiles/jtk-collection.dir/source/jtk/collection/array/ArrayIterator.c.obj
[ 30%] Building C object CMakeFiles/jtk-collection.dir/source/jtk/collection/array/Arrays.c.obj
[ 32%] Building C object CMakeFiles/jtk-collection.dir/source/jtk/collection/list/ArrayList.c.obj
[ 34%] Building C object CMakeFiles/jtk-collection.dir/source/jtk/collection/list/ArrayListIterator.c.obj
[ 36%] Building C object CMakeFiles/jtk-collection.dir/source/jtk/collection/list/DoublyLinkedList.c.obj
[ 39%] Building C object CMakeFiles/jtk-collection.dir/source/jtk/collection/list/DoublyLinkedListIterator.c.obj
[ 41%] Building C object CMakeFiles/jtk-collection.dir/source/jtk/collection/list/DoublyLinkedNode.c.obj
[ 43%] Building C object CMakeFiles/jtk-collection.dir/source/jtk/collection/map/HashMap.c.obj
[ 45%] Building C object CMakeFiles/jtk-collection.dir/source/jtk/collection/map/HashMapEntry.c.obj
[ 47%] Building C object CMakeFiles/jtk-collection.dir/source/jtk/collection/map/HashMapEntryIterator.c.obj
[ 50%] Building C object CMakeFiles/jtk-collection.dir/source/jtk/collection/map/HashMapKeyIterator.c.obj
[ 52%] Building C object CMakeFiles/jtk-collection.dir/source/jtk/collection/map/HashMapValueIterator.c.obj
[ 54%] Building C object CMakeFiles/jtk-collection.dir/source/jtk/collection/queue/ArrayQueue.c.obj
[ 56%] Building C object CMakeFiles/jtk-collection.dir/source/jtk/collection/queue/LinkedQueue.c.obj
[ 58%] Building C object CMakeFiles/jtk-collection.dir/source/jtk/collection/stack/ArrayStack.c.obj
[ 60%] Building C object CMakeFiles/jtk-collection.dir/source/jtk/collection/stack/LinkedStack.c.obj
[ 63%] Linking C static library libjtk-collection.a
[ 63%] Built target jtk-collection
Scanning dependencies of target jtk-unit
[ 65%] Building C object CMakeFiles/jtk-unit.dir/source/jtk/unit/ConsoleProgressListener.c.obj
[ 67%] Building C object CMakeFiles/jtk-unit.dir/source/jtk/unit/SimpleProgressListener.c.obj
[ 69%] Building C object CMakeFiles/jtk-unit.dir/source/jtk/unit/TestCase.c.obj
[ 71%] Building C object CMakeFiles/jtk-unit.dir/source/jtk/unit/TestDefect.c.obj
[ 73%] Building C object CMakeFiles/jtk-unit.dir/source/jtk/unit/TestFixture.c.obj
[ 76%] Building C object CMakeFiles/jtk-unit.dir/source/jtk/unit/TestListener.c.obj
[ 78%] Building C object CMakeFiles/jtk-unit.dir/source/jtk/unit/TestManager.c.obj
[ 80%] Building C object CMakeFiles/jtk-unit.dir/source/jtk/unit/TestSuite.c.obj
[ 82%] Linking C static library libjtk-unit.a
[ 82%] Built target jtk-unit
Scanning dependencies of target number
[ 84%] Building C object CMakeFiles/number.dir/example/unit/Number/Main.c.obj
[ 86%] Building C object CMakeFiles/number.dir/example/unit/Number/Number.c.obj
[ 89%] Linking C executable number.exe
[ 89%] Built target number
Scanning dependencies of target names
[ 91%] Building C object CMakeFiles/names.dir/example/collection/names/Names.c.obj
[ 93%] Linking C executable names.exe
[ 93%] Built target names
Scanning dependencies of target jtk-test
[ 95%] Building C object CMakeFiles/jtk-test.dir/test/source/Main.c.obj
[ 97%] Building C object CMakeFiles/jtk-test.dir/test/source/com/jtk/collection/list/ArrayListTest.c.obj
[100%] Linking C executable jtk-test.exe
[100%] Built target jtk-test
```