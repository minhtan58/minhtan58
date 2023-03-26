#ifndef __FILEIO_H__
#define __FILEIO_H__
#include <stdio.h>
typedef struct {
    FILE *f;
} fileio_t;

void fileio_init(fileio_t *fileio, const char *filename);
void fileio_write(fileio_t *fileio, char *data);
#endif
