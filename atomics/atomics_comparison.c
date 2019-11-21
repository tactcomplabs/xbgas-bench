// Test file for atomic operation instruction count comparison between xBGAS, OpenSHMEM, & MPI
// XBGAS Atomics: Comparable: xbrtime_typename_atomic_add, xbrtime_typename_atomic_compare_swap
//                Not Comparable: xbrtime_typename_atomic_land, xbrtime_typename_atomic_lor, xbrtime_typename_atomic_xor, xbrtime_typename_atomic_min,
//                                xbrtime_typename_atomic_max
// OpenSHMEM Atomics: Comparable: shmem_typename_atomic_compare_swap, shmem_typename_atomic_inc, shmem_typename_atomic_add,
//                    Not Comparable: shmem_typename_atomic_fetch, shmem_typename_atomic_set, shmem_typename_atomic_swap, shmem_typename_atomic_fetch_inc, shmem_typename_atomic_fetch_add,
//                                    shmem_typename_atomic_fetch_and, shmem_typename_atomic_and, shmem_typename_atomic_fetch_or, shmem_typename_atomic_or, shmem_typename_atomic_fetch_xor, shmem_typename_atomic_xor
// MPI Atomics: Comparable: MPI_fetch_and_op, MPI_compare_and_swap
//              Not Comparable: Comparable: MPI_get_accumulate

#include <stdint.h>

//#define TEST_XBGAS
//#define TEST_SHMEM
//#define TEST_MPI

#ifdef TEST_XBGAS

#include <xbrtime.h>

#define FLAG 0xC000000000000000ull

void xbrtime_atomic_add_test()
{
    xbrtime_init();
    int my_pe = xbrtime_mype();
    int numpes = xbrtime_num_pes();
    int64_t* value = (int64_t*) xbrtime_malloc(sizeof(int64_t));
    *value = my_pe;

    xbrtime_barrier();

    (*((unsigned long long *)(FLAG))) = 1;

    if(my_pe == 0)
    {
        xbrtime_int64_atomic_add(value, 1000000000, 1);
    }

    (*((unsigned long long *)(FLAG))) = 0;

    xbrtime_barrier();
    xbrtime_free(value);
    xbrtime_close();
}

void xbrtime_atomic_inc_test()
{
    xbrtime_init();
    int my_pe = xbrtime_mype();
    int numpes = xbrtime_num_pes();
    int64_t* value = (int64_t*) xbrtime_malloc(sizeof(int64_t));
    *value = my_pe;

    xbrtime_barrier();

    (*((unsigned long long *)(FLAG))) = 1;

    if(my_pe == 0)
    {
        xbrtime_int64_atomic_add(value, 1, 1);
    }

    (*((unsigned long long *)(FLAG))) = 0;

    xbrtime_barrier();
    xbrtime_free(value);
    xbrtime_close();
}

void xbrtime_atomic_compare_swap_test()
{
    xbrtime_init();
    int my_pe = xbrtime_mype();
    int numpes = xbrtime_num_pes();
    int64_t* value = (int64_t*) xbrtime_malloc(sizeof(int64_t));
    *value = my_pe;

    xbrtime_barrier();

    (*((unsigned long long *)(FLAG))) = 1;

    if(my_pe == 0)
    {
        xbrtime_int64_atomic_compare_swap(value, 1, 1);
    }

    (*((unsigned long long *)(FLAG))) = 0;

    xbrtime_barrier();
    xbrtime_free(value);
    xbrtime_close();
}

void xbrtime_atomic_land_test()
{
    xbrtime_init();
    int my_pe = xbrtime_mype();
    int numpes = xbrtime_num_pes();
    int64_t* value = (int64_t*) xbrtime_malloc(sizeof(int64_t));
    *value = my_pe;

    xbrtime_barrier();

    (*((unsigned long long *)(FLAG))) = 1;

    if(my_pe == 0)
    {
        xbrtime_int64_atomic_land(value, *value, 1);
    }

    (*((unsigned long long *)(FLAG))) = 0;

    xbrtime_barrier();
    xbrtime_free(value);
    xbrtime_close();
}

