#ifndef STUDENTS_H
#define STUDENTS_H

#define students_foreach_loop(stds, element) \
    struct students_el *element ## _el = stds->head; \
    const struct student *element = element ## _el->student; \
    for (; element ## _el != NULL; element ## _el = element ## _el->next, element = element ## _el ? element ## _el->student : NULL)

struct student {
    char name[256];
    char id[8];
};

struct students {
    int length;
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
int students_len(struct students *students);

// append given student at the end of the students list
void students_push_back(struct students *students, struct student *student);

// remove given index from the students list
void students_remove(struct students *students, int index);

// return the firs student's index that has the given name
int students_search_name(struct students *students, const char *name);

// return the firs student's index that has the given id
int students_search_id(struct students *students, const char *id);

// remove all students and free the list
void students_delete(struct students *students);

// foreach loop
void students_foreach(struct students *students, students_foreach_func f);

#endif
