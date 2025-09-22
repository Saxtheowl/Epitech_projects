int main() { char *p = malloc(100); if(p) strcpy(p, "Test with our malloc\!"); printf("%s\n", p); free(p); return 0; }
