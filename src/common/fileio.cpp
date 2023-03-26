#include "fileio.h"
#include <stdlib.h>
void fileio_init(fileio_t *fileio, const char *filename) {
    fileio->f = fopen(filename, "w");
    if (fileio->f == NULL) exit(-1);
}

void fileio_write(fileio_t *fileio, char *data) {
    fprintf(fileio->f, "%s\n", data);
    fflush(fileio->f);
}
