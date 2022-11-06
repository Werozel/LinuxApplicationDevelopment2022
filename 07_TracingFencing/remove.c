#define _GNU_SOURCE

#include <dlfcn.h>
#include <string.h>
#include <stdio.h>

typedef int (*remove_ptr)(const char *path);

int remove(const char *path) {
    printf("In remove\n");
    if (strstr(path, "PROTECT") != NULL) {
        return -1;
    }

    remove_ptr old_remove = (remove_ptr) dlsym(RTLD_NEXT, "remove");
    return old_remove(path);
}
