#ifndef COURSES_H
#define COURSES_H

#include "students.h"

struct course {
    char name[256];
    char professor[256];
    struct students *students;
    int number_of_sessions;
    struct students **attendance;
};

struct courses {
    int length;
    struct courses_el *head;
};

struct courses_el {
    struct course *course;
    struct courses_el *next;
};

struct course *course_create(const char *name, const char *professor, int number_of_sessions);

void course_register(struct course *course, struct student *student);

// Mark student as attending a session. Returns 0 on success, -1 on error.
int course_attend(struct course *course, const struct student *student, int session);

int course_student_attend_count(const struct course *course, const char *id);

void course_delete(struct course *course);

#endif
