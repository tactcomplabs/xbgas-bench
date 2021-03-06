#include "xbrtime.h"

#define NELEMS 10000
#define TEST_BROADCAST_TREE
//#define TEST_BROADCAST_VDG
//#define TEST_PUT_LOOP
//#define TEST_REDUCE_TREE
//#define TEST_REDUCE_RABEN
//#define TEST_GET_LOOP

int main()
{
    xbrtime_init();
    int i, my_pe, *b_vals, *dest_vals;
    my_pe = xbrtime_mype();
    b_vals = (int*) xbrtime_malloc(sizeof(int)*NELEMS);
    dest_vals = (int*) xbrtime_malloc(sizeof(int)*NELEMS);

    for(i = 0; i < NELEMS; i++){
        b_vals[i] = my_pe;
        dest_vals[i] = 999;
    }

    printf("Pre-Op - PE:%d b_vals[0]: %d b_vals[NELEMS-1]: %d dest_vals[0]: %d dest_vals[NELEMS-1]: %d\n",
            my_pe, b_vals[0], b_vals[NELEMS-1], dest_vals[0], dest_vals[NELEMS-1]);

    xbrtime_barrier();

#ifdef TEST_BROADCAST_TREE
    xbrtime_int_broadcast_tree(dest_vals, b_vals, NELEMS, 1, 0);
#elif defined (TEST_BROADCAST_VDG)
    xbrtime_int_broadcast_van_de_geijn(dest_vals, b_vals, NELEMS, 1, 0);
#elif defined (TEST_PUT_LOOP)
    if(my_pe == 0)
        for(i = 1 ; i < xbrtime_num_pes(); i++){
            xbrtime_int_put(dest_vals, b_vals, NELEMS, 1, my_pe+i);
    }
#elif defined (TEST_REDUCE_TREE)
    xbrtime_int_reduce_sum_tree(dest_vals, b_vals, NELEMS, 1, 0);
#elif defined (TEST_REDUCE_RABEN)
    xbrtime_int_reduce_sum_rabenseifner(dest_vals, b_vals, NELEMS, 1, 0);
#elif defined (TEST_GET_LOOP)
    if(my_pe == 0)
        for(i = 1 ; i < xbrtime_num_pes(); i++){
            xbrtime_int_get(dest_vals, b_vals, NELEMS, 1, my_pe+i);
    }
#endif

    xbrtime_barrier();

    printf("Post-Op - PE:%d b_vals[0]: %d b_vals[NELEMS-1]: %d dest_vals[0]: %d dest_vals[NELEMS-1]: %d\n",
            my_pe, b_vals[0], b_vals[NELEMS-1], dest_vals[0], dest_vals[NELEMS-1]);

    xbrtime_free(b_vals);
    xbrtime_free(dest_vals);

    xbrtime_close();

    return 0;
}
