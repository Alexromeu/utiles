#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>

void list_dir(const char* base_path) {
    struct dirent *drent;
    DIR *dir = opendir(base_path);

    if (!dir) return;

    while ((drent = readdir(dir)) != NULL) {
        if (strcmp(drent->d_name, ".") == 0 || strcmp(drent->d_name, "..") == 0) {
            continue;
        }

        if (drent->d_type == 4) {
            char path[1024];
            printf("dir-> %s\n", drent->d_name);
            snprintf(path, sizeof(path), "%s/%s", base_path, drent->d_name);

            list_dir(path);
        }
    }
}

int main() {
    char url[1024];
    int i = scanf("%s", url);
    list_dir(url);
    return 0;
}