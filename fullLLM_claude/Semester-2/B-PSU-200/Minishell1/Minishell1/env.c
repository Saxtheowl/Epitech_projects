#include "mysh.h"

void init_env(char **envp)
{
    g_shell.environ = copy_env(envp);
    g_shell.env_size = 0;
    if (g_shell.environ) {
        while (g_shell.environ[g_shell.env_size]) {
            g_shell.env_size++;
        }
    }
    g_shell.exit_status = 0;
}

char **copy_env(char **envp)
{
    int count = 0;
    int i;
    char **new_env;

    if (!envp) {
        return NULL;
    }

    while (envp[count]) {
        count++;
    }

    new_env = malloc((count + 1) * sizeof(char *));
    if (!new_env) {
        return NULL;
    }

    for (i = 0; i < count; i++) {
        new_env[i] = malloc(strlen(envp[i]) + 1);
        if (!new_env[i]) {
            while (--i >= 0) {
                free(new_env[i]);
            }
            free(new_env);
            return NULL;
        }
        strcpy(new_env[i], envp[i]);
    }
    new_env[count] = NULL;

    return new_env;
}

void free_env(void)
{
    int i;

    if (g_shell.environ) {
        for (i = 0; g_shell.environ[i]; i++) {
            free(g_shell.environ[i]);
        }
        free(g_shell.environ);
        g_shell.environ = NULL;
    }
    g_shell.env_size = 0;
}

char *get_env_var(char *name)
{
    int i;
    int len;

    if (!name || !g_shell.environ) {
        return NULL;
    }

    len = strlen(name);
    for (i = 0; g_shell.environ[i]; i++) {
        if (strncmp(g_shell.environ[i], name, len) == 0 &&
            g_shell.environ[i][len] == '=') {
            return g_shell.environ[i] + len + 1;
        }
    }

    return NULL;
}

int set_env_var(char *name, char *value)
{
    int i, name_len, value_len;
    char *new_entry;

    if (!name || !value) {
        return -1;
    }

    name_len = strlen(name);
    value_len = strlen(value);

    for (i = 0; g_shell.environ[i]; i++) {
        if (strncmp(g_shell.environ[i], name, name_len) == 0 &&
            g_shell.environ[i][name_len] == '=') {
            free(g_shell.environ[i]);
            new_entry = malloc(name_len + value_len + 2);
            if (!new_entry) {
                return -1;
            }
            sprintf(new_entry, "%s=%s", name, value);
            g_shell.environ[i] = new_entry;
            return 0;
        }
    }

    g_shell.environ = realloc(g_shell.environ, (g_shell.env_size + 2) * sizeof(char *));
    if (!g_shell.environ) {
        return -1;
    }

    new_entry = malloc(name_len + value_len + 2);
    if (!new_entry) {
        return -1;
    }
    sprintf(new_entry, "%s=%s", name, value);

    g_shell.environ[g_shell.env_size] = new_entry;
    g_shell.environ[g_shell.env_size + 1] = NULL;
    g_shell.env_size++;

    return 0;
}

int unset_env_var(char *name)
{
    int i, j, name_len;

    if (!name || !g_shell.environ) {
        return -1;
    }

    name_len = strlen(name);

    for (i = 0; g_shell.environ[i]; i++) {
        if (strncmp(g_shell.environ[i], name, name_len) == 0 &&
            g_shell.environ[i][name_len] == '=') {
            free(g_shell.environ[i]);
            
            for (j = i; g_shell.environ[j]; j++) {
                g_shell.environ[j] = g_shell.environ[j + 1];
            }
            g_shell.env_size--;
            return 0;
        }
    }

    return 0;
}