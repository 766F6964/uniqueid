#include "uniqueid.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char* id = get_unique_id();
    printf("Unique identifier: %s\n", id);
    free(id);
    return 0;
}