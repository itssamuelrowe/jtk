#include <jtk/collection/list/ArrayList.h>
#include <stdio.h>

struct xyz_Student_t {
    uint8_t* m_name;
    int32_t m_nameSize;
    uint8_t* m_branch;
    int32_t m_branchSize;
    uint8_t* m_college;
    int32_t m_collegeSize;
    uint8_t* m_id;
    int32_t m_idSize;
    int32_t m_age;
};

typedef struct xyz_Student_t xyz_Student_t;

xyz_Student_t* xyz_Student_new(const uint8_t* name, const uint8_t* branch,
    const uint8_t* college, const uint8_t* id, int32_t age) {
    xyz_Student_t* student = jtk_Memory_allocate(xyz_Student_t, 1);
    student->m_name = jtk_String_new(name);
    student->m_nameSize = jtk_String_getSize(name);
    student->m_branch = jtk_String_new(branch);
    student->m_branchSize = jtk_String_getSize(branch);
    student->m_college = jtk_String_new(college);
    student->m_collegeSize = jtk_String_getSize(college);
    student->m_id = jtk_String_new(id);
    student->m_idSize = jtk_String_getSize(id);
    student->m_age = age;
    
    return student;
}

void xyz_Student_delete(xyz_Student_t* student) {
    jtk_String_delete(student->m_name);
    jtk_String_delete(student->m_branch);
    jtk_String_delete(student->m_college);
    jtk_String_delete(student->m_id);
    jtk_Memory_deallocate(student);
}

enum xyz_Option_t {
    XYZ_OPTION_EXIT = 1,
    XYZ_OPTION_HELP = 2,
};

typedef enum xyz_Option_t xyz_Option_t;

void xyz_Option_printMenu() {
    fprintf(stdout,
        "1 - Exit\n"
        "2 - Help\n");
}

int32_t main() {
    jtk_ArrayList_t* students = jtk_ArrayList_new();
    
    xyz_Option_printMenu();
    xyz_Option_t option;
    do {
        option = xyz_Option_readOption();
        
        switch (option) {
            case XYZ_OPTION_HELP: {
                xyz_Option_showMenu();
                break;
            }
        }
    }
    while (option != XYZ_OPTION_EXIT);
    
    jtk_Iterator_t* iterator = jtk_ArrayList_getIterator(students);
    while (jtk_Iterator_hasNext(iterator)) {
        xyz_Student_t* student = (xyz_Student_t*)jtk_Iterator_getNext(iterator);
        xyz_Student_delete(student);
    }
    jtk_Iterator_delete(iterator);
    
    jtk_ArrayList_delete(students);
    return 0;
}

remove-id 1
display