void xbrtime_atomic_lor_test()
{
    xbrtime_init();
    int my_pe = xbrtime_mype();
    int numpes = xbrtime_num_pes();
    int64_t* value = (int64_t*) xbrtime_malloc(sizeof(int64_t));
    *value = my_pe;

    xbrtime_barrier();

    (*((unsigned long long *)(FLAG))) = 1;

    if(my_pe == 0)
    {
        xbrtime_int64_atomic_lor(value, *value, 1);
    }

    (*((unsigned long long *)(FLAG))) = 0;

    xbrtime_barrier();
    xbrtime_free(value);
    xbrtime_close();
}

void xbrtime_atomic_lxor_test()
{
    xbrtime_init();
    int my_pe = xbrtime_mype();
    int numpes = xbrtime_num_pes();
    int64_t* value = (int64_t*) xbrtime_malloc(sizeof(int64_t));
    *value = my_pe;

    xbrtime_barrier();

    (*((unsigned long long *)(FLAG))) = 1;

    if(my_pe == 0)
    {
        xbrtime_int64_atomic_lxor(value, *value, 1);
    }

    (*((unsigned long long *)(FLAG))) = 0;

    xbrtime_barrier();
    xbrtime_free(value);
    xbrtime_close();
}

void xbrtime_atomic_min_test()
{
    xbrtime_init();
    int my_pe = xbrtime_mype();
    int numpes = xbrtime_num_pes();
    uint64_t* value = (uint64_t*) xbrtime_malloc(sizeof(uint64_t));
    *value = my_pe;

    xbrtime_barrier();

    (*((unsigned long long *)(FLAG))) = 1;

    if(my_pe == 0)
    {
        xbrtime_uint64_atomic_min(value, *value, 1);
    }

    (*((unsigned long long *)(FLAG))) = 0;

    xbrtime_barrier();
    xbrtime_free(value);
    xbrtime_close();
}

void xbrtime_atomic_max_test()
{
    xbrtime_init();
    int my_pe = xbrtime_mype();
    int numpes = xbrtime_num_pes();
    uint64_t* value = (uint64_t*) xbrtime_malloc(sizeof(uint64_t));
    *value = my_pe;

    xbrtime_barrier();

    (*((unsigned long long *)(FLAG))) = 1;

    if(my_pe == 0)
    {
        xbrtime_uint64_atomic_max(value, *value, 1);
    }

    (*((unsigned long long *)(FLAG))) = 0;

    xbrtime_barrier();
    xbrtime_free(value);
    xbrtime_close();
}

#undef TEST_XBGAS
#endif

#ifdef TEST_SHMEM

#include <shmem.h>
#include "test.h"

// SHMEM tests use long long type because OSHMEM (OpenMPI OpenSHMEM) doesn't like the int64 typename in atomic calls

void shmem_atomic_add_test()
{
    shmem_init();
    perf_init();
    int my_pe = shmem_my_pe();
    int numpes = shmem_n_pes();
    long long* value = (long long*) shmem_malloc(sizeof(long long));
    *value = my_pe;

    shmem_barrier_all();

    if(my_pe == 0)
    {
        test_start();
        shmem_longlong_atomic_add(value, 1000000000, 1);
        test_end();
    }

    shmem_barrier_all();
    shmem_free(value);
    perf_end();
    shmem_finalize();
}

void shmem_atomic_inc_test()
{
    shmem_init();
    perf_init();
    int my_pe = shmem_my_pe();
    int numpes = shmem_n_pes();
    long long* value = (long long*) shmem_malloc(sizeof(long long));
    *value = my_pe;

    shmem_barrier_all();

    if(my_pe == 0)
    {
        test_start();
        shmem_longlong_atomic_inc(value, 1);
        test_end();
    }

    shmem_barrier_all();
    shmem_free(value);
    perf_end();
    shmem_finalize();
}

void shmem_atomic_compare_swap_test()
{
    shmem_init();
    perf_init();
    int my_pe = shmem_my_pe();
    int numpes = shmem_n_pes();
    long long* value = (long long*) shmem_malloc(sizeof(long long));
    *value = my_pe;

    shmem_barrier_all();

    if(my_pe == 0)
    {
        test_start();
        shmem_longlong_atomic_compare_swap(value, 1, *value, 1);
        test_end();
    }

    shmem_barrier_all();
    shmem_free(value);
    perf_end();
    shmem_finalize();
}

