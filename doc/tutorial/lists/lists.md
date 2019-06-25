# Lists

A list is an abstract data type that represents a sequence of values, where the
same value may occur more than once.

Apart from the general operations of a value collection, lists provide functions to
insert and delete elements based on indexes.

## Array List

The `ArrayList` class is a part of the **Collection Module**. It is declared in
the `jtk/collection/list/ArrayList.h` header file.

The `ArrayList` class represents a list backed by an array. The internal
array grows and shrinks as needed. As of this version, no interface is
provided to extract a reference to the internal array (although an interface
to obtain a copy is provided).

It is used to store dynamically sized collection of elements. Contrary to arrays
that are fixed in size, an `ArrayList` grows and shrinks its size automatically
when new elements are added and removed from it, respectively.

You can invoke the `jtk_ArrayList_new()` function to create an instance of
the `ArrayList` class. Please refer the documentation for other methods.
```
jtk_ArrayList_t* cars = jtk_ArrayList_new();
```

### Elements in ArrayList

The `ArrayList` class provides fast random access with error checking, when
assertions are enabled. An element is accessed by its integer index, the
position in the list. An attempt to access an element with an invalid index,
results in an assertion failure, if enabled. The indexes of a list are
of the form `0, 1, 2, 3, 4, 5, 6, 7, ... n - 1`, where `n` is the size of the
list. The first item of the sequence is at index `0`, the next at index `1`, and
so on. Thus, for a list containing ten elements, the valid indexes range from
`0` (inclusive) to `10` (exclusive).

The `jtk_ArrayList_add()` function adds an element to the end of the list.
Let's add a hundred elements to the list we created above.
```
int32_t i;
for (i = 0; i < 100; i++) {
    xyz_Car_t* car = xyz_Car_new(...);
    jtk_ArrayList_add(cars, car);
}
```

You can retrieve the elements via `jtk_ArrayList_getValue()` function. You need
to specify the list in which the element is stored and the index of the element.
```
int32_t j;
int32_t size = jtk_ArrayList_getSize(cars);
for (j = 0; j < size; j++) {
    xyz_Car_t* car = (xyz_Car_t*)jtk_ArrayList_getValue(cars, j);
    ...
}
```

### Capacity of ArrayList

The size of the internal array represents the capacity of the list, not
the size of the list. A simple interface is provided to manipulate the
capacity. The capacity is always greater or equal to the size of the list.
Further, it is automatically adjusted as needed. It may grow or shrink
contingent on the size of the list.

You can retrieve the current capacity of the list by invoking `jtk_ArrayList_getCapacity()`
function.
```
int32_t capacity = jtk_ArrayList_getCapacity(cars);
printf("The current capacity of the list is %d.\n", capacity);
```

### Attaching ObjectAdapter to ArrayList

Optionally, an `ObjectAdapter` may be attached to the list. The adapter
helps the implementation adapt elements as objects. Custom implementations
of algorithms for converting elements to strings, computing hashes, etc.
may be provided. If an `ObjectAdapter` is absent, the implementation falls
back to the default hard coded algorithms. Please refer to the documentation
of specific functions which employ the `ObjectAdapter` for more information.
As of this version, the `ObjectAdapter` should be initialized during the
creation of the list. This behaviour may become less rigid in the future
releases.

Here's an example of creating an `ArrayList` with `StringObjectAdapter`.
The `StringObjectAdapter` is declared in the `jtk/core/StringObjectAdapter.h`
header file.
```
jtk_ArrayList_t* list = jtk_ArrayList_newWithAdapter(jtk_StringObjectAdapter_getInstance());
```

### Obtaining Iterator from ArrayList

An iterator can be obtained for an instance of the `ArrayList` class.

Let's create an array list. We will obtain an iterator for it.
```
jtk_ArrayList_t* students = jtk_ArrayList_new(10);
```

Fill the array list with objects.
```
int32_t i;
for (i = 0; i < 10; i++) {
    xyz_Student_t* student = xyz_Student_new(...);
    jtk_ArrayList_add(students, student);
}
```

We can now obtain an iterator to traverse the elements. Always remember to destroy
an iterator you obtain.
```
jtk_Iterator_t* iterator = jtk_ArrayList_getIterator(students);
while (jtk_Iterator_hasNext(iterator)) {
    xyz_Student_t* student = (xyz_Student_t*)jtk_Iterator_getNext(iterator);
    ...
}
jtk_Iterator_delete(iterator);
```

The source iterator for the `ArrayList` class is situated in the
`jtk/collection/list/ArrayListIterator.h` header file.
```
jtk_ArrayList_t* list = jtk_ArrayList_new();
jtk_ArrayListIterator_t* listIterator = jtk_ArrayListIterator_new(list);
jtk_Iterator_t* iterator = jtk_ArrayListIterator_getIterator(listIterator);
while (jtk_Iterator_hasNext(iterator)) {
    ...
}
```

### ArrayList Synchronization Policy

The `ArrayList` class is intended to be used by a single thread. It does not
implement a thread synchronization policy. In other words, it is not thread
safe. Concurrent invocation of a function against an instance without an
external synchronization results in undefined behaviour.

## Doubly-linked List

