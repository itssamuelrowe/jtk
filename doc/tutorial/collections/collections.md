# Collections

The **Collections Module** in JTK is designed to provide simple interfaces to
store and manipulate group of objects. All the header files in this module are
located in the `jtk/collection` directory.

All operations on data such such as search, sort, insertion, manipulation,
deletion etc. can be performed by collections. This module provides
many classes such as `Array`, `ArrayList`, `DoublyLinkedList`, `HashMap`, etc.

Collections are divided into two categories.
    * Value Collections
    * Key-Value Collections
    
## Value Collections

A value collection is a group of values known as elements. General operations
such as retrieval, insertion, deletion, etc. are independent. In other words,
a general operation on a value does not depend on any other object. Collections
such as `Array`, `ArrayList`, and `DoublyLinkedList` belong to this type.

## Key-Value Collections

A key-value collection is a group of key-value pairs known as entries. General
operations such as retrieval, insertion, deletion, etc. are dependent. In other
words, a general operation on a value may depend on an associated key. Some key-value
collections extend this behaviour to reverse the roles, that is, a general operation
on a key may depend on an associated value. Collections such as `HashMap`,
`RBTreeMap`, and `HashSet` belong to this type.

## Object Adapter

Some operations such as sorting, searching, removing, etc. on a collection
require comparisons between the members of the collection and the target object.
Some other operations such as generating the string equivalent of a
collection requires the translation of its members into a string. Due to the
inherent nature of the C programming language, a general interface for delegating
such mundane operations is necessary.

Here, we adopt an Object Oriented Programming (OOP) _design pattern_ known
as the *Object Adapter Design Pattern*. It uses composition and can wrap classes
or interfaces (we are refering to the OOP concepts of class and interface), or both.
It can do this since it contains, as a private encapsulated member, the class or
interface object instance it wraps.

The Object Adapter Design Pattern is too verbose for our purpose. Therefore,
we modified this design pattern into what we call *Funnel Object Adapter Design Pattern*.
Basically, an object called the *funnel object adapter* is attached to a *driver*.
A driver is an object which requires a *client* object to be adapted
temporarily. A client object may be any object that is related to the driver, where
the relationship is defined by the driver. For each client adaptation, the driver
requests the associated funnel object adapter. Thus, multiple objects can be adapted
by a single funnel object adapter.

In JTK, the *funnel object adapter* is represented by the `jtk_ObjectAdapter_t`
structure. It consists of function pointers which act as *virtual functions*.
When a client object needs to be adapted, the appropriate function pointer is
invoked. As of version 1.0, JTK is bundled with two funnel object adapters,
`StringObjectAdapter` and `PointerObjectAdapter`. We intend to write more
object adapters in the future releases.

Every collection in JTK provides an interface to attach an object adapter, usually
during construction. Attaching an object adapter to a collection is optional.
Although, some key-value collections require object adapters compulsorily.
Please refer to the documentation of the concerned class for more information.

## Iterator

An `Iterator` is a class available in the **Collection Module**. It
is declared in the `jtk/collection/Iterator.h` header file. An instance of the
`Iterator` class is of the type `jtk_Iterator_t`.

For the sake of this documentation, when we say *iterator* we mean an object
which provides a common iterface for extracting data from a *source iterator*.
A source iterator is an object which extracts data from an underlying source
such as `ArrayList`, `DoublyLinkedList`, etc.

Every iterator has a lifecycle. Unlike other objects with lifecycle, an 
iterator does not notify listeners regarding its states. An iterator is
created by a source iterator when the latter is created.

When an element is requested (i.e., the next element), the iterator
delegates the task of extracting the element to the associated source
iterator. Although the source iterator may provide a direct interface
to extract elements, we recommend you to avoid using the source iterator
directly.

The iterator and the source iterator maintain a bidirectional ownership.
The pair is always created and destroyed together. The user is required
to create only the source iterator. After creation, a bidirectional ownership
is established. The user may destroy either the iterator or the source
iterator. But not both the iterator and the source iterator.

Internally, the iterator and source iterator communicate through the
availibility of the `m_destroy` function pointer within the `jtk_Iterator_t`
structure. When the destructor of the iterator is invoked, the iterator invokes
the `m_destroy` function, if available. The `m_destroy` function
unreferences any references made to the iterator from the internal data
structure of the source iterator. After which, the destructor is invoked
against the source iterator.

Similarly, when the destructor of the source iterator is invoked directly, the
reference to the `m_destroy` function pointer within the `jtk_Iterator_t`
structure is unreferenced before invoking the destructor against the
iterator.

Thus, in both the scenarios, the destructors of the source iterator and iterator
are invoked only once.

In the following example, we obtan an iterator from an `ArrayList`.
```
jtk_ArrayList_t* list = jtk_ArrayList_new();
```

For the sake of simplicity, let's assume that the array list has been populated
with a handful of elements. In the next step, we proceed to obtain an iterator.
```
jtk_Iterator_t* iterator = jtk_ArrayList_getIterator(list);
```

Internally, the obtained iterator is associated with a source iterator. We don't
have to bother ourselves with the source iterator. We can now traverse each
element by invoking `jtk_Iterator_getNext()` function in a loop. The loop has
to terminate when the iterator is empty. We can invoke the `jtk_Iterator_hasNext()`
function to determine whether the iterator has more elements, or not.
```
while (jtk_Iterator_hasNext(iterator)) {
    void* element = jtk_Iterator_getNext(iterator);
    ...
}
```

Always remember to destroy the iterator you obtain. We have already discussed
the internal algorithm involved in destroying an iterator. Further, do not
destroy the source of an iterator before destroying the iterator because the
iterator references the source internally. For instance, in the example above
you must destroy the iterator before destroying the array list and not the other
way around!
```
jtk_Iterator_delete(iterator);
jtk_ArrayList_delete(list);
```