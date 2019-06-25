# Arrays

An array is a sequential collection of similar type of elements that have
contiguous memory location. JTK supports two types of arrays.
    * Native Array
    * Wrapper Array

## Native Arrays

To avoid confusion, the documentation refers to instances of the `Array`
class as "arrays" and native arrays provided by the C programming language as
"raw arrays" or "native arrays" when needed. Otherwise, please try to resolve
the meaning with respect to the context in which we refer.

## Wrapper Arrays

The `Array` class represents an ordered sequence of objects of the same type,
known as its component type. In order to be flexible, the `Array` class accepts
`void*` pointers only. It is the responsibility of the programmer to code with
appropriate data types. Each item of an array is called an element.

It is a part of the **Collection Module**. It is declared in the 
`jtk/collection/array/Array.h` header file. An instance of the `Array` class
is of the type `jtk_Array_t`.

An `Array` has a _fixed_ size that is set when the array is constructed. The size
determines the number of elements that can be stored in the array. Please
refer [ArrayList](/jtk/tutorial/lists#array-list) for _dynamically growing arrays_.

The following example illustrates the creation of an array with twenty elements.

```
#include <jtk/collection/array/Array.h>

int32_t main() {
    jtk_Array_t* array = jtk_Array_new(20);
    ...
}
```

The `Array` class provides fast random access with error checking. An element
is accessed by its integer index, the position in the array. An attempt to
access an element with an invalid index results in an assertion failure,
if enabled. The indices of an array are of the form: `0, 1, 2, 3, 4,
5, 6, 7, ... n - 1`, where `n` is the size of the array. The first item of the 
sequence is at index `0`, the next at index `1`, and so on. Thus, for an array
of ten elements, the valid indices range from `0` (inclusive) to `10` (exclusive).

```
#include <jtk/collection/array/Array.h>

...

int32_t main() {
    /* Create an array capable of storing ten elements. */
    jtk_Array_t* students = jtk_Array_new(10);
    
    int32_t i;
    for (i = 0; i < 10; i++) {
        /* Create a new student. */
        xyz_Student_t* student = xyz_Student_new(i);
        /* Store the newly created student in the array. */
        jtk_Array_setValue(students, i, student);
    }
    
    for (i = 0; i < 10; i++) {
        /* Retrieve the student at the current index. */
        xyz_Student_t* student = (xyz_Student_t*)jtk_Array_getValue(students, i);
        /* Destroy the student object. */
        xyz_Student_delete(student);
    }
    
    /* Destroy the students array. */
    jtk_Array_delete(students);
    
    return 0;
}
```

Moreover, the `Array` class is provided as an alternative to raw arrays.
Where using a raw array would result in undefined behaviour, as specified by
the C standard, using the `Array` class would result in assertion failures, if
enabled.

Unlike native arrays, the `Array` class initializes all the elements to `NULL`
on creation.

```
/* Create a new array capable of storing ten elements. */
jtk_Array_t* array = jtk_Array_new(10);

/* Even though we have not initialized the array, we retrieve the element
 * at 0th index.
 */
void* element = jtk_Array_getValue(array, 0);

/* We determine whether the retrieved element is null, or not. */
bool isNull = element == NULL;

/* Print whether the retrieved element is null, or not. */
printf("%s\n",  isNull? "NULL" : "Not NULL");
```

## Array Helper

There are situations where we need to fill an array with a particular value,
fill a section of an array with a particular value, search an array, copy an
array, etc. The `Arrays` class provides many functions which implement such
operations on native arrays. Equivalent functions which operate on an instance
of the `jtk_Array_t` structure are provided by the `Array` class.

This class is a member of the `Collection` module and is present
in the `jtk/collection/array/Arrays.h` header file. There is no type
associated with this class.

### Binary Search

Create a simple array of integers. The binary search algorithm requires the
input array to be sorted.
```
int32_t array[] = { 10, 20, 30, 40, 50, 60, 70 };
```

Look for an element which does not exist. This should cause the `jtk_Arrays_binarySearch_i()`
function to return a negative integer.

```
int32_t i1 = jtk_Arrays_binarySearch_i(array, 7, 53);
printf("Index 1 = %d\n", i1);
```

Look for an element which exists. This should return `2`.

```
int32_t i2 = jtk_Arrays_binarySearch_i(array, 7, 30);
printf("Index 2 = %d\n", i2);
```

Look for an element within a specific range. The arguments are as follows:
the array in which we search for the element, the size of the array,
the starting index of the range, the stopping index of the range, and
the element we are looking for. The function should return `1`.

```
int32_t i3 = jtk_Arrays_binarySearchEx_i(array, 7, 0, 2, 20);
printf("Index 3 = %d\n", i3);
```

### Cloning Arrays

Create a simple array of integers. We will create clones of this array.
```
int32_t array[] = { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 };
```

Invoking the `jtk_Arrays_clone_*()` function should return a newly created array
containing the elements contained in the source array. The order of the
elements corresponds to the order of the elements in the source array.

``` 
int32_t* clone1 = jtk_Arrays_clone_i(array, 10);
```

Since, the `jtk_Arrays_clone_*()` function does not know the actual size of the
source array, we can exploit this to truncate arrays. For example, the following
line truncates the source array containing ten elements to create a clone with
just five elements. Only the first five elements are retained.

```
int32_t* clone2 = jtk_Arrays_clone_i(clone1, 5);
```

It is the responsibility of the user to destroy the cloned arrays. The
`jtk_Memory_deallocate()` is equivalent to `free()` function defined in the
C standard library. We recommend you to invoke jtk_Memory_deallocate() to
destroy an object when the object was previously allocated via `jtk_Memory_allocate()`.
All classes in JTK invoke `jtk_Memory_allocate()` to create objects.

```
jtk_Memory_deallocate(clone1);
jtk_Memory_deallocate(clone2);
```

### Copying Arrays

Create a simple array of integers. We will copy this array to another array.
```
int32_t source[] = { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 };
```

Invoking the `jtk_Arrays_copy_*()` function should copy all the elements from
the source array to the destination array. The arguments are as follows:
the source array, the size of the source array, the destination array, and the
size of the destination array.
```
int32_t destination1[10];
jtk_Arrays_copy_i(source, 10, destination, 10);
```
The `destination1` array should now contain `{ 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 }`.

Since the `jtk_Arrays_copy_*()` function does not know the actual size of the
source array and destination array, we can adjust the arguments to exploit the
function to truncate arrays as needed.

```
int32_t destination2[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
jtk_Arrays_copy_i(source, 10, destination2, 5);
```

This `destination2` array should now contain `{ 10, 20, 30, 40, 50, 0, 0, 0, 0, 0 }`.

### Extended Copying of Arrays

The extended version of the `jtk_Arrays_copy_*()` allows the user to copy a specific
range of elements from the source array. The elements can be copied at a specific
index within the destination array.

Create a simple array of integers. We will copy a specific range of this array
into another array.
```
int32_t source[] = { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 };
```

Invoking the `jtk_Arrays_copyEx_*()` function should copy a specific range of
the elements from the source array into the destination array. The elements are
copied at the specified index. The arguments are as follows: the source array,
the size of the source array, the starting index into the source array from where
the elements are copied, the destination array, and the size of the destination
array, the index into the destination array where the elements are copied, and
the size of the range.
```
int32_t destination1[10];
jtk_Arrays_copyEx_i(source, 10, 2, destination, 10, 2, 4);
```
The `destination1` array should now contain `{ 0, 0, 30, 40, 50, 60, 0, 0, 0, 0 }`.

### Comparing Arrays for Equality

Create two arrays of integers. We will compare them for equality.
```
int32_t array1[] = { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 };
int32_t array2[] = { 15, 25, 35, 45, 50, 60, 70, 80, 90, 100 };
```

Let's invoke the `jtk_Arrays_equals_*()` function to determine whether `array1`
and `array2` are equal, or not. The arguments are as follows: the first array
involved in the comparison, the size of the first array, the second array involved
in the comparison, and the size of the second array.
```
if (jtk_Arrays_equals_i(array1, 10, array2, 10)) {
    printf("The arrays are equal.\n");
}
else {
    printf("The arrays are not equal.\n");
}
```


Two arrays are considered equal if both arrays contain the same number of elements,
and all corresponding elements in the two arrays are equal, as determined by
comparison operators, this applies to integers and decimals only. For comparing
arrays of objects, a reference to an user define comparator function should be
passed.

The example above should generate the output `The arrays are not equal.`

## Array Iterator

An `Iterator` is a class available in the **Collection Module**. It
is declared in the `jtk/collection/Iterator.h` header file. Please refer [Iterators](/jtk/tutorial/collections#iterator)
for more details.

An iterator can be obtained for an instance of the `Array` class. In the case of
native arrays, only arrays of void pointers (`void**`) support iterators.

Let's create an instance of the `Array` class.
```
jtk_Array_t* students = jtk_Array_new(10);
```

Fill the array with objects.
```
int32_t i;
for (i = 0; i < 10; i++) {
    xyz_Student_t* student = xyz_Student_new(...);
    jtk_Array_setValue(students, i, student);
}
```

We can now obtain an iterator to traverse the elements. Always remember to destroy
an iterator you obtain.
```
jtk_Iterator_t* iterator = jtk_Array_getIterator(students);
while (jtk_Iterator_hasNext(iterator)) {
    xyz_Student_t* student = (xyz_Student_t*)jtk_Iterator_getNext(iterator);
    ...
}
jtk_Iterator_delete(iterator);
```

The source iterator for the `Array` class is situated in the
`jtk/collection/array/ArrayIterator.h` header file.

```
jtk_Array_t* array = jtk_Array_new(...);
jtk_ArrayIterator_t* arrayIterator = jtk_ArrayIterator_new(array);
jtk_Iterator_t* iterator = jtk_ArrayIterator_getIterator(arrayIterator);
while (jtk_Iterator_hasNext(iterator)) {
    ...
}
```