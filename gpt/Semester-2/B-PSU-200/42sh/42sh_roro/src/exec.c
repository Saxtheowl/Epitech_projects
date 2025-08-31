/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** Exec, pipelines, conditionals, redirections, builtins
*/

#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include "sh.h"

static int builtin_env(env_t *env, char **argv)
{ int i = 0; (void)argv; while (env->vars && env->vars[i]) { puts(env->vars[i]); i++; } return 0; }
static int builtin_setenv(env_t *env, char **argv)
{ if (!argv[1] || !argv[2]) return 1; return env_set(env, argv[1], argv[2]) ? 0 : 1; }
static int builtin_unsetenv(env_t *env, char **argv)
{ if (!argv[1]) return 1; return env_unset(env, argv[1]) ? 0 : 1; }
static int builtin_cd(env_t *env, char **argv)
{ const char *path = argv[1] ? argv[1] : env_get(env, "HOME"); if (!path || chdir(path) != 0) { perror("cd"); return 1; } return 0; }
static int is_builtin(const char *cmd)
{ return strcmp(cmd, "env") == 0 || strcmp(cmd, "setenv") == 0 || strcmp(cmd, "unsetenv") == 0 || strcmp(cmd, "cd") == 0 || strcmp(cmd, "exit") == 0; }
static int run_builtin(env_t *env, char **argv)
{ if (strcmp(argv[0], "env") == 0) return builtin_env(env, argv); if (strcmp(argv[0], "setenv") == 0) return builtin_setenv(env, argv); if (strcmp(argv[0], "unsetenv") == 0) return builtin_unsetenv(env, argv); if (strcmp(argv[0], "cd") == 0) return builtin_cd(env, argv); if (strcmp(argv[0], "exit") == 0) exit(0); return 1; }

static char *join_path(const char *a, const char *b)
{ size_t la = strlen(a), lb = strlen(b); char *s = malloc(la + 1 + lb + 1); if (!s) return NULL; memcpy(s, a, la); s[la] = '/'; memcpy(s + la + 1, b, lb + 1); return s; }
static char *find_in_path(env_t *env, const char *cmd)
{ char *path, *p, *save; if (strchr(cmd, '/')) return strdup(cmd); path = env_get(env, "PATH"); if (!path) return strdup(cmd); path = strdup(path); if (!path) return NULL; p = strtok_r(path, ":", &save); while (p) { char *full = join_path(p, cmd); if (full && access(full, X_OK) == 0) { free(path); return full; } free(full); p = strtok_r(NULL, ":", &save); } free(path); return strdup(cmd); }

static int filter_redirections(char **argv, char **infile, char **outfile, int *append)
{ int i = 0, j = 0, changed = 0; *infile = NULL; *outfile = NULL; *append = 0; while (argv[i]) { if (strcmp(argv[i], "<") == 0 && argv[i + 1]) { *infile = argv[i + 1]; i += 2; changed = 1; continue; } if (strcmp(argv[i], ">>") == 0 && argv[i + 1]) { *outfile = argv[i + 1]; *append = 1; i += 2; changed = 1; continue; } if (strcmp(argv[i], ">") == 0 && argv[i + 1]) { *outfile = argv[i + 1]; *append = 0; i += 2; changed = 1; continue; } argv[j++] = argv[i++]; } argv[j] = NULL; return changed; }

int run_command(env_t *env, char **argv)
{ pid_t pid; int status; char *prog; if (!argv || !argv[0]) return 0; if (is_builtin(argv[0])) return run_builtin(env, argv); prog = find_in_path(env, argv[0]); if (!prog) return 1; pid = fork(); if (pid == 0) { execve(prog, argv, env->vars); perror(argv[0]); _exit(1); } free(prog); if (pid < 0) return 1; waitpid(pid, &status, 0); return WIFEXITED(status) ? WEXITSTATUS(status) : 1; }

int run_pipeline(env_t *env, char **segments)
{
    int i = 0; int in_fd = -1; int fds[2]; int status = 0; pid_t pid; pid_t last = -1;
    while (segments[i]) {
        char **argv = split_words(segments[i]); int has_next = segments[i + 1] != NULL; if (!argv) return 1; if (has_next && pipe(fds) < 0) { free_words(argv); return 1; }
        pid = fork();
        if (pid == 0) {
            char *infile = NULL, *outfile = NULL; int append = 0; filter_redirections(argv, &infile, &outfile, &append);
            if (in_fd != -1) { dup2(in_fd, 0); close(in_fd); }
            if (has_next) { close(fds[0]); dup2(fds[1], 1); close(fds[1]); }
            if (infile) { int ifd = open(infile, O_RDONLY); if (ifd >= 0) { dup2(ifd, 0); close(ifd); } else { perror(infile); _exit(1); } }
            if (outfile) { int flags = O_WRONLY | O_CREAT | (append ? O_APPEND : O_TRUNC); int ofd = open(outfile, flags, 0644); if (ofd >= 0) { dup2(ofd, 1); close(ofd); } else { perror(outfile); _exit(1); } }
            if (is_builtin(argv[0])) { run_builtin(env, argv); _exit(0); }
            char *prog = find_in_path(env, argv[0]); if (prog) { execve(prog, argv, env->vars); }
            perror(argv[0]); _exit(1);
        }
        if (in_fd != -1)
            close(in_fd);
        if (has_next) {
            close(fds[1]);
            in_fd = fds[0];
        }
        free_words(argv); last = pid; i++;
    }
    if (last != -1)
        waitpid(last, &status, 0);
    while (wait(NULL) > 0) {}
    return WIFEXITED(status) ? WEXITSTATUS(status) : 1;
}

static int run_conditionals(env_t *env, const char *line)
{
    const char *p = line; int code = 0;
    while (*p) {
        const char *start = p; const char *op = NULL; int op_len = 0;
        while (*p) { if (p[0] == '&' && p[1] == '&') { op = p; op_len = 2; break; } if (p[0] == '|' && p[1] == '|' ) { op = p; op_len = 2; break; } p++; }
        size_t len = op ? (size_t)(op - start) : strlen(start); char *chunk = strndup(start, len); int rc; if (!chunk) return 1;
        { char *expanded = expand_vars(env, chunk); if (!expanded) { free(chunk); return 1; } free(chunk); chunk = expanded; }
        if (strchr(chunk, '|')) { char **segs = split_pipeline(chunk); rc = segs ? run_pipeline(env, segs) : 1; if (segs) free_words(segs); }
        else { char **argv = split_words(chunk); rc = argv ? run_command(env, argv) : 1; if (argv) free_words(argv); }
        free(chunk); code = rc; if (!op) break;
        if (op[0] == '&' && code != 0) { p = op + op_len; while (*p) { if ((p[0] == '&' && p[1] == '&') || (p[0] == '|' && p[1] == '|')) break; p++; } }
        else if (op[0] == '|' && code == 0) { p = op + op_len; while (*p) { if ((p[0] == '&' && p[1] == '&') || (p[0] == '|' && p[1] == '|')) break; p++; } }
        else { p = op + op_len; }
    }
    return code;
}

int run_line(env_t *env, const char *line)
{ char **cmds = split_commands(line); int i = 0, code = 0; if (!cmds) return 1; while (cmds[i]) { code = run_conditionals(env, cmds[i]); i++; } free_words(cmds); return code; }
