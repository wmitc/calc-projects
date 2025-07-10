#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#include "tpool.h"

static const size_t num_threads = 4;
static const size_t num_items   = 10;

pthread_mutex_t print_mutex = PTHREAD_MUTEX_INITIALIZER;

void worker(void *arg)
{
    int *val = arg;
    int  old = *val;

    *val += 1000;
    pthread_mutex_lock(&print_mutex);
    printf("tid=%p, old=%d, val=%d\n", pthread_self(), old, *val);
    pthread_mutex_unlock(&print_mutex);

    if (*val%2)
        usleep(100000);
}

typedef struct {
    const char *str1;
    const char *str2;
    const char *str3;
} string_triplet_t;


void print_strings_worker(void *arg) {
    string_triplet_t *triplet = (string_triplet_t *)arg;

    //pthread_mutex_lock(&print_mutex);
    if (triplet) {
        printf("String 1: %s\n", triplet->str1);
        printf("String 2: %s\n", triplet->str2);
        printf("String 3: %s\n", triplet->str3);
    } else {
        printf("Worker received null argument.\n");
    }
    //pthread_mutex_unlock(&print_mutex);

    return NULL;
}


int main(int argc, char **argv)
{
    tpool_t *tm;
    int     *vals;
    size_t   i;


    tm   = tpool_create(num_threads);
    vals = calloc(num_items, sizeof(*vals));


    string_triplet_t *data = malloc(sizeof(string_triplet_t));
    data->str1 = "Hello";
    data->str2 = "from";
    data->str3 = "worker!";

    tpool_add_work(tm, print_strings_worker, data);

    for (i=0; i<num_items; i++) {
        vals[i] = i;
        tpool_add_work(tm, worker, vals+i);
    }

    tpool_wait(tm);

    free(data);

    for (i=0; i<num_items; i++) {
        //pthread_mutex_lock(&print_mutex);
        printf("%d\n", vals[i]);
        //pthread_mutex_unlock(&print_mutex);
    }

    free(vals);
    tpool_destroy(tm);
    return 0;
}
