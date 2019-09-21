# Friday, May 18, 2018

cmake_minimum_required (VERSION 3.4.1)

# Packages

# find_package (PkgConfig REQUIRED)

# Project Name

project("Jez Toolkit (JTK)")

# Project Version Number

set(JTK_PROJECT_VERSION_MAJOR 2)
set(JTK_PROJECT_VERSION_MINOR 0)
set(JTK_PROJECT_VERSION_PATCH 0)
set(JTK_PROJECT_VERSION_TWEAK 0)
set(JTK_PROJECT_VERSION "${JTK_PROJECT_VERSION_MAJOR}.${JTK_PROJECT_VERSION_MINOR}.${JTK_PROJECT_VERSION_PATCH}.${JTK_PROJECT_VERSION_TWEAK}")

# Directories

set(JTK_INSTALL_BINARY_DIR "${CMAKE_INSTALL_PREFIX}/bin" CACHE PATH "Installation directory for executables.")
set(JTK_INSTALL_LIBRARY_DIR "${CMAKE_INSTALL_PREFIX}/lib/jtk" CACHE PATH "Installation directory for libraries.")
set(JTK_INSTALL_INCLUDE_DIR "${CMAKE_INSTALL_PREFIX}/include" CACHE PATH "Installer directory for header files.")
set(JTK_INSTALL_PKGCONFIG_DIR "${CMAKE_INSTALL_PREFIX}/share/pkgconfig" CACHE PATH "Installer directory for pkgconfig (.pc) files.")

# Options

option(BUILD_shared "Build shared libraries instead of static libraries." ON)
option(BUILD_tests "Build the unit tests for JTK." ON)

if(NOT BUILD_TYPE)
    message(WARNING "Build type not specified, falling back to 'Release' mode. To specify build type use: -DCMAKE_BUILD_TYPE=<mode> where <mode> is Debug or Release.")
    set(BUILD_TYPE "Release" CACHE STRING "The type of build: Debug or Release." FORCE)
endif(NOT BUILD_TYPE)

# Source

include_directories("${PROJECT_SOURCE_DIR}/include")

set(
    JTK_CORE_SOURCE

    ${PROJECT_SOURCE_DIR}/source/jtk/Configuration.c

    ${PROJECT_SOURCE_DIR}/source/jtk/core/CString.c
    ${PROJECT_SOURCE_DIR}/source/jtk/core/CStringObjectAdapter.c
    ${PROJECT_SOURCE_DIR}/source/jtk/core/DefaultErrorHandler.c
    ${PROJECT_SOURCE_DIR}/source/jtk/core/Double.c
    ${PROJECT_SOURCE_DIR}/source/jtk/core/Float.c
    ${PROJECT_SOURCE_DIR}/source/jtk/core/Integer.c
    ${PROJECT_SOURCE_DIR}/source/jtk/core/PointerObjectAdapter.c
    ${PROJECT_SOURCE_DIR}/source/jtk/core/String.c
    ${PROJECT_SOURCE_DIR}/source/jtk/core/StringBuilder.c
    ${PROJECT_SOURCE_DIR}/source/jtk/core/StringObjectAdapter.c
    ${PROJECT_SOURCE_DIR}/source/jtk/core/System.c

    # Input/Output Module

    ${PROJECT_SOURCE_DIR}/source/jtk/io/DataInputStream.c

    # TODO: Move this to a separate module.
    ${PROJECT_SOURCE_DIR}/source/jtk/math/Math.c
    ${PROJECT_SOURCE_DIR}/source/jtk/math/DistanceMetric.c
)

set(
    JTK_NATIVE_SOURCE

    ${PROJECT_SOURCE_DIR}/source/linux/com/onecube/jtk/fs/NativeFileHandle.c
    ${PROJECT_SOURCE_DIR}/source/linux/com/onecube/jtk/support/NativeError.c
)

set(
    JTK_CLAP_SOURCE

    ${PROJECT_SOURCE_DIR}/source/jtk/clap/ClapParser.c
)

