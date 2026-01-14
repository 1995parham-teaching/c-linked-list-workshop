# Compiler settings
CC = gcc
CFLAGS = -Wall -Wextra -std=c11
LDLIBS =

# Strict flags for static analysis
CHECK_FLAGS = -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wstrict-prototypes \
              -Wmissing-prototypes -Wformat=2 -Werror -fsyntax-only

# Source files
SRCS = students.c courses.c
OBJS = $(SRCS:.c=.o)

# Test executables
TEST_STUDENTS = students_test
TEST_COURSES = courses_test

# Main executable (for Step 3)
MAIN = cas.out

# Default target
all: $(MAIN)

# Main application (requires main.c for Step 3)
$(MAIN): main.o $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LDLIBS)

# Object files
%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

# Static analysis / linting
.PHONY: check
check:
	@echo "Running static analysis..."
	@$(CC) $(CHECK_FLAGS) students.c && echo "  students.c: OK"
	@$(CC) $(CHECK_FLAGS) courses.c && echo "  courses.c: OK"
	@$(CC) $(CHECK_FLAGS) -Wno-missing-prototypes students_test.c && echo "  students_test.c: OK"
	@$(CC) $(CHECK_FLAGS) -Wno-missing-prototypes courses_test.c && echo "  courses_test.c: OK"
	@echo "All checks passed!"

# Build tests
$(TEST_STUDENTS): students_test.c students.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDLIBS)

$(TEST_COURSES): courses_test.c courses.o students.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDLIBS)

# Run tests
.PHONY: test
test: $(TEST_STUDENTS) $(TEST_COURSES)
	@echo "Running students_test..."
	@./$(TEST_STUDENTS)
	@echo ""
	@echo "Running courses_test..."
	@./$(TEST_COURSES)
	@echo ""
	@echo "All tests passed!"

# Build and run everything
.PHONY: ci
ci: check test
	@echo "CI complete!"

# Clean build artifacts
.PHONY: clean
clean:
	rm -f $(MAIN) $(TEST_STUDENTS) $(TEST_COURSES) *.o students.txt

# Dependencies
students.o: students.c students.h
courses.o: courses.c courses.h students.h
