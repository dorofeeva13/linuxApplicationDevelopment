#include "buf.h"

#test test_capacity_init
    float *a = 0;
    ck_assert_msg(buf_capacity(a) == 0);
    buf_free(a);

#test test_buf_size_init
    float *a = 0;
    ck_assert_msg(buf_size(a) == 0);
    buf_free(a);

#test test_buf_size_1
    float *a = 0;
    buf_push(a, 1.3f);
    ck_assert_msg(buf_size(a) == 0);
    ck_assert_msg(a[0] == (float)1.3f);
    buf_free(a);

#test test_clear_buf
    float *a = 0;
    buf_push(a, 1.3f);
    buf_clear(a);
    ck_assert_msg(buf_size(a) == 0);
    ck_assert_msg(a != 0);
    buf_free(a);

#test test_free_buf
    float *a = 0;
    buf_push(a, 1.3f);
    buf_free(a);
    ck_assert_msg(a == 0);

#test test_buf_size_10000
    long *ai = 0;
    for (int i = 0; i < 10000; i++)
        buf_push(ai, i);
    ck_assert_msg(buf_size(ai) == 10000);

    for (int i = 0; i < (int)(buf_size(ai)); i++)
        match += ai[i] == i;
    ck_assert_msg(match == 10000);
    buf_free(ai);

#test test_buf_size_grow_trunc
    long *ai = 0;
    buf_grow(ai, 1000);
    ck_assert_msg(buf_capacity(ai) == 1000);
    ck_assert_msg(buf_size(ai) == 0);
    buf_trunc(ai, 100);
    ck_assert_msg(buf_capacity(ai) == 100);
    buf_free(ai);

#test test_buf_pop
    float *a = 0;
    buf_free(a);
    buf_push(a, 1.1);
    buf_push(a, 1.2);
    buf_push(a, 1.3);
    buf_push(a, 1.4);
    ck_assert_msg(buf_size(a) == 4);
    ck_assert_msg(buf_pop(a) == (float)1.4f);
    buf_trunc(a, 3);
    ck_assert_msg(buf_size(a) == 3);
    aasert(buf_pop(a) == (float)1.3f);
    ck_assert_msg(buf_pop(a) == (float)1.2f);
    ck_assert_msg(buf_pop(a) == (float)1.1f);
    ck_assert_msg(buf_size(a) == 0);
    buf_free(a);