set(
    JTK_COLLECTION_SOURCE

    ${PROJECT_SOURCE_DIR}/source/jtk/collection/CollectionHelper.c
    ${PROJECT_SOURCE_DIR}/source/jtk/collection/Iterator.c

    ${PROJECT_SOURCE_DIR}/source/jtk/collection/array/Array.c
    ${PROJECT_SOURCE_DIR}/source/jtk/collection/array/ArrayIterator.c
    ${PROJECT_SOURCE_DIR}/source/jtk/collection/array/Arrays.c

    ${PROJECT_SOURCE_DIR}/source/jtk/collection/list/ArrayList.c
    ${PROJECT_SOURCE_DIR}/source/jtk/collection/list/ArrayListIterator.c
    ${PROJECT_SOURCE_DIR}/source/jtk/collection/list/DoublyLinkedList.c
    ${PROJECT_SOURCE_DIR}/source/jtk/collection/list/DoublyLinkedListIterator.c
    ${PROJECT_SOURCE_DIR}/source/jtk/collection/list/DoublyLinkedNode.c

    ${PROJECT_SOURCE_DIR}/source/jtk/collection/map/HashMap.c
    ${PROJECT_SOURCE_DIR}/source/jtk/collection/map/HashMapEntry.c
    ${PROJECT_SOURCE_DIR}/source/jtk/collection/map/HashMapEntryIterator.c
    ${PROJECT_SOURCE_DIR}/source/jtk/collection/map/HashMapKeyIterator.c
    ${PROJECT_SOURCE_DIR}/source/jtk/collection/map/HashMapValueIterator.c
    ${PROJECT_SOURCE_DIR}/source/jtk/collection/map/RBTreeMap.c
    ${PROJECT_SOURCE_DIR}/source/jtk/collection/map/RBTreeMapEntry.c

    ${PROJECT_SOURCE_DIR}/source/jtk/collection/queue/ArrayQueue.c
    ${PROJECT_SOURCE_DIR}/source/jtk/collection/queue/LinkedQueue.c

    ${PROJECT_SOURCE_DIR}/source/jtk/collection/stack/ArrayStack.c
    ${PROJECT_SOURCE_DIR}/source/jtk/collection/stack/LinkedStack.c
)

set(
    JTK_FS_SOURCE

    ${PROJECT_SOURCE_DIR}/source/jtk/fs/PathHandle.c
    ${PROJECT_SOURCE_DIR}/source/jtk/fs/Path.c
    ${PROJECT_SOURCE_DIR}/source/jtk/fs/FileInputStream.c
)

set(
    JTK_HOKUM_SOURCE

    ${PROJECT_SOURCE_DIR}/source/jtk/hokum/Tape.c
)

set(
    JTK_IO_SOURCE

    ${PROJECT_SOURCE_DIR}/source/jtk/io/BufferedInputStream.c
    ${PROJECT_SOURCE_DIR}/source/jtk/io/DataInputStream.c
    ${PROJECT_SOURCE_DIR}/source/jtk/io/InputStream.c
    ${PROJECT_SOURCE_DIR}/source/jtk/io/InputStreamHelper.c
)

set(
    JTK_LOG_SOURCE

    ${PROJECT_SOURCE_DIR}/source/jtk/log/Logger.c
    ${PROJECT_SOURCE_DIR}/source/jtk/log/LogRecord.c
)

set(
    JTK_UNIT_SOURCE

    ${PROJECT_SOURCE_DIR}/source/jtk/unit/ConsoleProgressListener.c
    ${PROJECT_SOURCE_DIR}/source/jtk/unit/SimpleProgressListener.c
    ${PROJECT_SOURCE_DIR}/source/jtk/unit/TestCase.c
    ${PROJECT_SOURCE_DIR}/source/jtk/unit/TestDefect.c
    ${PROJECT_SOURCE_DIR}/source/jtk/unit/TestFixture.c
    ${PROJECT_SOURCE_DIR}/source/jtk/unit/TestListener.c
    ${PROJECT_SOURCE_DIR}/source/jtk/unit/TestManager.c
    ${PROJECT_SOURCE_DIR}/source/jtk/unit/TestSuite.c
)

# Compile

set(CMAKE_VERBOSE_MAKEFILE off)

