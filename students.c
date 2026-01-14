#include <stdlib.h>
#include <string.h>

#include "students.h"


struct student *student_new(const char *name, const char *id) {
  struct student *std = malloc(sizeof(struct student));
  if (std == NULL) {
    return NULL;
  }

  size_t nlen = sizeof(std->name);
  strncpy(std->name, name, nlen - 1);
  std->name[nlen - 1] = '\0';

  size_t ilen = sizeof(std->id);
  strncpy(std->id, id, ilen - 1);
  std->id[ilen - 1] = '\0';

  return std;
}

void student_delete(struct student *student) {
  free(student);
}

struct students *students_new(void) {
  struct students *stds = malloc(sizeof(struct students));
  if (stds == NULL) {
    return NULL;
  }
  stds->length = 0;
  stds->head = NULL;

  return stds;
}

size_t students_len(const struct students *students) {
  return students->length;
}

void students_push_back(struct students *students, struct student *student) {
  struct students_el *el = malloc(sizeof(struct students_el));
  if (el == NULL) {
    return;
  }
  el->next = NULL;
  el->student = student;

  students->length++;

  if (students->head == NULL) {
    students->head = el;
  } else {
    struct students_el *p = students->head;

    while (p->next != NULL) {
      p = p->next;
    }

    p->next = el;
  }
}

int students_remove(struct students *students, size_t index) {
  if (index >= students->length) {
    return -1;
  }

  struct students_el *el = students->head;

  if (index == 0) {
    students->head = el->next;
    student_delete(el->student);
    free(el);
  } else {
    size_t i = 0;
    while (i + 1 < index) {
      el = el->next;
      i++;
    }
    struct students_el *to_remove = el->next;
    el->next = to_remove->next;
    student_delete(to_remove->student);
    free(to_remove);
  }

  students->length--;
  return 0;
}

int students_search_name(const struct students *students, const char *name) {
  int index = -1;
  int i = 0;

  struct students_el *p = students->head;
  while (p) {
    if (strcmp(p->student->name, name) == 0) {
      index = i;
      break;
    }
    i++;
    p = p->next;
  }

  return index;
}

int students_search_id(const struct students *students, const char *id) {
  int index = -1;
  int i = 0;

  struct students_el *p = students->head;
  while (p) {
    if (strcmp(p->student->id, id) == 0) {
      index = i;
      break;
    }
    i++;
    p = p->next;
  }

  return index;
}

void students_delete(struct students *students) {
  struct students_el *p = students->head;

  while (p) {
    struct students_el *el = p;
    p = p->next;
    student_delete(el->student);
    free(el);
  }

  free(students);
}

void students_clear(struct students *students) {
  struct students_el *p = students->head;

  while (p) {
    struct students_el *el = p;
    p = p->next;
    free(el);
  }

  free(students);
}

void students_foreach(const struct students *students, students_foreach_func f) {
  struct students_el *p = students->head;

  while (p) {
    f(p->student);
    p = p->next;
  }
}
