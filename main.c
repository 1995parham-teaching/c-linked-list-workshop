#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "courses.h"

#define DEFAULT_SESSIONS 16
#define MIN_ATTENDANCE 3

// Input helpers
static int read_int(const char *prompt) {
  int value;
  printf("%s", prompt);
  if (scanf("%d", &value) != 1) {
    // Clear invalid input
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    return -1;
  }
  // Clear trailing newline
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
  return value;
}

static void read_string(const char *prompt, char *buffer, size_t size) {
  printf("%s", prompt);
  if (fgets(buffer, (int)size, stdin) != NULL) {
    // Remove trailing newline
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
      buffer[len - 1] = '\0';
    }
  }
}

// Menu display functions
static void show_main_menu(void) {
  printf("\n");
  printf("=== Class Attendance System ===\n");
  printf("1. List all courses\n");
  printf("2. Add new course\n");
  printf("3. Select a course\n");
  printf("4. Remove a course\n");
  printf("0. Exit\n");
}

static void show_course_menu(const struct course *course) {
  printf("\n");
  printf("=== %s ===\n", course->name);
  printf("1. View course info\n");
  printf("2. Register student\n");
  printf("3. Remove student\n");
  printf("4. Mark attendance\n");
  printf("5. View attendance report\n");
  printf("6. Check 3/16 rule violations\n");
  printf("0. Back to main menu\n");
}

// Course operations
static void list_courses(const struct courses *courses) {
  printf("\n--- Courses ---\n");
  if (courses_len(courses) == 0) {
    printf("No courses available.\n");
    return;
  }

  for (int i = 0; i < courses_len(courses); i++) {
    struct course *c = courses_get(courses, i);
    printf("%d. %s (Prof. %s)\n", i + 1, c->name, c->professor);
  }
}

static void add_course(struct courses *courses) {
  char name[256];
  char professor[256];

  printf("\n--- Add New Course ---\n");
  read_string("Course name: ", name, sizeof(name));
  read_string("Professor name: ", professor, sizeof(professor));

  int sessions = read_int("Number of sessions (default 16): ");
  if (sessions <= 0) {
    sessions = DEFAULT_SESSIONS;
  }

  struct course *course = course_create(name, professor, sessions);
  if (course == NULL) {
    printf("Error: Failed to create course.\n");
    return;
  }

  courses_push_back(courses, course);
  printf("Course '%s' added successfully.\n", name);
}

static struct course *select_course(struct courses *courses) {
  if (courses_len(courses) == 0) {
    printf("No courses available.\n");
    return NULL;
  }

  list_courses(courses);
  int index = read_int("Select course number: ");

  if (index < 1 || index > courses_len(courses)) {
    printf("Invalid selection.\n");
    return NULL;
  }

  return courses_get(courses, index - 1);
}

static void remove_course(struct courses *courses) {
  if (courses_len(courses) == 0) {
    printf("No courses available.\n");
    return;
  }

  list_courses(courses);
  int index = read_int("Select course to remove: ");

  if (index < 1 || index > courses_len(courses)) {
    printf("Invalid selection.\n");
    return;
  }

  struct course *c = courses_get(courses, index - 1);
  printf("Removing course '%s'...\n", c->name);
  courses_remove(courses, index - 1);
  printf("Course removed.\n");
}

// Student operations
static void view_course_info(const struct course *course) {
  printf("\n--- Course Info ---\n");
  printf("Name: %s\n", course->name);
  printf("Professor: %s\n", course->professor);
  printf("Sessions: %d\n", course->number_of_sessions);
  printf("Enrolled students: %zu\n", students_len(course->students));
}

static void register_student(struct course *course) {
  char name[256];
  char id[32];

  printf("\n--- Register Student ---\n");
  read_string("Student name: ", name, sizeof(name));
  read_string("Student ID: ", id, sizeof(id));

  // Check if student already exists
  if (students_search_id(course->students, id) != -1) {
    printf("Error: Student with ID '%s' already registered.\n", id);
    return;
  }

  struct student *student = student_new(name, id);
  if (student == NULL) {
    printf("Error: Failed to create student.\n");
    return;
  }

  course_register(course, student);
  printf("Student '%s' registered successfully.\n", name);
}

static void remove_student(struct course *course) {
  if (students_len(course->students) == 0) {
    printf("No students enrolled.\n");
    return;
  }

  printf("\n--- Remove Student ---\n");
  printf("Enrolled students:\n");

  int i = 0;
  students_foreach_loop(course->students, s) {
    printf("%d. %s (%s)\n", i + 1, s->name, s->id);
    i++;
  }

  int index = read_int("Select student to remove: ");
  if (index < 1 || index > (int)students_len(course->students)) {
    printf("Invalid selection.\n");
    return;
  }

  students_remove(course->students, (size_t)(index - 1));
  printf("Student removed.\n");
}

