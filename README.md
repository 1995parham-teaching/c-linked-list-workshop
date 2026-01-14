<div align="center">
  <h1>C Workshop on Linked-List and Structures</h1>
  <img alt="GitHub Workflow Status" src="https://img.shields.io/github/actions/workflow/status/1995parham-teaching/c-linked-list-workshop/ci.yml?logo=github&style=for-the-badge">
</div>

## Class Attendance System (CAS)

A workshop project implementing a Class Attendance System in C, designed to teach linked lists and data structures.

### Data Structures

**Course:**

| Field              | Type          |
| ------------------ | ------------- |
| Name               | String (255)  |
| Professor          | String (255)  |
| Number of Students | Integer       |
| Students List      | Linked-List   |
| Number of Sessions | Integer       |
| Attendance List    | []Linked-List |

**Student:**

| Field | Type        |
| ----- | ----------- |
| Name  | String (255)|
| ID    | String (31) |

### Requirements

**Class Management**
- Manage multiple classes per semester
- Add/remove classes dynamically (classes stored as linked-list)
- Select a class to manage its students and attendance

**Attendance Tracking**
- Each class has multiple sessions
- Attendance stored as an array of linked-lists (one per session)
- Mark students as present for each session

**Student Management**
- View all students with their attendance rate
- Students not meeting the **3/16 attendance rule** can be removed (with user confirmation)

**Persistence**
- Save class data to files (one file per class)
- Load class data on subsequent runs

### Implementation Steps

1. **Step 1:** Implement and Test a simple linked-list (`students.c`, `students.h`)
2. **Step 2:** Implement and Test a single class with its attendance (`courses.c`, `courses.h`)
3. **Step 3:** Implement the whole program (`main.c`)
4. **Step 4:** Add persistence into CAS with files

Step by Step [Gist](https://gist.github.com/1995parham/12684919529a6f2181208888d5a52cc5).

## Building and Testing

### Prerequisites

- GCC compiler
- Make

### Makefile Targets

| Target | Description |
|--------|-------------|
| `make check` | Run static analysis with strict compiler warnings |
| `make test` | Build and run all tests |
| `make ci` | Full CI workflow (check + test) |
| `make clean` | Remove build artifacts |
| `make all` | Build main application (requires `main.c`) |

### Quick Start

```bash
# Run static analysis
make check

# Build and run tests
make test

# Full CI workflow
make ci
```

## Project Structure

```
.
├── students.h          # Student linked-list interface
├── students.c          # Student linked-list implementation
├── students_test.c     # Student module tests
├── courses.h           # Course management interface
├── courses.c           # Course management implementation
├── courses_test.c      # Course module tests
├── Makefile            # Build configuration
└── .github/workflows/  # CI configuration
```

## API Reference

### Students Module

```c
// Create/delete
struct student *student_new(const char *name, const char *id);
void student_delete(struct student *student);

// List operations
struct students *students_new(void);
size_t students_len(const struct students *students);
void students_push_back(struct students *students, struct student *student);
int students_remove(struct students *students, size_t index);

// Search
int students_search_name(const struct students *students, const char *name);
int students_search_id(const struct students *students, const char *id);

// Cleanup
void students_delete(struct students *students);  // Frees students
void students_clear(struct students *students);   // Keeps students

// Iteration
void students_foreach(const struct students *students, students_foreach_func f);
students_foreach_loop(stds, element) { ... }  // Macro
```

### Courses Module

```c
struct course *course_create(const char *name, const char *professor, int sessions);
void course_register(struct course *course, struct student *student);
int course_attend(struct course *course, const struct student *student, int session);
int course_student_attend_count(const struct course *course, const char *id);
void course_delete(struct course *course);
```
