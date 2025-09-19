/*
** EPITECH PROJECT, 2025
** My_sudo
** File description:
** User authentication for my_sudo
*/

#include "my_sudo.h"

char *get_password_input(void)
{
    char *password = NULL;
    size_t len = 0;
    ssize_t read;

    // Read password from stdin (not from tty like real sudo)
    read = getline(&password, &len, stdin);
    if (read > 0 && password[read - 1] == '\n') {
        password[read - 1] = '\0';
    }

    return password;
}

int verify_password(const char *username, const char *password)
{
    struct spwd *shadow_entry;
    char *encrypted;

    // Get shadow entry for user
    shadow_entry = getspnam(username);
    if (!shadow_entry) {
        // If shadow not available, try passwd
        struct passwd *pw = getpwnam(username);
        if (!pw || strcmp(pw->pw_passwd, "x") == 0) {
            return 0;
        }
        encrypted = crypt(password, pw->pw_passwd);
        return (encrypted && strcmp(encrypted, pw->pw_passwd) == 0);
    }

    // Verify password using shadow
    encrypted = crypt(password, shadow_entry->sp_pwdp);
    return (encrypted && strcmp(encrypted, shadow_entry->sp_pwdp) == 0);
}

int authenticate_user(const char *username)
{
    char *password;
    int attempts = 0;
    int max_attempts = 3;

    printf("[my_sudo] password for %s:\n", username);

    while (attempts < max_attempts) {
        password = get_password_input();
        if (!password) {
            return 0;
        }

        if (verify_password(username, password)) {
            free(password);
            return 1;
        }

        free(password);
        attempts++;

        if (attempts < max_attempts) {
            printf("Sorry, try again.\n");
            printf("[my_sudo] password for %s:\n", username);
        }
    }

    printf("my_sudo: %d incorrect password attempts\n", attempts);
    return 0;
}