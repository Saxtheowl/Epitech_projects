#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "../include/sok.h"

static char *read_file(const char *path, size_t *out_len)
{
    int fd = open(path, O_RDONLY);
    if (fd < 0) return NULL;
    size_t cap = 8192, len = 0; char *buf = malloc(cap);
    if (!buf) { close(fd); return NULL; }
    for (;;) {
        if (len == cap) { cap *= 2; char *nb = realloc(buf, cap); if(!nb){free(buf); close(fd); return NULL;} buf = nb; }
        ssize_t r = read(fd, buf + len, cap - len);
        if (r < 0) { free(buf); close(fd); return NULL; }
        if (r == 0) break;
        len += (size_t)r;
    }
    close(fd); if (out_len) *out_len = len; return buf;
}

int load_map(const char *path, map_t *m)
{
    memset(m, 0, sizeof(*m));
    size_t len=0; char *data = read_file(path, &len);
    if (!data || len==0) { free(data); return 84; }
    // compute width as max line length, height as number of lines
    int w = 0, h = 0, cw = 0;
    for (size_t i=0;i<len;i++) { if (data[i]=='\n'){ if (cw>w) w=cw; cw=0; h++; } else cw++; }
    if (cw>0){ h++; if (cw>w) w=cw; }
    if (w<=0 || h<=0) { free(data); return 84; }
    char *cells = malloc((size_t)w*(size_t)h);
    char *targets = calloc((size_t)w*(size_t)h, 1);
    if (!cells || !targets){ free(data); free(cells); free(targets); return 84; }
    int px=-1, py=-1; size_t pos=0; int y=0, x=0;
    for (; y<h; y++) {
        x=0;
        for (; x<w; x++) {
            char ch=' ';
            if (pos < len && data[pos] != '\n') { ch = data[pos++]; }
            else ch=' ';
            if (pos < len && data[pos]=='\n' && x==w-1) pos++;
            if (ch=='P'){ px=x; py=y; ch=' '; }
            if (ch=='O'){ targets[y*w + x]=1; ch=' '; }
            if (ch!='#' && ch!='X' && ch!=' ') { free(data); free(cells); free(targets); return 84; }
            cells[y*w + x] = ch;
        }
        if (pos<len && data[pos]=='\n') pos++;
    }
    free(data);
    if (px<0 || py<0) { free(cells); free(targets); return 84; }
    m->w=w; m->h=h; m->cells=cells; m->targets=targets; m->px=px; m->py=py; return 0;
}

void free_map(map_t *m)
{
    if (!m) return;
    free(m->cells);
    free(m->targets);
    memset(m,0,sizeof(*m));
}

int is_win(const map_t *m)
{
    for (int y=0;y<m->h;y++) for (int x=0;x<m->w;x++){
        int i=y*m->w+x; if (m->targets[i] && m->cells[i] != 'X') return 0;
    }
    return 1;
}
