#ifndef STUDENTS_H
#define STUDENTS_H

#include <stddef.h>

#define students_foreach_loop(stds, element) \
    for (struct students_el *element ## _el = (stds)->head; \
         element ## _el != NULL; \
         element ## _el = element ## _el->next) \
        for (const struct student *element = element ## _el->student; \
             element != NULL; element = NULL)

struct student {
    char name[256];
    char id[32];
};

struct students {
    size_t length;
    struct students_el *head;
};

struct students_el {
    struct student *student;
    struct students_el *next;
};

typedef void (students_foreach_func)(const struct student *student);

// create a new student
struct student *student_new(const char *name, const char *id);

// free the memory of given student
void student_delete(struct student *student);

// create a new students list
struct students *students_new(void);

// return the number of students in the list
size_t students_len(const struct students *students);

// append given student at the end of the students list
void students_push_back(struct students *students, struct student *student);

// remove given index from the students list and free the student
// returns 0 on success, -1 on invalid index
int students_remove(struct students *students, size_t index);

// return the first student's index that has the given name, or -1 if not found
int students_search_name(const struct students *students, const char *name);

// return the first student's index that has the given id, or -1 if not found
int students_search_id(const struct students *students, const char *id);

// remove all students and free the list (frees student objects)
void students_delete(struct students *students);

// free the list without freeing student objects (for non-owning lists)
void students_clear(struct students *students);

// foreach loop
void students_foreach(const struct students *students, students_foreach_func f);

#endif
