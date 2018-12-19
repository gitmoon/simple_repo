#include <pthread.h>
#include <stdio.h>

#define NUM_ITERATIONS  10

static pthread_t first;
static pthread_t second;


static void *increment(void *ptr);
static void *decrement(void *ptr);

pthread_mutex_t lock;

static void *increment(void *ptr)
{
    pthread_mutex_lock(&lock);
    int *local_counter = (int*)ptr;
    for (int i = 0; i < NUM_ITERATIONS; i++)
    {
        (*local_counter)++;
    }
    pthread_mutex_unlock(&lock);
    pthread_exit(NULL);
}

static void *decrement(void *ptr)
{
    pthread_mutex_lock(&lock);
    int *local_counter = (int*)ptr;
    for (int i = 0; i < NUM_ITERATIONS; i++)
    {
        (*local_counter)--;
    }
    pthread_mutex_unlock(&lock);
    pthread_exit(NULL);
}

int main(void)
{
    int counter = 0;
    int result = 0;
    void *status = NULL;

    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        return 1;
    }

    if (0 != pthread_create(&first, NULL, increment, &counter))
    {
        fprintf(stderr, "Error creating first thread\n");
        result = 1;
    }

    if (0 == result)
    {
        if (0 != pthread_create(&second, NULL, decrement, &counter))
        {
            fprintf(stderr, "Error creating second thread\n");
            result = 1;
        }
    }

    if (0 == result)
    {
        if (0 != pthread_join(first, &status))
        {
            fprintf(stderr, "Error failed to join first\n");
            result = 1;
        }
    }

    if (0 == result)
    {
        if (0 != pthread_join(second, &status))
        {
            fprintf(stderr, "Error failed to join second\n");
            result = 1;
        }
    }

    pthread_mutex_destroy(&lock);
    printf("\ncounter = %d\n", counter);
    return result;
}
