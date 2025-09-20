#include "framework.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static struct test_case **registered_tests = NULL;
static size_t tests_count = 0;
static size_t tests_capacity = 0;
static struct test_case *current_test = NULL;
static int current_failed = 0;

static int stdout_pipe[2] = {-1, -1};
static int saved_stdout = -1;
static char *captured_output = NULL;
static int capture_active = 0;

static char *duplicate_buffer(const char *source)
{
    size_t length = strlen(source);
    char *copy = malloc(length + 1);

    if (!copy) {
        return NULL;
    }
    memcpy(copy, source, length + 1);
    return copy;
}

void register_test(struct test_case *test)
{
    if (tests_count == tests_capacity) {
        size_t new_capacity = tests_capacity ? tests_capacity * 2 : 16;
        struct test_case **new_tests = realloc(registered_tests, new_capacity * sizeof(*new_tests));
        if (!new_tests) {
            perror("realloc");
            exit(EXIT_FAILURE);
        }
        registered_tests = new_tests;
        tests_capacity = new_capacity;
    }
    registered_tests[tests_count++] = test;
}

void test_fail(const char *file, int line, const char *expr, const char *details)
{
    current_failed = 1;
    fprintf(stderr, "[FAIL] %s::%s (%s:%d) - %s", current_test->suite, current_test->name, file, line, expr);
    if (details) {
        fprintf(stderr, " [%s]", details);
    }
    fprintf(stderr, "\n");
}

void cr_redirect_stdout(void)
{
    if (capture_active) {
        return;
    }
    if (pipe(stdout_pipe) != 0) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    fflush(stdout);
    saved_stdout = dup(STDOUT_FILENO);
    if (saved_stdout == -1) {
        perror("dup");
        exit(EXIT_FAILURE);
    }
    if (dup2(stdout_pipe[1], STDOUT_FILENO) == -1) {
        perror("dup2");
        exit(EXIT_FAILURE);
    }
    close(stdout_pipe[1]);
    stdout_pipe[1] = -1;
    capture_active = 1;
}

static void clear_capture(void)
{
    if (!capture_active) {
        return;
    }
    fflush(stdout);
    dup2(saved_stdout, STDOUT_FILENO);
    close(saved_stdout);
    saved_stdout = -1;
    capture_active = 0;
}

const char *test_capture_stdout_end(void)
{
    if (!capture_active) {
        return captured_output ? captured_output : "";
    }
    clear_capture();
    if (captured_output) {
        free(captured_output);
        captured_output = NULL;
    }
    char buffer[16384];
    ssize_t read_bytes = read(stdout_pipe[0], buffer, sizeof(buffer) - 1);
    close(stdout_pipe[0]);
    stdout_pipe[0] = -1;
    if (read_bytes < 0) {
        read_bytes = 0;
    }
    buffer[read_bytes] = '\0';
    captured_output = duplicate_buffer(buffer);
    if (!captured_output) {
        captured_output = malloc(1);
        if (!captured_output) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
        captured_output[0] = '\0';
    }
    return captured_output;
}

int main(void)
{
    size_t passed = 0;

    for (size_t i = 0; i < tests_count; ++i) {
        current_test = registered_tests[i];
        current_failed = 0;
        if (captured_output) {
            free(captured_output);
            captured_output = NULL;
        }
        if (capture_active) {
            clear_capture();
        }
        current_test->fn();
        if (!current_failed) {
            ++passed;
        }
    }
    if (capture_active) {
        clear_capture();
    }
    free(captured_output);
    free(registered_tests);
    fprintf(stdout, "[RESULT] %zu/%zu tests passed\n", passed, tests_count);
    return (passed == tests_count) ? EXIT_SUCCESS : EXIT_FAILURE;
}
