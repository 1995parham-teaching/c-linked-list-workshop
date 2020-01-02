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

void course_attend(struct course *course, struct student *student, int session);

int course_student_attend_count(struct course *course, const char *id);

#endif
