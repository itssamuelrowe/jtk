# Unit Tests

The objective of unit testing is to isolate a section of code and verify its
correctness.

The user has to write the unit tests just once. The **Unit Test Module** automatically runs
these tests and verifies their correctness. You can run your tests whenever you
are in doubt without any effort.

## Test Case

We represent each test case as an object. A test case has a name, a target function,
and a fixture (which is optional).

The `TestCase` class is a part of the **Unit Test Module**. It is declared in the
`jtk/unit/TestCase.h` header file.

You can invoke the `jtk_TestCase_new()` function to create a test case. The arguments
are as follows: the name of the test case, the fixture (which is optional), and the
target function which performs the assertions.
```
jtk_TestCase_t* testCase = jtk_TestCase_new("testEqualityOperatorWhenOperandsAreEqual",
    NULL, testEqualityOperatorWhenOperandsAreEqual);
```

## Assertion

An assertion verifies the correctness of an isolated section of code. Every
assertion has an expected condition which is compared to the actual condition.
When an assertion fails, it indicates that the test case has effectively failed.
This causes the control to jump back to the *invoker*. Thus, subsequent
statements in the target function are skipped. Which means, you should not
allocate any resources within the target function. Please refer the section
*Test Fixtures* where we learn how to balance allocation and deallocation
of resources.

The `TestCase` class provides a plethora of functions to assert various conditions.
Please refer the documentation for more information.

In the `testEqualityOperatorWhenOperandsAreEqual` test case, we assert that
two equal operands compared by the equality operator should result in `true`.
```
void testEqualityOperatorWhenOperandsAreEqual(jtk_TestCase_t* testCase, void* bundle) {
    jtk_TestCase_assertTrue(testCase, 272000 == 272000);
}
```

## Test Fixture

A test case requires certain resources to operate. Such resources are known
as *fixture*.

The `TestFixture` class provides a convenient place to create and destroy fixtures. 
In other words, the framework notifies your code when a fixture needs to be *set-up*.
Simiarly, the framework notifies your code when a fixture needs to be *torn down*.
Thus, you can balance allocation and deallocation of your resources.

Usually, test cases are quite small. Many test cases require a common set of
objects. We recommend you to bundle fixtures into resuable components.

The following code snippets were extracted from the unit tests written for the
`ArrayList` class.

```
jtk_TestCase_t* testCase =
    jtk_TestCase_new("testIsEmptyAfterClearing", jtk_ArrayListTest_getFixture(),
    (jtk_TestCaseTargetFunction_t)jtk_ArrayListTest_testIsEmptyAfterClearing);
```

A bundle is an user defined object in which we store all the resources. The
bundle is stored in the fixture. The `TestFixture` allows you to specify
a bundle during the creation of a fixture. But we recommend you to create
the bundle during set-up.
```
/* Bundle */

jtk_ArrayListBundle_t* jtk_ArrayListBundle_new() {
    jtk_ArrayListBundle_t* bundle = jtk_Memory_allocate(jtk_ArrayListBundle_t, 1);
    bundle->m_list = jtk_ArrayList_new();

    return bundle;
}

void jtk_ArrayListBundle_delete(jtk_ArrayListBundle_t* bundle) {
    jtk_ArrayList_delete(bundle->m_list);
    jtk_Memory_deallocate(bundle);
}

/* Fixture */

void jtk_ArrayListTest_setUp(jtk_TestFixture_t* fixture) {
    jtk_ArrayListBundle_t* bundle = jtk_ArrayListBundle_new();
    jtk_TestFixture_setBundle(fixture, bundle);
}

void jtk_ArrayListTest_tearDown(jtk_TestFixture_t* fixture) {
    jtk_ArrayListBundle_t* bundle = jtk_TestFixture_getBundle(fixture);
    jtk_ArrayListBundle_delete(bundle);
}

jtk_TestFixture_t* jtk_ArrayListTest_getFixture() {
    return jtk_TestFixture_new(jtk_ArrayListTest_setUp, jtk_ArrayListTest_tearDown, NULL);
}
```

