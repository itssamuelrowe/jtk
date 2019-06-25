# Nomenclature

Every component declared within JTK uses a name scheme. It is divided into
three categories:
    * Function Nomeclature
    * Type Nomenclature
    * Function Pointer Type Nomenclature

Please note, in the following chapter we show examples from C++. They are
shown only to explain the analogy. Therefore, you don't have to know C++ to
understand the examples.

## Function Nomeclature

```
jtk_Class_function[_OverloadSuffix]
```

The name of a function is divided into three parts, separated by an underscore:
    * `jtk` - This prefix is added to all the components in JTK. We are simply
      trying to simulate a name space (as in C++) or a package (as in Java).
    * _Class_ - The class in which the function belongs, refer the (Module)[/jtk/tutorial/module] chapter for the definition
      of a class.
    * _function_ - The name of the function.
    * _OverloadSuffix_ - Certain functions within the library are overloaded,
    that is, they perform the same operation but on different data types.
    Such functions share a same name with a unique suffix. This part is optional.
    The suffixes are listed below.

| Suffix          | Type               |
| --------------- | ------------------ |
| v               | `void*`            |
| n               | `boolean`          |
| b               | `byte`             |
| s               | `short`            |
| i               | `integer`          |
| l               | `long`             |
| f               | `float`            |
| d               | `double`           |
| z               | `uint8_t*`         |
| c               | `char`             |
| cz              | `char*`            |

Example (in C++):

```
class TestCase {
public:

    boolean isSuccessful() {
        ...
    }
}
```

The above class translates to the following snippet in C. It follows the naming
scheme as described above.

```
bool jtk_TestCase_isSuccessful(jtk_TestCase_t* testCase) {
    ...
}
```

## Type Nomeclature

```
jtk_Class_t
```

Type is a general term for structures, enumerations, and function pointer types.
This section describes the nomenclature for structures and enumerations only.
For function pointer types see the section [Function Pointer Type Nomeclature](/jtk/tutorial/nomenclature#function-pointer-type-nomenclature).

The name of a data type is divided into three parts, separated by an underscore:
    * `jtk` - This prefix is added to all the components in JTK. We are simply
      trying to simulate a name space (as in C++) or a package (as in Java).
    * _Class_ - The name of the data type.
    * `t` - This suffix indicates that the component is a type. Many data types defined
    by the C standard use this suffix.

Example (in C++):

```
class TestCase {
    ...
};
```

The above class name translates to the following type in C. It follows the naming
scheme as described above.

```
struct jtk_TestCase_t {
    ...
};

/* Assign an alias to 'struct jtk_TestCase_t'. */
typedef struct jtk_TestCase_t jtk_TestCase_t;
```

## Function Pointer Type Nomeclature

```
jtk_Class_NameFunction_t
```

The name of a function pointer type is divided into five parts, separated by an underscore,
except for `Name` and `Function`:
    * `jtk` - This prefix is added to all the components in JTK. We are simply
      trying to simulate a name space (as in C++) or a package (as in Java).
    * _Class_ -  The class in which the function belongs, refer the (Module)[/jtk/tutorial/module] chapter for the definition
      of a class.
    * _Name_ - The name of the function, with the first letter being capital.
    * `Function` - Adding `Function` helps us read easily. For example,
       `jtk_ObjectAdapter_EqualsFunction_t` sounds better than `jtk_ObjectAdapter_Equals_t`,
       at least, that is how we feel.
    * `t` - This suffix indicates that the component is a type. Many data types defined
    by the C standard use this suffix.

Example (in C++):

```
class ObjectAdapter {
public:

    void equals(void* object1, void* object2) {
        ...
    }
};
```

The function `equals` in the above example translates to the following type in C.
It follows the naming scheme as described above.

```
typedef void (*jtk_ObjectAdapter_EqualsFunction_t)(void* object1, void* object2);
```