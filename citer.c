#include <stdbool.h>
#include <stddef.h> // size_t
#include <stdlib.h> // malloc
#include <string.h> // memcpy


#define FOREACH(iter_type, item_name, iter_name) \
    for (; iter_name.iter_exhausted? 0 : (item_name = iter_type ## _next(&iter_name), 1);)

typedef long long iterint;


typedef struct counti {
    iterint current;
    iterint step;
    bool iter_exhausted;
} counti;

iterint counti_next(counti* count) {
    return count->current += count->step;
}


typedef struct rangei {
    iterint current;
    iterint stop;
    iterint step;
    bool iter_exhausted;
} rangei;

int sign(long long n) {
    return (n > 0) - (n < 0);
}

iterint rangei_next(rangei* range) {
    int ss = sign(range->step);
    iterint old = range->current;

    range->current += range->step;

    if (ss * range->current >= ss * range->stop) {
        range->iter_exhausted = true;
    }

    return old;
}


typedef struct repeati {
    void* to_repeat;
    bool stops;
    iterint times;
    bool iter_exhausted;
} repeati;

void* repeati_next(repeati* repeater) {
    if (repeater->stops && --repeater->times <= 0) {
        repeater->iter_exhausted = true;
    }

    return repeater->to_repeat;
}


typedef struct copyrepeati {
    repeati repeater;
    size_t type_size;
    bool iter_exhausted;
} copyrepeati;

void* copyrepeati_next(copyrepeati* repeater) {
    void* copy = malloc(repeater->type_size);
    memcpy(copy, repeati_next(&repeater->repeater), repeater->type_size);

    repeater->iter_exhausted = repeater->repeater.iter_exhausted;

    return copy;
}

// USAGE //

#include <stdio.h>

int main(void) {
    // Count to 100 by 2s

    iterint num;
    rangei range = {0, 100, 2};
    
    FOREACH (rangei, num, range) {
        printf("%d\n", num);
    }

    // Count down from 10

    range = (rangei) {10, 0, -1};

    FOREACH (rangei, num, range) {
        printf("%d\n", num);
    }

    // test copyrepeati

    void* to_repeat;
    to_repeat = &to_repeat;

    copyrepeati repeater = {{to_repeat, true, 3}, sizeof to_repeat};

    void* item;

    FOREACH (copyrepeati, item, repeater) {
        printf("%p\n", item);
    }

    return 0;
}