#undef TEST_SHMEM
#endif

#ifdef TEST_MPI

#include <mpi.h>
#include "test.h"

void mpi_atomic_add_test()
{
    MPI_Init(NULL, NULL);
    perf_init();
    int my_pe, numpes;
    MPI_Win window;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_pe);
    MPI_Comm_size(MPI_COMM_WORLD, &numpes);
    int64_t result, value;

    if(my_pe == 1)
    {
        value = 1;
    }
    else
    {
        value = 1000000000;
    }

    MPI_Win_create(&value, sizeof(int64_t), sizeof(int64_t), MPI_INFO_NULL, MPI_COMM_WORLD, &window);

    MPI_Barrier(MPI_COMM_WORLD);

    if(my_pe == 0)
    {
        MPI_Win_lock_all(0, window);
        test_start();
        MPI_Fetch_and_op(&value, &result, MPI_INT64_T, 1, 0, MPI_SUM, window);
        test_end();
        MPI_Win_flush_all(window);
        MPI_Win_unlock_all(window);
    }

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Win_free(&window);
    perf_end();
    MPI_Finalize();
}

void mpi_atomic_inc_test()
{
    MPI_Init(NULL, NULL);
    perf_init();
    int my_pe, numpes;
    MPI_Win window;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_pe);
    MPI_Comm_size(MPI_COMM_WORLD, &numpes);
    int64_t result, value;
    value = 1;

    MPI_Win_create(&value, sizeof(int64_t), sizeof(int64_t), MPI_INFO_NULL, MPI_COMM_WORLD, &window);

    MPI_Barrier(MPI_COMM_WORLD);

    if(my_pe == 0)
    {
        MPI_Win_lock_all(0, window);
        test_start();
        MPI_Fetch_and_op(&value, &result, MPI_INT64_T, 1, 0, MPI_SUM, window);
        test_end();
        MPI_Win_flush_all(window);
        MPI_Win_unlock_all(window);
    }

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Win_free(&window);
    perf_end();
    MPI_Finalize();
}

void mpi_atomic_compare_swap_test()
{
    MPI_Init(NULL, NULL);
    perf_init();
    int my_pe, numpes;
    MPI_Win window;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_pe);
    MPI_Comm_size(MPI_COMM_WORLD, &numpes);
    int64_t result, value, compare;
    value = my_pe;
    compare = 1;

    MPI_Win_create(&value, sizeof(int64_t), sizeof(int64_t), MPI_INFO_NULL, MPI_COMM_WORLD, &window);

    MPI_Barrier(MPI_COMM_WORLD);

    if(my_pe == 0)
    {
        MPI_Win_lock_all(0, window);
        test_start();
        MPI_Compare_and_swap(&value, &compare, &result, MPI_INT64_T, 1, 0, window);
        test_end();
        MPI_Win_flush_all(window);
        MPI_Win_unlock_all(window);
    }

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Win_free(&window);
    perf_end();
    MPI_Finalize();
}

void mpi_atomic_land_test()
{
    MPI_Init(NULL, NULL);
    perf_init();
    int my_pe, numpes;
    MPI_Win window;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_pe);
    MPI_Comm_size(MPI_COMM_WORLD, &numpes);
    int64_t result, value;
    value = my_pe;

    MPI_Win_create(&value, sizeof(int64_t), sizeof(int64_t), MPI_INFO_NULL, MPI_COMM_WORLD, &window);

    MPI_Barrier(MPI_COMM_WORLD);

    if(my_pe == 0)
    {
        MPI_Win_lock_all(0, window);
        test_start();
        MPI_Fetch_and_op(&value, &result, MPI_INT64_T, 1, 0, MPI_LAND, window);
        test_end();
        MPI_Win_flush_all(window);
        MPI_Win_unlock_all(window);
    }

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Win_free(&window);
    perf_end();
    MPI_Finalize();
}

