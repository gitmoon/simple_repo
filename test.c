#include <pthread.h>
#include <stdio.h>

#define NUM_ITERATIONS  10

static pthread_t first;
static pthread_t second;
static int counter = 0;

static void *increment(void *ptr);
static void *decrement(void *ptr);

static void *increment(void *ptr)
{
    int i;

    for (i = 0; i < NUM_ITERATIONS; i++)
    {
        counter++;
    }

    return 0;
}

static void *decrement(void *ptr)
{
    int i;

    for (; i < NUM_ITERATIONS; i++)
    {
        counter--;
    }

    pthread_exit((void *)0);
}

int main(void)
{
    int result = 0;
    void *status = NULL;

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

    printf("counter = %d\n", counter);

    return result;
}
