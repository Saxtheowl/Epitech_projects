/*
** EPITECH PROJECT, 2025
** My_sudo
** File description:
** User authentication functions
*/

#include "my_sudo.h"

char *read_password(void)
{
    struct termios old_termios, new_termios;
    char *password = malloc(256);
    int i = 0;
    int c = 0;
    
    if (!password)
        return NULL;
    
    if (tcgetattr(STDIN_FILENO, &old_termios) != 0) {
        free(password);
        return NULL;
    }
    
    new_termios = old_termios;
    new_termios.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHONL);
    
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &new_termios) != 0) {
        free(password);
        return NULL;
    }
    
    while ((c = getchar()) != '\n' && c != EOF && i < 255) {
        password[i++] = c;
    }
    password[i] = '\0';
    
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &old_termios);
    printf("\n");
    
    return password;
}

static int verify_password(const char *username, const char *password)
{
    struct spwd *spwd_entry = getspnam(username);
    char *encrypted = NULL;
    
    if (!spwd_entry) {
        struct passwd *pwd = getpwnam(username);
        if (!pwd)
            return -1;
        if (strcmp(pwd->pw_passwd, "*") == 0 || strcmp(pwd->pw_passwd, "x") == 0)
            return -1;
        encrypted = crypt(password, pwd->pw_passwd);
        return (encrypted && strcmp(encrypted, pwd->pw_passwd) == 0) ? 0 : -1;
    }
    
    encrypted = crypt(password, spwd_entry->sp_pwdp);
    if (!encrypted)
        return -1;
    
    return (strcmp(encrypted, spwd_entry->sp_pwdp) == 0) ? 0 : -1;
}

int authenticate_user(const char *username)
{
    char *password = NULL;
    int attempts = 0;
    int failed_attempts = 0;
    
    for (attempts = 0; attempts < MAX_ATTEMPTS; attempts++) {
        printf("[my_sudo] password for %s:", username);
        fflush(stdout);
        
        password = read_password();
        if (!password) {
            fprintf(stderr, "my_sudo: unable to read password\n");
            return -1;
        }
        
        if (verify_password(username, password) == 0) {
            if (failed_attempts > 0) {
                fprintf(stderr, "Sorry, try again.\n");
            }
            free(password);
            return 0;
        }
        
        failed_attempts++;
        free(password);
        
        if (attempts < MAX_ATTEMPTS - 1) {
            fprintf(stderr, "Sorry, try again.\n");
        }
    }
    
    fprintf(stderr, "my_sudo: %d incorrect password attempts\n", failed_attempts);
    return -1;
}