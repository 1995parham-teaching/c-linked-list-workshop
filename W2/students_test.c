#include <stdio.h>

#include "students.h"

void students_print(const struct student *student) {
  printf("Name: %s\n", student->name);
  printf("ID: %s\n", student->id);
}

int main() {
  struct students *stds = students_new();

  struct student *std1 = student_new("Parham Alvani", "9231058");
  struct student *std2 = student_new("Saman Fekri", "9231075");

  students_push_back(stds, std1);
  students_push_back(stds, std2);

  students_foreach(stds, students_print);

  students_foreach_loop(stds, el) {
    printf("Name: %s\n", el->name);
    printf("ID: %s\n", el->id);
  }

  printf("%d\n", students_len(stds));
  printf("Parham @ %d\n", students_search_name(stds, "Parham Alvani"));
  printf("Saman @ %d\n", students_search_id(stds, "9231075"));
  students_delete(stds);
}