static void mark_attendance(struct course *course) {
  if (students_len(course->students) == 0) {
    printf("No students enrolled.\n");
    return;
  }

  printf("\n--- Mark Attendance ---\n");
  printf("Session number (0-%d): ", course->number_of_sessions - 1);
  int session = read_int("");

  if (session < 0 || session >= course->number_of_sessions) {
    printf("Invalid session number.\n");
    return;
  }

  printf("Mark attendance for session %d.\n", session);
  printf("Enter student numbers to mark present (0 to finish):\n");

  int i = 0;
  students_foreach_loop(course->students, s) {
    printf("%d. %s (%s)\n", i + 1, s->name, s->id);
    i++;
  }

  while (1) {
    int index = read_int("Student number (0 to finish): ");
    if (index == 0) {
      break;
    }

    if (index < 1 || index > (int)students_len(course->students)) {
      printf("Invalid selection.\n");
      continue;
    }

    // Find the student by index
    int j = 0;
    students_foreach_loop(course->students, s) {
      if (j == index - 1) {
        if (course_attend(course, s, session) == 0) {
          printf("Marked %s as present.\n", s->name);
        } else {
          printf("Failed to mark attendance.\n");
        }
        break;
      }
      j++;
    }
  }

  printf("Attendance marking complete.\n");
}

static void view_attendance_report(const struct course *course) {
  if (students_len(course->students) == 0) {
    printf("No students enrolled.\n");
    return;
  }

  printf("\n--- Attendance Report ---\n");
  printf("%-30s %-10s %s\n", "Name", "ID", "Attendance");
  printf("%-30s %-10s %s\n", "----", "--", "----------");

  students_foreach_loop(course->students, s) {
    int count = course_student_attend_count(course, s->id);
    printf("%-30s %-10s %d/%d\n", s->name, s->id, count, course->number_of_sessions);
  }
}

static void check_violations(struct course *course) {
  if (students_len(course->students) == 0) {
    printf("No students enrolled.\n");
    return;
  }

  printf("\n--- 3/16 Rule Violations ---\n");
  printf("Students with less than %d attendances:\n\n", MIN_ATTENDANCE);

  int violations = 0;
  int indices[256];
  int idx = 0;

  students_foreach_loop(course->students, s) {
    int count = course_student_attend_count(course, s->id);
    if (count < MIN_ATTENDANCE) {
      printf("%d. %s (%s) - %d/%d attendances\n",
             violations + 1, s->name, s->id, count, course->number_of_sessions);
      if (violations < 256) {
        indices[violations] = idx;
      }
      violations++;
    }
    idx++;
  }

  if (violations == 0) {
    printf("No violations found.\n");
    return;
  }

  printf("\nFound %d student(s) with violations.\n", violations);

  char response[16];
  read_string("Remove all violating students? (yes/no): ", response, sizeof(response));

  if (strcmp(response, "yes") == 0) {
    // Remove in reverse order to maintain correct indices
    for (int i = violations - 1; i >= 0; i--) {
      students_remove(course->students, (size_t)indices[i]);
    }
    printf("Removed %d student(s).\n", violations);
  } else {
    printf("No students removed.\n");
  }
}

// Main program
int main(void) {
  struct courses *courses = courses_new();
  if (courses == NULL) {
    fprintf(stderr, "Error: Failed to initialize courses list.\n");
    return 1;
  }

  struct course *current_course = NULL;
  int running = 1;

  printf("Welcome to the Class Attendance System (CAS)\n");

  while (running) {
    if (current_course == NULL) {
      // Main menu
      show_main_menu();
      int choice = read_int("Choice: ");

      switch (choice) {
        case 1:
          list_courses(courses);
          break;
        case 2:
          add_course(courses);
          break;
        case 3:
          current_course = select_course(courses);
          break;
        case 4:
          remove_course(courses);
          break;
        case 0:
          running = 0;
          break;
        default:
          printf("Invalid choice.\n");
      }
    } else {
      // Course menu
      show_course_menu(current_course);
      int choice = read_int("Choice: ");

      switch (choice) {
        case 1:
          view_course_info(current_course);
          break;
        case 2:
          register_student(current_course);
          break;
        case 3:
          remove_student(current_course);
          break;
        case 4:
          mark_attendance(current_course);
          break;
        case 5:
          view_attendance_report(current_course);
          break;
        case 6:
          check_violations(current_course);
          break;
        case 0:
          current_course = NULL;
          break;
        default:
          printf("Invalid choice.\n");
      }
    }
  }

  printf("Goodbye!\n");
  courses_delete(courses);
  return 0;
}
