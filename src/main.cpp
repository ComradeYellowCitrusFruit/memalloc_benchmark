#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <thread>
#include "mem.hpp"
#include "mem_int.hpp"

engine::internals::Pool pool;

void memallocTest()
{
    time_t dur = time(NULL);
    void *ptrs[1048576];

    for(int i = 0; i < 1048576; i++)
        ptrs[i] = engine::memalloc(2048, 0);

    for(int i = 0; i < 1048576; i++)
        engine::memfree(ptrs[i]);

    dur -= time(NULL);
    printf("memalloc: %zu", (size_t)dur);
}

void mallocTest()
{
    time_t dur = time(NULL);
    void *ptrs[524288];

    for(int i = 0; i < 524288; i++)
        ptrs[i] = malloc(2048);

    for(int i = 0; i < 524288; i++)
        free(ptrs[i]);

    dur -= time(NULL);
    printf("malloc: %zu", (size_t)dur);
}

int main()
{
    pool = engine::internals::Pool();
    std::thread mallocThread(mallocTest);
    std::thread memallocThread(memallocTest);
    puts( \
            "Performing a benchmark test on the memalloc function of the Citrus Engine against glibc's malloc.\n" \
            "The test allocates 1GB in 2048 byte blocks, and then frees each block.\n" \
            "Starting the test now.\n" \
    );
    mallocThread.detach();
    memallocThread.detach();
    mallocThread.join();
    memallocThread.join();
}   