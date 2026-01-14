#include <stdlib.h>
#include <string.h>

#include "courses.h"

struct course *course_create(const char *name, const char *professor, int number_of_sessions) {
  struct course *crs = malloc(sizeof(struct course));
  if (crs == NULL) {
    return NULL;
  }

  size_t nlen = sizeof(crs->name);
  strncpy(crs->name, name, nlen - 1);
  crs->name[nlen - 1] = '\0';

  size_t plen = sizeof(crs->professor);
  strncpy(crs->professor, professor, plen - 1);
  crs->professor[plen - 1] = '\0';

  crs->students = students_new();
  if (crs->students == NULL) {
    free(crs);
    return NULL;
  }

  crs->number_of_sessions = number_of_sessions;
  crs->attendance = malloc(sizeof(struct students *) * (size_t)number_of_sessions);
  if (crs->attendance == NULL) {
    students_delete(crs->students);
    free(crs);
    return NULL;
  }

  for (int i = 0; i < number_of_sessions; i++) {
    crs->attendance[i] = students_new();
    if (crs->attendance[i] == NULL) {
      // Clean up previously allocated attendance lists
      for (int j = 0; j < i; j++) {
        students_clear(crs->attendance[j]);
      }
      free(crs->attendance);
      students_delete(crs->students);
      free(crs);
      return NULL;
    }
  }

  return crs;
}

void course_register(struct course *course, struct student *student) {
  students_push_back(course->students, student);
}

int course_attend(struct course *course, const struct student *student, int session) {
  // Validate session bounds
  if (session < 0 || session >= course->number_of_sessions) {
    return -1;
  }

  // Check the student existence in the enrolled list
  if (students_search_id(course->students, student->id) == -1) {
    return -1;
  }

  // Note: We store a reference to the student, not a copy.
  // The attendance list does not own the student object.
  students_push_back(course->attendance[session], (struct student *)student);
  return 0;
}

int course_student_attend_count(const struct course *course, const char *id) {
  int count = 0;

  for (int i = 0; i < course->number_of_sessions; i++) {
    if (students_search_id(course->attendance[i], id) != -1) {
      count++;
    }
  }

  return count;
}


void course_delete(struct course *course) {
  // First clear attendance lists (they don't own the students)
  for (int i = 0; i < course->number_of_sessions; i++) {
    students_clear(course->attendance[i]);
  }
  free(course->attendance);

  // Then delete students list (it owns the students)
  students_delete(course->students);

  free(course);
}

// Courses list management

struct courses *courses_new(void) {
  struct courses *list = malloc(sizeof(struct courses));
  if (list == NULL) {
    return NULL;
  }
  list->length = 0;
  list->head = NULL;
  return list;
}

int courses_len(const struct courses *courses) {
  return courses->length;
}

void courses_push_back(struct courses *courses, struct course *course) {
  struct courses_el *el = malloc(sizeof(struct courses_el));
  if (el == NULL) {
    return;
  }
  el->course = course;
  el->next = NULL;

  courses->length++;

  if (courses->head == NULL) {
    courses->head = el;
  } else {
    struct courses_el *p = courses->head;
    while (p->next != NULL) {
      p = p->next;
    }
    p->next = el;
  }
}

struct course *courses_get(const struct courses *courses, int index) {
  if (index < 0 || index >= courses->length) {
    return NULL;
  }

  struct courses_el *p = courses->head;
  for (int i = 0; i < index; i++) {
    p = p->next;
  }
  return p->course;
}

void courses_remove(struct courses *courses, int index) {
  if (index < 0 || index >= courses->length) {
    return;
  }

  struct courses_el *el = courses->head;

  if (index == 0) {
    courses->head = el->next;
    course_delete(el->course);
    free(el);
  } else {
    for (int i = 0; i < index - 1; i++) {
      el = el->next;
    }
    struct courses_el *to_remove = el->next;
    el->next = to_remove->next;
    course_delete(to_remove->course);
    free(to_remove);
  }

  courses->length--;
}

void courses_delete(struct courses *courses) {
  struct courses_el *p = courses->head;

  while (p) {
    struct courses_el *el = p;
    p = p->next;
    course_delete(el->course);
    free(el);
  }

  free(courses);
}
