#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "svec.h"

#define VEC_HDR(v) ((vector *)((char *)(v) - sizeof(vector)))

typedef struct {
    size_t cap;
    size_t len;
    size_t esz;
} vector;

void* vec_init(size_t esz) {
    vector *vec = malloc(sizeof(vector) + esz * 4);
    if (!vec) return NULL;

    vec->cap = 4;
    vec->len = 0;
    vec->esz = esz;

    return (char *)vec + sizeof(vector);
}

void vec_free(void *v) {
    if (!v) return;
    free(VEC_HDR(v));
}

void* _vec_push(void *v, void *element) {
    vector *vec = VEC_HDR(v);

    if (!vec) return NULL;

    if (vec->cap == vec->len) {
        size_t new_cap = vec->cap * 2;
        vector *tmp = realloc(vec, sizeof(vector) + new_cap * vec->esz);

        if (!tmp) return v;
        
        vec = tmp;
        vec->cap = new_cap;
    }

    void *data = (char *)vec + sizeof(vector);
    memcpy((char *)data + vec->len * vec->esz, element, vec->esz);
    vec->len++;

    return data;
}

void vec_pop(void *v) {
    vector *vec = VEC_HDR(v);

    if (!vec || vec->len == 0) return;
    
    vec->len--;
}

void vec_delete(void *v, size_t index) {
    vector *vec = VEC_HDR(v);

    if (!vec || vec->len == 0 || vec->len <= index) return;
    
    char *data = (char *)v;

    memmove((char *)data + index * vec->esz, (char *)data + (index + 1) * vec->esz, vec->esz * (vec->len - index - 1));
    vec->len--;
}

void* _vec_insert(void *v, void *element, size_t index) {
    vector *vec = VEC_HDR(v);
    
    if (!vec || vec->len < index) return v;

    if (vec->cap == vec->len) {
        size_t new_cap = vec->cap * 2;
        void *tmp = realloc(vec, sizeof(vector) + new_cap * vec->esz);

        if (!tmp) return v;
    
        vec = tmp;
        vec->cap = new_cap;
    }
    
    char *data = (char *)vec + sizeof(vector);
    memmove((char *)data + (index + 1) * vec->esz, (char *)data + index * vec->esz, vec->esz * (vec->len - index));
    vec->len++;

    memcpy((char *)data + index * vec->esz, element, vec->esz);

    return data;
}

size_t vec_len(void *v) {
    if (!v) return 0;
    
    vector *vec = VEC_HDR(v);

    return vec->len;
}
