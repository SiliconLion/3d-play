#pragma once

#include <stdio.h>
#include <stdlib.h>

//path is a null terminated string of the file path
//sets length to be length of the file in bytes. Pass in NULL to ignore this 
char * readFile(const char* path, int* length) {
    FILE * file = fopen(path, "r");
    if (!file) {
        printf("Unable to open file %s", path);
        length = NULL;
        return NULL;
    }
    fseek(file, 0, SEEK_END);
    int size = ftell(file);

    char * outString = calloc(sizeof(char), size);
    
    fseek(file, 0, 0);
    fread(outString, sizeof(char), size, file); 
    fclose(file);

    if(length) {
        *length = size;
    }

    return outString;
}


//takes a path and returns a pointer to its contents. 
//sets *count to be the number of bytes pointed to. Pass in NULL to ignore this.
int8_t * readBytes(const char* path, int* count) {
    if(!path) {
        printf("error: `path` is a null pointer.\n");
    }
    FILE * file = fopen(path, "rb");
    if (!file) {
        printf("Unable to open file %s\n", path);
        count = NULL;
        return NULL;
    }
    fseek(file, 0, SEEK_END);
    int size = ftell(file);

    int8_t * bytes = calloc(sizeof(int8_t), size);

    fseek(file, 0, 0);
    fread(bytes, sizeof(int8_t), size, file); 
    fclose(file);

    if(count) {
        *count = size;
    }
    return bytes;
}

//writes to the file `path`. writes `count` bytes from `bytes` to the file.
//returns false if fail, true if success.
bool writeBytes(const char* path, int8_t * bytes, int count) {
    if(!path) {
        printf("error: `path` is a null pointer.\n");
        return false;
    }
    FILE * file = fopen(path, "wb+");
    if (!file) {
        printf("Unable to open file %s", path);
        return false;
    }

    fwrite(bytes, 1, count, file);
    return true;
}