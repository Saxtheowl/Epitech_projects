#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int run_test(char *args[], char *expected_output) {
    int pipefd[2];
    pid_t pid;
    char buffer[1024] = {0};
    int status;

    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 0;
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        return 0;
    }

    if (pid == 0) {
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);

        execv("./z", args);
        perror("execv");
        exit(1);
    } else {
        close(pipefd[1]);
        read(pipefd[0], buffer, sizeof(buffer) - 1);
        close(pipefd[0]);
        waitpid(pid, &status, 0);

        if (strcmp(buffer, expected_output) == 0) {
            printf("✓ Test passed: %s\n", args[1] ? args[1] : "no args");
            return 1;
        } else {
            printf("✗ Test failed: %s\n", args[1] ? args[1] : "no args");
            printf("  Expected: %s\n", expected_output);
            printf("  Got: %s\n", buffer);
            return 0;
        }
    }
}

int main() {
    printf("Running tests for z program...\n\n");

    int passed = 0;
    int total = 0;

    // Test 1: Special value 0x12345678
    char *test1[] = {"./z", "0x12345678", NULL};
    total++;
    if (run_test(test1, "0111101000001010")) passed++;

    // Test 2: Special value 0x87654321
    char *test2[] = {"./z", "0x87654321", NULL};
    total++;
    if (run_test(test2, "0111101000001010")) passed++;

    // Test 3: Invalid hex characters
    char *test3[] = {"./z", "0xGHIJ", NULL};
    total++;
    if (run_test(test3, "z\n")) passed++;

    // Test 4: Last byte null
    char *test4[] = {"./z", "0x1234567800", NULL};
    total++;
    if (run_test(test4, "z\n")) passed++;

    // Test 5: Contains 0x42
    char *test5[] = {"./z", "0x42", NULL};
    total++;
    if (run_test(test5, "z\n")) passed++;

    printf("\n%d/%d tests passed\n", passed, total);
    return (passed == total) ? 0 : 1;
}