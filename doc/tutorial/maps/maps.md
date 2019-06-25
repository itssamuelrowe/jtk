# Maps

A map is a collection which associates keys to values. A map cannot contain duplicate
keys. The order of the entries in map depends on the implementation in question.
As of version 1.0, JTK provides only one general-purpose map: `HashMap`.

## Hash Map

The `HashMap` class is a part of the **Collection Module**. It is declared in
the `jtk/collection/map/HashMap.h` header file.

The `HashMap` class represents a map backed by an hash table.

Here's an example of how you can create a hash map. It requires two object
adapters, where one adapts keys and the other adapts values. An adapter for
values is optional, if you are not using any functions which require it.
```
jtk_HashMap_t* map = jtk_HashMap_new(jtk_StringObjectAdapter_getInstance(),
    jtk_StringObjectAdapter_getInstance());
```

### Attaching ObjectAdapters for Adapting Keys and Values

As of this version, an object adapter to adapt keys is necssary. Although,
an object adapter to adapt values is optional. Custom implementations of
algorithms for converting elements to strings, computing hashes, etc. may
be provided. If an object adapter is absent, the implementation fails (to be
precise, results are undefined). This behaviour may change in the future
releases, but mostly not.

Both the adapters should be passed to the constructor. Changing the adapters
after emplacing entries may result in inconsistent distribution. Although
the entries may be redistributed after changing the adapters, the implementation
does not support this. We intend to keep the interface simple and avoid
complications. In case of an absolute requirement, we recommend employing another
map where the elements can be redistributed.

Internally, all the key-value pairs are stored as entries in an array of buckets.
The array grows and shrinks as needed. As of this version, no interface is
provided to extract a reference to the internal array. Although, an interface
to manipulate the threshold and load factor is provided.

You can invoke the `jtk_HashMap_newWithLoadFactor()` function to construct a
hash map with a custom load factor.
```
jtk_HashMap_t* map = jtk_HashMap_newWithLoadFactor(jtk_StringObjectAdapter_getInstance(),
    jtk_StringObjectAdapter_getInstance(), 0.9f);
```

You can invoke the `jtk_HashMap_newWithCapacity()` function to construct a
hash map with a custom initial capacity.
```
jtk_HashMap_t* map = jtk_HashMap_newWithCapacity(jtk_StringObjectAdapter_getInstance(),
    jtk_StringObjectAdapter_getInstance(), 16);
```

Or, you can specify both load factor and capacity together.
```
jtk_HashMap_t* map = jtk_HashMap_newEx(jtk_StringObjectAdapter_getInstance(),
    jtk_StringObjectAdapter_getInstance(), 0.6, 32);
```

### Inserting Entries in HashMap

The `HashMap` class provides access to values associated with keys. A value is
accessed by its associated key. 

The `jtk_HashMap_put()` function inserts an entry in the map. If the specified
key already exists, this function updates the value silently.
```
xyz_House_t* stark = xyz_House_new(...);
xyz_House_t* lannister = xyz_House_new(...);
xyz_House_t* tyrell = xyz_House_new(...);
xyz_House_t* arryn = xyz_House_new(...);
xyz_House_t* targaryen = xyz_House_new(...);
xyz_House_t* martell = xyz_House_new(...);
xyz_House_t* baratheon = xyz_House_new(...);
xyz_House_t* greyjoy = xyz_House_new(...);

jtk_HashMap_put(houses, "House Stark", stark);
jtk_HashMap_put(houses, "House Lannister", lannister);
jtk_HashMap_put(houses, "House Tyrell", tyrell);
jtk_HashMap_put(houses, "House Arryn", arryn);
jtk_HashMap_put(houses, "House Targaryen", targaryen);
jtk_HashMap_put(houses, "House Martell", martell);
jtk_HashMap_put(houses, "House Bartheon", baratheon);
jtk_HashMap_put(houses, "House Greyjoy", greyjoy);
```

The `jtk_HashMap_putStrictly()` function inserts an entry only if the key does
not exist. The following example fails to update the key `House Stark`.
```
if (jtk_HashMap_putStrictly(houses, "House Stark", lannister, NULL)) {
    printf("House Stark already exists! It cannot be replaced by House Lannister.\n");
}
else {
    printf("Yeah, right.\n");
}
```

### Removing Keys from HashMap

You can remove a key by invoking `jtk_HashMap_removeKey()`.
```
/* Spoiler alert! */
jtk_HashMap_removeKey(houses, "House Tyrell");
```

### Getting Values from HashMap

You can retrieve a value via `jtk_HashMap_getValue()` function. You need
to specify the map in which the value is stored and the key associated with the
value.
```
xyz_House_t* house = (xyz_House_t*)jtk_HashMap_getValue(houses, "House Targaryen");
```

### Obtaining Iterator from HashMap

An iterator can be obtained for an instance of the `HashMap` class.

We can obtain three types of iterators from a `HashMap`. We can obtain an iterator
to traverse entries, keys, and values. Always remember to destroy the iterator you
obtain.
```
jtk_Iterator_t* keyIterator = jtk_DoublyLinkedList_getKeyIterator(houses);
while (jtk_Iterator_hasNext(keyIterator)) {
    const uint8_t* key = (const uint8_t*)jtk_Iterator_getNext(keyIterator);
    xyz_House_t* house = (xyz_House_t*)jtk_HashMap_getValue(houses, key);
    ...
}
jtk_Iterator_delete(keyIterator);
```

```
jtk_Iterator_t* valueIterator = jtk_DoublyLinkedList_getValueIterator(students);
while (jtk_Iterator_hasNext(valueIterator)) {
    xyz_House_t* house = (xyz_House_t*)jtk_Iterator_getNext(valueIterator);
    ...
}
jtk_Iterator_delete(valueIterator);
```

```
jtk_Iterator_t* entryIterator = jtk_DoublyLinkedList_getEntryIterator(students);
while (jtk_Iterator_hasNext(entryIterator)) {
    jtk_HashMapEntry_t* entry = (jtk_HashMapEntry_t*)jtk_Iterator_getNext(entryIterator);
    const uint8_t* key = (const uint8_t*)entry->m_key;
    xyz_House_t* value = (xyz_House_t*)entry->m_value;
    ...
}
jtk_Iterator_delete(entryIterator);
```

The source iterators for the `HashMap` class are situated in the
`jtk/collection/map/HashMapEntryIterator.h`, `jtk/collection/map/HashMapKeyIterator.h`,
and `jtk/collection/map/HashMapValueIterator.h` header files.
```
jtk_HashMapEntryIterator_t* entryIterator = jtk_HashMapEntryIterator_new(houses);
jtk_Iterator_t* iterator = jtk_HashMapEntryIterator_getIterator(entryIterator);
while (jtk_Iterator_hasNext(iterator)) {
    ...
}
```

```
jtk_HashMapValueIterator_t* entryIterator = jtk_HashMapValueIterator_new(houses);
jtk_Iterator_t* iterator = jtk_HashMapValueIterator_getIterator(entryIterator);
while (jtk_Iterator_hasNext(iterator)) {
    ...
}
```

```
jtk_HashMapKeyIterator_t* entryIterator = jtk_HashMapKeyIterator_new(houses);
jtk_Iterator_t* iterator = jtk_HashMapKeyIterator_getIterator(entryIterator);
while (jtk_Iterator_hasNext(iterator)) {
    ...
}
```

### HashMap Synchronization Policy

The HashMap class is intended to be used by a single thread. It does not
implement a thread synchronization policy. In other words, it is not thread
safe. Concurrent invocation of a function against an instance without an
external synchronization results in undefined behaviour.