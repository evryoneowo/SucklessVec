#include <stdio.h>
#include <stdlib.h>

#include "svec.h"

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    printf("How much numbers to sort?\n");

    int n;
    scanf("%d", &n);
    
    printf("\nOK. Now, please, input %d numbers:\n", n);

    int *vec = vec_init(sizeof(int));
    
    int num;
    for (int i = 0; i < n; i++) {
        printf("#%d: ", i+1);
        scanf("%d", &num);

        vec_push(vec, num);
    }

    qsort(vec, vec_len(vec), sizeof(int), compare);

    printf("Sorted nums: \n{");
    for (size_t i = 0; i < vec_len(vec); i++) {
        printf("%d", vec[i]);

        if (i < vec_len(vec) - 1) {
            printf(", ");
        }
    }

    printf("}\n");

    vec_free(vec);

    return 0;
}
