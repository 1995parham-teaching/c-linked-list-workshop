#include <stdlib.h>
#include <string.h>

#include "courses.h"

struct course *course_create(const char *name, const char *professor, int number_of_sessions) {
  struct course *crs = malloc(sizeof(struct course));

  size_t nlen = sizeof(crs->name) / sizeof(char);
  strncpy(crs->name, name, nlen - 1);
  crs->name[nlen - 1] = '\0';

  size_t plen = sizeof(crs->professor) / sizeof(char);
  strncpy(crs->professor, professor, plen - 1);
  crs->professor[plen - 1] = '\0';

  crs->students = students_new();

  crs->number_of_sessions = number_of_sessions;
  crs->attendance = malloc(sizeof(struct students *) * number_of_sessions);
  for (int i = 0; i < number_of_sessions; i++) {
    crs->attendance[i] = students_new();
  }

  return crs;
}

void course_register(struct course *course, struct student *student) {
  students_push_back(course->students, student);
}

void course_attend(struct course *course, struct student *student, int session) {
  students_push_back(course->attendance[session], student);
}