void mpi_atomic_lor_test()
{
    MPI_Init(NULL, NULL);
    perf_init();
    int my_pe, numpes;
    MPI_Win window;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_pe);
    MPI_Comm_size(MPI_COMM_WORLD, &numpes);
    int64_t result, value;
    value = my_pe;

    MPI_Win_create(&value, sizeof(int64_t), sizeof(int64_t), MPI_INFO_NULL, MPI_COMM_WORLD, &window);

    MPI_Barrier(MPI_COMM_WORLD);

    if(my_pe == 0)
    {
        MPI_Win_lock_all(0, window);
        test_start();
        MPI_Fetch_and_op(&value, &result, MPI_INT64_T, 1, 0, MPI_LOR, window);
        test_end();
        MPI_Win_flush_all(window);
        MPI_Win_unlock_all(window);
    }

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Win_free(&window);
    perf_end();
    MPI_Finalize();
}

void mpi_atomic_lxor_test()
{
    MPI_Init(NULL, NULL);
    perf_init();
    int my_pe, numpes;
    MPI_Win window;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_pe);
    MPI_Comm_size(MPI_COMM_WORLD, &numpes);
    int64_t result, value;
    value = my_pe;

    MPI_Win_create(&value, sizeof(int64_t), sizeof(int64_t), MPI_INFO_NULL, MPI_COMM_WORLD, &window);

    MPI_Barrier(MPI_COMM_WORLD);

    if(my_pe == 0)
    {
        MPI_Win_lock_all(0, window);
        test_start();
        MPI_Fetch_and_op(&value, &result, MPI_INT64_T, 1, 0, MPI_LXOR, window);
        test_end();
        MPI_Win_flush_all(window);
        MPI_Win_unlock_all(window);
    }

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Win_free(&window);
    perf_end();
    MPI_Finalize();
}

void mpi_atomic_min_test()
{
    MPI_Init(NULL, NULL);
    perf_init();
    int my_pe, numpes;
    MPI_Win window;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_pe);
    MPI_Comm_size(MPI_COMM_WORLD, &numpes);
    int64_t result, value;
    value = my_pe;

    MPI_Win_create(&value, sizeof(int64_t), sizeof(int64_t), MPI_INFO_NULL, MPI_COMM_WORLD, &window);

    MPI_Barrier(MPI_COMM_WORLD);

    if(my_pe == 0)
    {
        MPI_Win_lock_all(0, window);
        test_start();
        MPI_Fetch_and_op(&value, &result, MPI_INT64_T, 1, 0, MPI_MIN, window);
        test_end();
        MPI_Win_flush_all(window);
        MPI_Win_unlock_all(window);
    }

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Win_free(&window);
    perf_end();
    MPI_Finalize();
}

void mpi_atomic_max_test()
{
    MPI_Init(NULL, NULL);
    perf_init();
    int my_pe, numpes;
    MPI_Win window;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_pe);
    MPI_Comm_size(MPI_COMM_WORLD, &numpes);
    int64_t result, value;
    value = my_pe;

    MPI_Win_create(&value, sizeof(int64_t), sizeof(int64_t), MPI_INFO_NULL, MPI_COMM_WORLD, &window);

    MPI_Barrier(MPI_COMM_WORLD);

    if(my_pe == 0)
    {
        MPI_Win_lock_all(0, window);
        test_start();
        MPI_Fetch_and_op(&value, &result, MPI_INT64_T, 1, 0, MPI_MAX, window);
        test_end();
        MPI_Win_flush_all(window);
        MPI_Win_unlock_all(window);
    }

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Win_free(&window);
    perf_end();
    MPI_Finalize();
}

#undef TEST_MPI
#endif

void main()
{
    //xbrtime_atomic_add_test();
    //xbrtime_atomic_inc_test();
    //xbrtime_atomic_compare_swap_test();
    //xbrtime_atomic_land_test();
    //xbrtime_atomic_lor_test();
    //xbrtime_atomic_lxor_test();
    //xbrtime_atomic_min_test();
    //xbrtime_atomic_max_test();
    //shmem_atomic_add_test();
    //shmem_atomic_inc_test();
    //shmem_atomic_compare_swap_test();
    //mpi_atomic_add_test();
    //mpi_atomic_inc_test();
    //mpi_atomic_compare_swap_test();
    //mpi_atomic_land_test();
    //mpi_atomic_lor_test();
    //mpi_atomic_lxor_test();
    //mpi_atomic_min_test();
    //mpi_atomic_max_test();
}
