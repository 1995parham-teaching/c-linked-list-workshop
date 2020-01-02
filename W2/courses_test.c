#include <stdlib.h>

#include "classes.h"

int main() {
  struct course *crs = course_create("Introduction to Programming", "Dr.Bakhshi", 16);

  struct student *std1 = student_new("Parham Alvani", "9231058");
  struct student *std2 = student_new("Saman Fekri", "9231075");
  struct student *std3 = student_new("Sepehr Sabour", "9231011");
  struct student *std4 = student_new("Hesam Hedayati", "9231027");

  course_register(crs, std1);
  course_register(crs, std2);
  course_register(crs, std3);
  course_register(crs, std4);
}
