#include <stdlib.h>
#include <string.h>

#include "students.h"


struct student *student_new(const char *name, const char *id) {
  struct student *std = malloc(sizeof(struct student));

  size_t nlen = sizeof(std->name) / sizeof(char);
  strncpy(std->name, name, nlen - 1);
  std->name[nlen - 1] = '\0';

  size_t ilen = sizeof(std->id) / sizeof(char);
  strncpy(std->id, id, ilen - 1);
  std->id[ilen - 1] = '\0';

  return std;
}

void student_delete(struct student *student) {
  free(student);
}

struct students *students_new(void) {
  struct students *stds = malloc(sizeof(struct students));
  stds->length = 0;
  stds->head = NULL;

  return stds;
}

int students_len(struct students *students) {
  return students->length;
}

void students_push_back(struct students *students, struct student *student) {
  struct students_el *el = malloc(sizeof(struct students_el));
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

void students_remove(struct students *students, int index) {
  struct students_el *el = students->head;

  if (index == 0) {
    students->head = el->next;
    free(el);
  } else {
    int i = 0;
    while (el && i + 1 < index) {
      el = el->next;
      i++;
    }
    if (i + 1 == index) {
      struct students_el *p = el->next->next;
      free(el->next);
      el->next = p;
    }
  }
}

int students_search_name(struct students *students, const char *name) {
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

int students_search_id(struct students *students, const char *id) {
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
    free(el);
  }

  free(students);
}

void students_foreach(struct students *students, students_foreach_func f) {
  struct students_el *p = students->head;

  while (p) {
    f(p->student);
    p = p->next;
  }
}
