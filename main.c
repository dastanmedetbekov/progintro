#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>

#define MAX_SECTIONS 64

typedef struct {
    char name[256];
    int total;
    int done;
} Section;

Section sections[MAX_SECTIONS];
int section_count = 0;
int global_total = 0;
int global_done = 0;

Section* get_section(const char *name) {
    for (int i = 0; i < section_count; i++) {
        if (strcmp(sections[i].name, name) == 0)
            return &sections[i];
    }
    if (section_count >= MAX_SECTIONS) return NULL;
    strncpy(sections[section_count].name, name, 255);
    sections[section_count].total = 0;
    sections[section_count].done = 0;
    return &sections[section_count++];
}

void extract_section(const char *path, char *out, size_t out_size) {
    const char *p = path;
    if (p[0] == '.' && p[1] == '/') p += 2;
    const char *slash = strchr(p, '/');
    if (slash) {
        size_t len = slash - p;
        if (len >= out_size) len = out_size - 1;
        strncpy(out, p, len);
        out[len] = '\0';
    } else {
        strncpy(out, p, out_size - 1);
        out[out_size - 1] = '\0';
    }
}

int has_readme(const char *dir_path) {
    char path[1024];
    snprintf(path, sizeof(path), "%s/README.md", dir_path);
    struct stat st;
    return stat(path, &st) == 0;
}

void check_tasks(const char *dir_path, int depth) {
    struct dirent *entry;
    struct stat path_stat;
    DIR *dir = opendir(dir_path);
    if (!dir) return;

    int has_check = 0;
    int has_rm = has_readme(dir_path);

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0 ||
            strcmp(entry->d_name, ".git") == 0 ||
            strcmp(entry->d_name, "00.Examples") == 0)
            continue;

        char path[1024];
        snprintf(path, sizeof(path), "%s/%s", dir_path, entry->d_name);

        if (stat(path, &path_stat) != 0) continue;

        if (S_ISDIR(path_stat.st_mode)) {
            check_tasks(path, depth + 1);
        } else {
            if (strcmp(entry->d_name, "CHECK") == 0)
                has_check = 1;
        }
    }
    closedir(dir);

    if (depth == 2 && has_rm) {
        char section_name[256];
        extract_section(dir_path, section_name, sizeof(section_name));
        Section *sec = get_section(section_name);
        if (sec) {
            sec->total++;
            global_total++;
            if (has_check) {
                sec->done++;
                global_done++;
            }
        }
    }
}

void print_bar(int done, int total, int width) {
    if (total == 0) { printf("[%*s]", width, ""); return; }
    int filled = (done * width) / total;
    printf("[");
    for (int i = 0; i < width; i++)
        printf(i < filled ? "#" : ".");
    printf("]");
}

int cmp_sections(const void *a, const void *b) {
    return strcmp(((Section*)a)->name, ((Section*)b)->name);
}

int main(int argc, char *argv[]) {
    const char *start_path = (argc > 1) ? argv[1] : ".";

    check_tasks(start_path, 0);

    qsort(sections, section_count, sizeof(Section), cmp_sections);

    printf("\n+------------------------------------------------------+\n");
    printf("|                  BOOK PROGRESS                      |\n");
    printf("+------------------------------------------------------+\n\n");

    int best_idx = 0, worst_idx = 0;
    for (int i = 1; i < section_count; i++) {
        if (sections[i].total == 0) continue;
        double r  = (double)sections[i].done      / sections[i].total;
        double rb = (double)sections[best_idx].done  / sections[best_idx].total;
        double rw = (double)sections[worst_idx].done / sections[worst_idx].total;
        if (r > rb) best_idx  = i;
        if (r < rw) worst_idx = i;
    }

    for (int i = 0; i < section_count; i++) {
        Section *s = &sections[i];
        if (s->total == 0) continue;

        int pct = (s->done * 100) / s->total;
        const char *tag = (pct == 100) ? "[DONE]" : (pct == 0) ? "[    ]" : "[ >> ]";

        printf("  %-22s %s ", s->name, tag);
        print_bar(s->done, s->total, 20);
        printf(" %2d/%-2d (%3d%%)\n", s->done, s->total, pct);
    }

    int gpct = global_total ? (global_done * 100) / global_total : 0;
    printf("\n+------------------------------------------------------+\n");
    printf("  TOTAL   ");
    print_bar(global_done, global_total, 30);
    printf("  %d/%d (%d%%)\n", global_done, global_total, gpct);
    printf("+------------------------------------------------------+\n");
    printf("  Best section  : %s (%d/%d)\n",
        sections[best_idx].name,  sections[best_idx].done,  sections[best_idx].total);
    printf("  Needs work    : %s (%d/%d)\n",
        sections[worst_idx].name, sections[worst_idx].done, sections[worst_idx].total);
    printf("  Remaining     : %d tasks\n\n", global_total - global_done);

    return 0;
}