The `DoublyLinkedList` class is a part of the **Collection Module**. It is declared in
the `jtk/collection/list/DoublyLinkedList.h` header file.

The `DoublyLinkedList` class represents a list backed by linked nodes. Each node
in the list contains an element, along with pointers which link to the previous
node and the next node in the list. These pointers allow us to navigate through
the list in both directions. Unlike the doubly-linked list, a singly-linked list
only allows navigation in the forward direction. As of version 1.0, the singly-linked
list is not implemeted. We intend to implement in the future releases. 

You can invoke the `jtk_DoublyLinkedList_new()` function to create an instance of
the `DoublyLinkedList` class. Please refer the documentation for other methods.
```
jtk_DoublyLinkedList_t* cars = jtk_DoublyLinkedList_new();
```

### Elements in DoublyLinkedList

The DoublyLinkedList class *does not provide fast random access* to elements.
Although error checking is implemented, only when assertions are enabled.

An element is accessed by its integer index, the position in the list.
An attempt to access an element with an invalid index, usually, results in
assertion failure. The indexes of a list are of the form
`0, 1, 2, 3, 4, 5, 6, 7, ... n - 1`, where `n` is the size of the list. The
first item of the sequence is at index `0`, the next at index `1`, and so on.
Thus, for a list containing ten elements, the valid indexes range from
`0` (inclusive) to `10` (exclusive).

The `jtk_DoublyLinkedList_add()` function adds an element to the end of the list.
It is equivalent to `jtk_DoublyLinkedList_addLast()`. Let's add a hundred elements
to the list we created above.
```
int32_t i;
for (i = 0; i < 100; i++) {
    xyz_Car_t* car = xyz_Car_new(...);
    jtk_DoublyLinkedList_addLast(cars, car);
}
```

In a similar fashion, you can add elements to the beginning of the list by
invoking `jtk_DoublyLinkedList_addFirst()`. Let's add another hundred elements
to the list we created above.
```
for (i = 0; i < 100; i++) {
    xyz_Car_t* car = xyz_Car_new(...);
    jtk_DoublyLinkedList_addFirst(cars, car);
}
```

You can retrieve the elements via `jtk_DoublyLinkedList_getValue()` function.
You need to specify the list in which the element is stored and the index of
the element.
```
int32_t j;
int32_t size = jtk_DoublyLinkedList_getSize(cars);
for (j = 0; j < size; j++) {
    xyz_Car_t* car = (xyz_Car_t*)jtk_DoublyLinkedList_getValue(cars, j);
    ...
}
```

You can invoke the `jtk_DoublyLinkedList_getFirst()` and `jtk_DoublyLinkedList_getLast()`
functions to retrieve the first and last elements, respectively.

### Attaching ObjectAdapter to DoublyLinkedList

Optionally, an `ObjectAdapter` may be attached to the list. The adapter
helps the implementation adapt elements as objects. Custom implementations
of algorithms for converting elements to strings, computing hashes, etc.
may be provided. If an `ObjectAdapter` is absent, the implementation falls
back to the default hard coded algorithms. Please refer to the documentation
of specific functions which employ the `ObjectAdapter` for more information.
As of this version, the `ObjectAdapter` should be initialized during the
creation of the list. This behaviour may become less rigid in the future
releases.

Here's an example of creating an `DoublyLinkedList` with `StringObjectAdapter`.
The `StringObjectAdapter` is declared in the `jtk/core/StringObjectAdapter.h`
header file.
```
jtk_DoublyLinkedList_t* list = jtk_DoublyLinkedList_newWithAdapter(jtk_StringObjectAdapter_getInstance());
```

### Obtaining Iterator from DoublyLinkedList

An iterator can be obtained for an instance of the `DoublyLinkedList` class.

Let's create an array list. We will obtain an iterator for it.
```
jtk_DoublyLinkedList_t* students = jtk_DoublyLinkedList_new(10);
```

Fill the array list with objects.
```
int32_t i;
for (i = 0; i < 10; i++) {
    xyz_Student_t* student = xyz_Student_new(...);
    jtk_DoublyLinkedList_add(students, student);
}
```

We can now obtain an iterator to traverse the elements. Always remember to destroy
the iterator you obtain.
```
jtk_Iterator_t* iterator = jtk_DoublyLinkedList_getIterator(students);
while (jtk_Iterator_hasNext(iterator)) {
    xyz_Student_t* student = (xyz_Student_t*)jtk_Iterator_getNext(iterator);
    ...
}
jtk_Iterator_delete(iterator);
```

The source iterator for the `DoublyLinkedList` class is situated in the
`jtk/collection/list/DoublyLinkedListIterator.h` header file.
```
jtk_DoublyLinkedList_t* list = jtk_DoublyLinkedList_new();
jtk_DoublyLinkedListIterator_t* listIterator = jtk_DoublyLinkedListIterator_new(list);
jtk_Iterator_t* iterator = jtk_DoublyLinkedListIterator_getIterator(listIterator);
while (jtk_Iterator_hasNext(iterator)) {
    ...
}
```

### DoublyLinkedList Synchronization Policy

The `DoublyLinkedList` class is intended to be used by a single thread. It does not
implement a thread synchronization policy. In other words, it is not thread
safe. Concurrent invocation of a function against an instance without an
external synchronization results in undefined behaviour.