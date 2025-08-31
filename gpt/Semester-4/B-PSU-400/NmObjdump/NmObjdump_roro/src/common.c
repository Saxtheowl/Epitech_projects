/*
** EPITECH PROJECT, 2025
** NmObjdump_roro
** File description:
** common
*/

#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include "common.h"
#include <ctype.h>

void *xmalloc(size_t n)
{
    void *p = malloc(n);
    if (!p) {
        fprintf(stderr, "Memory allocation failure\n");
        exit(84);
    }
    return p;
}

static int map_whole(int fd, unsigned char **data, size_t *size)
{
    struct stat st;
    ssize_t rd;
    if (fstat(fd, &st) == -1)
        return 84;
    *size = (size_t)st.st_size;
    *data = xmalloc(*size);
    rd = read(fd, *data, *size);
    if (rd < 0 || (size_t)rd != *size)
        return 84;
    return 0;
}

int is_ar(const unsigned char *p, size_t n)
{
    const unsigned char sig[] = "!<arch>\n";
    return (n >= sizeof(sig) - 1 && memcmp(p, sig, sizeof(sig) - 1) == 0);
}

static size_t parse_decimal(const unsigned char *p, size_t len)
{
    size_t v = 0;
    size_t i;
    for (i = 0; i < len; ++i) {
        if (p[i] < '0' || p[i] > '9')
            continue;
        v = v * 10 + (p[i] - '0');
    }
    return v;
}

/* GNU ar header format */
typedef struct {
    char name[16];
    char mtime[12];
    char uid[6];
    char gid[6];
    char mode[8];
    char size[10];
    char fmag[2];
} ar_hdr_t;

int ar_iterate(const file_t *ar, ar_iter_cb cb, void *ctx)
{
    const unsigned char *p = ar->data;
    const unsigned char *end = ar->data + ar->size;
    const unsigned char *cur;
    const char *strtab = NULL;
    size_t strtab_size = 0;

    if (!is_ar(p, ar->size))
        return 84;
    cur = p + 8; /* skip signature */
    while (cur + sizeof(ar_hdr_t) <= end) {
        const ar_hdr_t *h = (const ar_hdr_t *)cur;
        size_t fsize = parse_decimal((const unsigned char *)h->size, sizeof(h->size));
        const unsigned char *mdata = cur + sizeof(ar_hdr_t);
        const unsigned char *next = mdata + fsize + (fsize & 1);
        const char *name = NULL;
        char name_buf[128];

        if (next > end)
            break;

        if (h->name[0] == '/' && h->name[1] == '/' ) {
            /* GNU string table */
            strtab = (const char *)mdata;
            strtab_size = fsize;
        } else if (h->name[0] == '/' && h->name[1] == ' ') {
            /* symbol table, skip */
        } else if (h->name[0] == '/' && isdigit((unsigned char)h->name[1])) {
            /* long name reference into string table */
            size_t off = parse_decimal((const unsigned char *)&h->name[1], 15);
            if (strtab && off < strtab_size) {
                const char *s = strtab + off;
                size_t i = 0;
                while (off + i < strtab_size && s[i] != '/' && s[i] != '\n' && i + 1 < sizeof(name_buf)) {
                    name_buf[i] = s[i];
                    i++;
                }
                name_buf[i] = '\0';
                name = name_buf;
            }
        } else if (h->name[0] == '#' && h->name[1] == '1' && h->name[2] == '/') {
            /* BSD extended name length after '#1/' */
            size_t nlen = parse_decimal((const unsigned char *)&h->name[3], 13);
            if (nlen < sizeof(name_buf) && nlen <= fsize) {
                memcpy(name_buf, mdata, nlen);
                name_buf[nlen] = '\0';
                name = name_buf;
                mdata += nlen;
                fsize -= nlen;
            }
        } else {
            /* normal name, might end with '/' */
            size_t i;
            for (i = 0; i < sizeof(h->name) && h->name[i] != ' ' && h->name[i] != '/'; ++i)
                name_buf[i] = h->name[i];
            name_buf[i] = '\0';
            name = name_buf;
        }

        if (name && mdata + fsize <= end) {
            ar_member_t m = { name, mdata, fsize };
            int rc = cb(ar->path, &m, ctx);
            if (rc != 0)
                return rc;
        }
        cur = next;
    }
    return 0;
}

int open_file(const char *path, file_t *out)
{
    memset(out, 0, sizeof(*out));
    out->path = path;
    out->fd = open(path, O_RDONLY);
    if (out->fd < 0)
        return 84;
    if (map_whole(out->fd, &out->data, &out->size) != 0)
        return 84;
    if (out->size >= 4 && out->data[0] == 0x7f && out->data[1] == 'E' && out->data[2] == 'L' && out->data[3] == 'F') {
        unsigned char cls = out->data[4];
        if (cls == ELFCLASS64) {
            out->kind = BIN_ELF64;
            out->u.e64.eh = (Elf64_Ehdr *)out->data;
            out->u.e64.sh = (Elf64_Shdr *)(out->data + out->u.e64.eh->e_shoff);
            out->u.e64.shnum = out->u.e64.eh->e_shnum;
        } else if (cls == ELFCLASS32) {
            out->kind = BIN_ELF32;
            out->u.e32.eh = (Elf32_Ehdr *)out->data;
            out->u.e32.sh = (Elf32_Shdr *)(out->data + out->u.e32.eh->e_shoff);
            out->u.e32.shnum = out->u.e32.eh->e_shnum;
        } else {
            out->kind = BIN_UNKNOWN;
        }
    } else if (is_ar(out->data, out->size)) {
        out->kind = BIN_AR;
    } else {
        out->kind = BIN_UNKNOWN;
        return 84;
    }
    return 0;
}

void close_file(file_t *f)
{
    if (f->data)
        free(f->data);
    if (f->fd >= 0)
        close(f->fd);
}