Now, the test case can access the resources via the bundle.

```
void jtk_ArrayListTest_testIsEmptyAfterClearing(jtk_TestCase_t* testCase,
    jtk_ArrayListBundle_t* bundle) {
    
    jtk_ArrayList_clear(bundle->m_list);
    jtk_TestCase_assertTrue(testCase, jtk_ArrayList_isEmpty(bundle->m_list));
}
```

## Test Suite

In real world applications, we need the ability to manipulate multiple test cases
at once. All the examples shown until now are invidual moving parts. For example,
if you have ten test cases, you have to individually run each of them! Our challenge
here is to extend this to group multiple test cases, so we can perform batch
operations.

We compose test cases into tree structures to represent part or whole hierarchies.
We can compose other compositions into these tree structures to extend our
functionality. The composition of tests and other compositions into tree structures
is known as test suites.


The `TestSuite` class is a part of the **Unit Test Module**. It is declared in the
`jtk/unit/TestSuite.h` header file.

You can invoke the `jtk_TestSuite_new()` function to create a test suite. 

```
jtk_TestSuite_t* suite = jtk_TestSuite_new("ArrayListTest");
```

You can add test cases to a test suite via `jtk_TestSuite_addCase()`.
```
jtk_TestCase_t* testCase1 =
    jtk_TestCase_new("testIsEmptyAfterClearing", jtk_ArrayListTest_getFixture(),
    (jtk_TestCaseTargetFunction_t)jtk_ArrayListTest_testIsEmptyAfterClearing);
jtk_TestCase_t* testCase2 =
    jtk_TestCase_new("testGetSizeAfterClearing", jtk_ArrayListTest_getFixture(),
    (jtk_TestCaseTargetFunction_t)jtk_ArrayListTest_testGetSizeAfterClearing);

jtk_TestSuite_addCase(suite, testCase1);
jtk_TestSuite_addCase(suite, testCase2);
```

You can even add test suites to a test suite by invoking `jtk_TestSuite_addSuite()`. 
```
jtk_TestSuite_addSuite(mainSuite, arrayListSuite);
jtk_TestSuite_addSuite(mainSuite, hashMapSuite);
```

## Test Manager

The `TestManager` is a facade for managing tests. You can provide a test suite
and it will run all the test cases recursively, or simply a test case.

You can invoke the `jtk_TestManager_new()` function to create a `TestManager`.
```
jtk_TestManager_t* manager = jtk_TestManager_new();
```

### Running TestSuite

You can run a test suite by invoking `jtk_TestManager_runSuite()`. The test manager
recursively runs every test case in the suite.
```
jtk_TestManager_runSuite(suite);
```

### Running TestCase

You can even run an individual test case by invoking `jtk_TestManager_runCase()`.
```
jtk_TestManager_runCase(testCase);
```

### Attaching TestListener

You can attach listeners to receive notifications regarding the progress of the
tests. Register a test listener by invoking `jtk_TestManager_addTestListener()`.
JTK is packaged with two test listeners: `ConsoleProgressListener` and
`SimpleProgressListener`.
```
jtk_ConsoleProgressListener_t* consoleProgressListener =
    jtk_ConsoleProgressListener_new();
jtk_TestListener_t* listener =
    jtk_ConsoleProgressListener_getTestListener(consoleProgressListener);

jtk_TestManager_addTestListener(manager, listener);
```

### Detaching TestListener

You can detach listeners from a test manager to prevent the listener from
receiving notifications. Unregister a test listener by invoking
`jtk_TestManager_removeTestListener()`.
```
jtk_TestManager_removeTestListener(manager, listener);
```

## Test Listener

### Failures and Errors

We distinguish between two aspects a test case may result in: *failure* and *error*.
A failure is anticipated and checked for with assertions. Errors are unanticipated
problems encountered in a test case, such as division by zero, etc. As of version
1.0, only failures are detected by the framework. We intend to implement detection
of errors in the future releases.