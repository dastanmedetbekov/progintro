#include <stdio.h>
#include <stdlib.h>

struct files {
    char *name;
    long offset;
    size_t max_line_len;
};

void cleaner(struct files *s) {
    free(s);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        return 1;
    }
    size_t g_max_len = 0;
    
    struct files *s = malloc((argc - 1) * sizeof(struct files));
    
    for (int i = 1; i < argc; i++) {
       int y = i - 1;
       size_t current_line_len = 0;
       long curent_line_offset = 0;
       s[y].name = argv[i];
       s[y].offset = 0;
       s[y].max_line_len = 0;

       FILE *f = fopen(argv[i], "r");
       if (f == NULL) {
           cleaner(s);
           return 1;
       }

       int ch;

       while ((ch = fgetc(f)) != EOF) {
           if (ch != '\n') {
               current_line_len++;
           } else {
               if (current_line_len > s[y].max_line_len) {
                   s[y].max_line_len = current_line_len;
                   s[y].offset = curent_line_offset;
               }
            curent_line_offset = ftell(f);
            current_line_len = 0;
           }
       }
       if (current_line_len > s[y].max_line_len) {
           s[y].max_line_len = current_line_len;
           s[y].offset = curent_line_offset;
       }

       fclose(f);
       if (s[y].max_line_len > g_max_len) {
           g_max_len = s[y].max_line_len;
       }
    }

    for (int i = 0; i < argc - 1; i++) {
        FILE *f = fopen(s[i].name, "r");
        if (f == NULL) {
            continue;
        }

        fseek(f, s[i].offset, SEEK_SET);
        
        if (s[i].max_line_len == g_max_len) {
            putchar('*');
        }

        printf("%s: ", s[i].name);

        for (size_t j = 0; j < s[i].max_line_len; j++) {
            putchar(fgetc(f));
        }

        putchar('\n');
        fclose(f);
    }
    putchar('\n');
    cleaner(s);
    return 0;

}

