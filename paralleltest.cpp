
#include <pthread.h>
#include <stdio.h>

volatile int start = 0;

volatile int x, y, a, b;

void *work1(void *)
{
    while (!start)
        ;
    b = 1;
    x = a;
    return nullptr;
}

void *work2(void *)
{
    while (!start)
        ;
    a = 1;
    y = b;
    return nullptr;
}

int main()
{
    pthread_t t1, t2;

    long i = 0;

    while (true)
    {
        i += 1;
        x = y = a = b = 0;
        start = 0;
        pthread_create(&t1, nullptr, work1, nullptr);
        pthread_create(&t2, nullptr, work2, nullptr);
        start = 1;
        pthread_join(t1, nullptr);
        pthread_join(t2, nullptr);

        if (x == 0 && y == 0)
            break;
    }

    printf("Count %ld. x=%d, y=%d", i, x, y);
    return 0;
}
