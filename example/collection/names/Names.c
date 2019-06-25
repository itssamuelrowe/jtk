#include <jtk/collection/map/HashMap.h>
#include <jtk/core/StringObjectAdapter.h>

struct xyz_Person_t {
    uint8_t* m_name;
    int32_t m_age;
    uint8_t* m_college;
};

typedef struct xyz_Person_t xyz_Person_t;

xyz_Person_t* xyz_Person_new(const uint8_t* name, int32_t age, const uint8_t* college) {
    xyz_Person_t* person = jtk_Memory_allocate(xyz_Person_t, 1);
    person->m_name = jtk_String_new(name);
    person->m_age = age;
    person->m_college = jtk_String_new(college);

    return person;
}

void xyz_Person_delete(xyz_Person_t* person) {
    jtk_String_delete(person->m_name);
    jtk_String_delete(person->m_college);
    jtk_Memory_deallocate(person);
}

void printDetails(jtk_HashMap_t* map, const uint8_t* name) {
    xyz_Person_t* person = jtk_HashMap_getValue(map, name);
    if (person != NULL) {
        printf("Name: %s\n", person->m_name);
        printf("Age: %d\n", person->m_age);
        printf("College: %s\n", person->m_college);
    }
    else {
        printf("No record found for '%s'\n", name);
    }
    printf("----------------------------------------------------------------------\n");
}

int32_t main() {
    xyz_Person_t* samuel = xyz_Person_new("Samuel Rowe", 19, "Presidency University");
    xyz_Person_t* johaniel = xyz_Person_new("Johaniel Augutine", 19, "IHM");
    xyz_Person_t* suhas = xyz_Person_new("Suhas KS", 20, "Presidency University");
    xyz_Person_t* pavan = xyz_Person_new("Pavan Kumar", 19, "Bangalore City College");
    xyz_Person_t* satya = xyz_Person_new("Satya Pratyusha Talapragada", 19, "Presidency University");

    jtk_ObjectAdapter_t* keyAdapter = jtk_StringObjectAdapter_getInstance();

    jtk_HashMap_t* map = jtk_HashMap_new(keyAdapter, NULL);
    printf("(After creating) Size: %d\n", jtk_HashMap_getSize(map));

    /* The keys are static! In other words, they exist as long this scope is
     * valid.
     */
    jtk_HashMap_put(map, "samuel", samuel);
    jtk_HashMap_put(map, "johaniel", johaniel);
    jtk_HashMap_put(map, "suhas", suhas);
    jtk_HashMap_put(map, "pavan", pavan);
    jtk_HashMap_put(map, "satya", satya);
    printf("(After mapping) Size: %d\n", jtk_HashMap_getSize(map));

    printDetails(map, "Suhas");
    printDetails(map, "Samuel");

    jtk_Iterator_t* keys = jtk_HashMap_getKeyIterator(map);
    while (jtk_Iterator_hasNext(keys)) {
        const uint8_t* key = (const uint8_t*)jtk_Iterator_getNext(keys);
        printDetails(map, key);
    }
    jtk_Iterator_delete(keys);

    jtk_HashMap_removeKey(map, "samuel");
    jtk_HashMap_removeKey(map, "pavan");
    jtk_HashMap_removeKey(map, "suhas");
    printDetails(map, "samuel");
    printDetails(map, "pavan");
    printDetails(map, "suhas");
    printf("(After removing) Size: %d\n", jtk_HashMap_getSize(map));

    printf("Contains key 'suhas'? %d\n", jtk_HashMap_containsKey(map, "suhas"));
    printf("Contains key 'satya'? %d\n", jtk_HashMap_containsKey(map, "satya"));
    printf("Contains value 'suhas'? %d\n", jtk_HashMap_containsValue(map, suhas));
    printf("Contains value 'satya'? %d\n", jtk_HashMap_containsValue(map, satya));

    jtk_HashMap_clear(map);
    printf("(After clearing) Size: %d\n", jtk_HashMap_getSize(map));

    xyz_Person_delete(samuel);
    xyz_Person_delete(johaniel);
    xyz_Person_delete(suhas);
    xyz_Person_delete(pavan);
    xyz_Person_delete(satya);

    return 0;
}