add_library(
    jtk-core

    ${JTK_CORE_SOURCE}
    ${JTK_COLLECTION_SOURCE}
    ${JTK_LOG_SOURCE}
    ${JTK_IO_SOURCE}
    ${JTK_HOKUM_SOURCE}
    ${JTK_UNIT_SOURCE}
    ${JTK_CLAP_SOURCE}
    ${JTK_NATIVE_SOURCE}
    ${JTK_FS_SOURCE})

# target_compile_options(jtk-core PUBLIC -Wall -g)
target_compile_options(jtk-core PUBLIC -w -g)

# add_library(jtk-collection ${JTK_COLLECTION_SOURCE})
# target_compile_options(jtk-collection PUBLIC -Wall -Wswitch -g)
# target_compile_options(jtk-collection PUBLIC -w -g)
# target_link_libraries(jtk-collection jtk-core)

# add_library(jtk-log ${JTK_LOG_SOURCE})
# target_compile_options(jtk-log PUBLIC -Wall -Wswitch -g)
# target_compile_options(jtk-log PUBLIC -w -g)
# target_link_libraries(jtk-log jtk-core jtk-collection)

# add_library(jtk-unit ${JTK_UNIT_SOURCE})
# target_compile_options(jtk-collection PUBLIC -Wall -Wswitch -g)
# target_compile_options(jtk-collection PUBLIC -w -g)
# target_link_libraries(jtk-unit jtk-core jtk-collection)

# File Configuration

set(JTK_PC "${CMAKE_CURRENT_BINARY_DIR}/jtk.pc")
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/share/jtk.pc.cmakein" ${JTK_PC} @ONLY)

#******************************************************************************#
# Example                                                                      #
#******************************************************************************#

set(
    EXAMPLE_UNIT_NUMBER_SOURCE
    ${PROJECT_SOURCE_DIR}/example/unit/Number/Main.c
    ${PROJECT_SOURCE_DIR}/example/unit/Number/Number.c
)
add_executable(number ${EXAMPLE_UNIT_NUMBER_SOURCE})
target_link_libraries(number jtk-core)
# target_link_libraries(number jtk-collection)
# target_link_libraries(number jtk-unit)

set(
    EXAMPLE_FS_READ_SOURCE
    ${PROJECT_SOURCE_DIR}/example/fs/Read/read.c
)
add_executable(read ${EXAMPLE_FS_READ_SOURCE})
target_link_libraries(read jtk-core)
# target_link_libraries(number jtk-collection)
# target_link_libraries(number jtk-unit)

set(
    EXAMPLE_COLLECTION_NAMES_SOURCE
    ${PROJECT_SOURCE_DIR}/example/collection/names/Names.c
)
add_executable(names ${EXAMPLE_COLLECTION_NAMES_SOURCE})
target_link_libraries(names jtk-core)
# target_link_libraries(names jtk-collection)

#******************************************************************************#
# Unit Tests                                                                   #
#******************************************************************************#

include_directories("${PROJECT_SOURCE_DIR}/test/include")

set(
    JTK_UNIT_TEST_SOURCE
    ${PROJECT_SOURCE_DIR}/test/source/Main.c
    ${PROJECT_SOURCE_DIR}/test/source/com/jtk/collection/list/ArrayListTest.c
)
add_executable(jtk-test ${JTK_UNIT_TEST_SOURCE})
target_link_libraries(jtk-test jtk-core)
# target_link_libraries(jtk-test jtk-collection)
# target_link_libraries(jtk-test jtk-unit)

# File Configuration

set (JTK_PC "${CMAKE_CURRENT_BINARY_DIR}/jtk.pc")
configure_file (${CMAKE_CURRENT_SOURCE_DIR}/share/jtk.pc.cmakein ${JTK_PC} @ONLY)

# Installer

install(TARGETS jtk-core ARCHIVE DESTINATION ${JTK_INSTALL_LIBRARY_DIR})
install(DIRECTORY "${PROJECT_SOURCE_DIR}/include/" DESTINATION ${JTK_INSTALL_INCLUDE_DIR} FILES_MATCHING PATTERN "*.h")
install(FILES ${JTK_PC} DESTINATION ${JTK_INSTALL_PKGCONFIG_DIR})