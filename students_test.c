#include <stdio.h>

#include "students.h"

void students_print(const struct student *student) {
  printf("Name: %s\n", student->name);
  printf("ID: %s\n", student->id);
}

int main(void) {
  struct students *stds = students_new();

  struct student *std1 = student_new("Parham Alvani", "9231058");
  struct student *std2 = student_new("Saman Fekri", "9231075");
  struct student *std3 = student_new("Sepehr Sabour", "9231011");
  struct student *std4 = student_new("Hesam Hedayati", "9231027");

  students_push_back(stds, std1);
  students_push_back(stds, std2);
  students_push_back(stds, std3);
  students_push_back(stds, std4);

  students_foreach(stds, students_print);

  FILE *fp = fopen("students.txt", "w");
  students_foreach_loop(stds, el) {
    fprintf(fp, "Name: %s\n", el->name);
    fprintf(fp, "ID: %s\n", el->id);
    fprintf(fp, "\n");
  }
  fclose(fp);

  printf("%zu\n", students_len(stds));
  printf("Parham @ %d\n", students_search_name(stds, "Parham Alvani"));
  printf("Saman @ %d\n", students_search_id(stds, "9231075"));

  // students_delete frees both the list and all students it contains
  students_delete(stds);
}
