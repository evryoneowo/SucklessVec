#include <stddef.h>

#define vec_push(vec, element) \
    ({ \
        __typeof__(element) _tmp = (element); \
        (vec) = _vec_push((vec), &_tmp); \
    })
#define vec_insert(vec, element, index) \
    ({ \
        __typeof__(element) _tmp = (element); \
        (vec) = _vec_insert((vec), &_tmp, (index)); \
    })

void* vec_init(size_t esz);
void vec_free(void *v);
void vec_delete(void *v, size_t index);
size_t vec_len(void *v);

void* _vec_push(void *v, void *element);
void* _vec_insert(void *v, void *element, size_t index);
