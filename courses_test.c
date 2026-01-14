#include <stdio.h>

#include "courses.h"

int main(void) {
  struct course *crs = course_create("Introduction to Programming", "Dr.Bakhshi", 16);

  struct student *std1 = student_new("Parham Alvani", "9231058");
  struct student *std2 = student_new("Saman Fekri", "9231075");
  struct student *std3 = student_new("Sepehr Sabour", "9231011");
  struct student *std4 = student_new("Hesam Hedayati", "9231027");

  course_register(crs, std1);
  course_register(crs, std2);
  course_register(crs, std3);
  course_register(crs, std4);

  course_attend(crs, std1, 0);
  course_attend(crs, std2, 0);
  course_attend(crs, std3, 0);

  course_attend(crs, std1, 1);
  course_attend(crs, std2, 1);
  course_attend(crs, std4, 1);

  printf("%s: %d\n", std1->id, course_student_attend_count(crs, std1->id));
  printf("%s: %d\n", std2->id, course_student_attend_count(crs, std2->id));
  printf("%s: %d\n", std3->id, course_student_attend_count(crs, std3->id));
  printf("%s: %d\n", std4->id, course_student_attend_count(crs, std4->id));

  // course_delete frees the course and all registered students
  course_delete(crs);
}
