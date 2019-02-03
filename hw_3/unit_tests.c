#include <math.h>
#include <float.h> /* defines DBL_EPSILON */
#include "dynamic_array.h"
#include "arbitrary_array.h"
#include "gtest/gtest.h"

#define X 1.2345

typedef struct {
    double x, y, z;
} Point;

char * point_to_string ( void * p ) {
    Point * q = (Point *) p;
    char * str = (char *) calloc(40, sizeof(char));
    snprintf(str,40,"{%.1lf,%.1lf,%.1lf}", q->x, q->y, q->z);
    return str;
}

namespace {

    TEST(DynamicArray, Min_Max){
        DynamicArray * da = DynamicArray_new();
        DynamicArray_push(da, 35.0);
        DynamicArray_push(da, -2.0);
        DynamicArray_push(da, 18.0);
        ASSERT_DOUBLE_EQ(DynamicArray_max(da), 35.0);
        ASSERT_DOUBLE_EQ(DynamicArray_min(da), -2.0);
        DynamicArray_pop_front(da);
        ASSERT_DOUBLE_EQ(DynamicArray_max(da), 18.0);
        DynamicArray_pop(da);
        ASSERT_DOUBLE_EQ(DynamicArray_max(da), -2.0);
        ASSERT_DOUBLE_EQ(DynamicArray_min(da), -2.0);
        DynamicArray_pop(da);
        ASSERT_DEATH(DynamicArray_max(da), ".*Assertion.*");
        DynamicArray_destroy(da);
        free(da);
    }

    TEST(DynamicArray, Median){
        DynamicArray * da = DynamicArray_new();
        DynamicArray_push(da, 2.0);
        DynamicArray_push(da, 10.0);
        DynamicArray_push(da, 21.0);
        DynamicArray_push(da, 3.0);
        DynamicArray_push(da, 11.0);
        ASSERT_DOUBLE_EQ(DynamicArray_median(da), 10.0);
        DynamicArray_push(da, 4.0);
        ASSERT_DOUBLE_EQ(DynamicArray_median(da), 7.0);
        DynamicArray_destroy(da);
        free(da);
    }

    TEST(DynamicArray, Sum_Mean){
        DynamicArray * da = DynamicArray_new();
        ASSERT_DOUBLE_EQ(DynamicArray_sum(da), 0);
        ASSERT_DEATH(DynamicArray_mean(da), ".*Assertion.*");
        double sum = -5.2+6.8+9.9+(-4.35)+0.77;
        double mean = sum/5.0;
        DynamicArray_push(da, -5.2);
        DynamicArray_push(da, 6.8);
        DynamicArray_push(da, 9.9);
        DynamicArray_push(da, -4.35);
        DynamicArray_push(da, 0.77);        
        ASSERT_DOUBLE_EQ(DynamicArray_sum(da), sum);
        ASSERT_DOUBLE_EQ(DynamicArray_mean(da), mean);
        DynamicArray_destroy(da);
        free(da);
    }
    
    TEST(DynamicArray, First_Last){
        DynamicArray * da = DynamicArray_new();
        DynamicArray_push(da, 23.0);
        DynamicArray_push(da, 45.0);
        ASSERT_DOUBLE_EQ(DynamicArray_first(da), 23.0);
        ASSERT_DOUBLE_EQ(DynamicArray_last(da), 45.0);
        DynamicArray_pop(da);
        ASSERT_DOUBLE_EQ(DynamicArray_first(da), 23.0);
        ASSERT_DOUBLE_EQ(DynamicArray_last(da), 23.0);
        DynamicArray_pop(da);
        ASSERT_DEATH(DynamicArray_first(da), ".*Assertion.*");
        ASSERT_DEATH(DynamicArray_last(da), ".*Assertion.*");
        DynamicArray_destroy(da);
        free(da);
    }

    TEST(DynamicArray, Copy){
        DynamicArray * da = DynamicArray_new();
        for (int i = 0; i < 5; i++){
            DynamicArray_push(da, i);
        }
        DynamicArray *ptr = DynamicArray_copy(da);
        for (int i = 0; i < 5; i++){
            ASSERT_EQ(DynamicArray_get(ptr, i), i);
        }
        DynamicArray_set(ptr, 2, 101);
        ASSERT_EQ(DynamicArray_get(da, 2), 2);
        ASSERT_EQ(DynamicArray_get(ptr, 2), 101);
        DynamicArray_destroy(da);
        DynamicArray_destroy(ptr);
        free(da);
        free(ptr);
    }

    TEST(DynamicArray, Range){
        DynamicArray * a = DynamicArray_range(1.0, 2.0, 0.3);
        for(int i=0; i<DynamicArray_size(a); i++){
            ASSERT_LT(
                abs(DynamicArray_get(a,i) - (1.0 + i*0.3)),
                DBL_EPSILON
            );
        }
        DynamicArray * b = DynamicArray_range(7.0, 1.0, -2);
        for(int i=0; i<DynamicArray_size(b); i++){
            ASSERT_LT(
                abs(DynamicArray_get(b,i) - (7.0 - i*2)),
                DBL_EPSILON
            );
        }
        DynamicArray * c = DynamicArray_range(6, 4, 3);
        ASSERT_EQ(DynamicArray_size(c), 0);
        ASSERT_DEATH(DynamicArray_first(c), ".*Assertion.*");
        DynamicArray_destroy(a);
        DynamicArray_destroy(b);
        DynamicArray_destroy(c);
        free(a);
        free(b);
        free(c);
    }

    TEST(DynamicArray, Concat)
    {
        DynamicArray *a = DynamicArray_new();
        DynamicArray *b = DynamicArray_range(1, 2, 0.1);
        DynamicArray *c = DynamicArray_concat(a, b);
        for (int i = 0; i < DynamicArray_size(b); i++)
        {
            ASSERT_DOUBLE_EQ(DynamicArray_get(c, DynamicArray_size(a) + i), 1 + 0.1 * i);
        }
        DynamicArray_destroy(a);        
        DynamicArray_destroy(b);
        DynamicArray_destroy(c);
        free(a);
        free(b);
        free(c);
    }
    TEST(DynamicArray, Take){
        DynamicArray *a = DynamicArray_range(-2, 3, 1);
        DynamicArray *b = DynamicArray_take(a, 2);
        for (int i = 0; i < DynamicArray_size(b); i++)
        {
            ASSERT_DOUBLE_EQ(DynamicArray_get(b, i), -2 + i);
        }
        DynamicArray *c = DynamicArray_take(a, -2); 
        //for (int i = 0; i < DynamicArray_size(c); i++)
        //{
        //    ASSERT_DOUBLE_EQ(DynamicArray_get(c, i), 3 - i);
        //}
        DynamicArray *d = DynamicArray_take(a, 10); 
        for (int i = 6; i < DynamicArray_size(d); i++)
        {
            ASSERT_DOUBLE_EQ(DynamicArray_get(c, i), 0);
        }
        DynamicArray *e = DynamicArray_take(a, -10); 
        for (int i = 6; i < DynamicArray_size(e); i++)
        {
            ASSERT_DOUBLE_EQ(DynamicArray_get(e, 2), 0);
        }
        DynamicArray_destroy(a);        
        DynamicArray_destroy(b);
        DynamicArray_destroy(c);
        DynamicArray_destroy(d);
        DynamicArray_destroy(e);
        free(a);
        free(b);
        free(c);
        free(d);
        free(e);
    }
    TEST(DynamicArray, All){
        DynamicArray *a = DynamicArray_range(0, 1, 0.1);
        DynamicArray *b = DynamicArray_range(1.1, 2, 0.1);
        DynamicArray *c = DynamicArray_concat(a, b);
        DynamicArray *d = DynamicArray_take(a, -3);
        DynamicArray *e = DynamicArray_copy(b);
        DynamicArray *f = DynamicArray_copy(b);
        ASSERT_EQ(DynamicArray_is_valid(d), 1);
        ASSERT_EQ(DynamicArray_num_arrays(), 6);
        DynamicArray_destroy_all();
        ASSERT_EQ(DynamicArray_is_valid(f), 0);
        ASSERT_EQ(DynamicArray_num_arrays(), 0);
        DynamicArray *h = DynamicArray_range(1.1, 2, 0.1);
        ASSERT_EQ(DynamicArray_is_valid(h), 1);
        ASSERT_EQ(DynamicArray_num_arrays(), 1);
        DynamicArray_destroy_all();
        ASSERT_EQ(DynamicArray_num_arrays(), 0);
        ASSERT_EQ(DynamicArray_is_valid(h), 1);
        free(a);
        free(b);
        free(c);
        free(d);
        free(e);
        free(c);
        free(f);
    }

    TEST(ArbitraryArray,OfPointers) {

    // Create the array that will hold the pointers
    ArbitraryArray * ptrs = ArbitraryArray_new(sizeof(DynamicArray *));

    // Create a couple of dynamic arrays
    DynamicArray * a = DynamicArray_new(),
                            * b = DynamicArray_new();

    // Add the dynamic arrays to the pointer array
    ArbitraryArray_set_from_ptr(ptrs, 0, &a);
    ArbitraryArray_set_from_ptr(ptrs, 1, &b);

    // Get them back. Note that because the array contains pointers,
    // and _get_ptr returns a pointer to a pointer, we need to cast
    // its result as a pointer to a DynamicArray pointer.
    DynamicArray ** ptr_a = (DynamicArray **) ArbitraryArray_get_ptr(ptrs,0);
    DynamicArray ** ptr_b = (DynamicArray **) ArbitraryArray_get_ptr(ptrs,1);

    // Check that the pointers are equal
    ASSERT_EQ(*ptr_a, a);
    ASSERT_EQ(*ptr_b, b);
    ASSERT_NE(*ptr_a, b);
    ASSERT_NE(*ptr_b, a);
    }

    TEST(ArbitraryArray, String){
        Point p = {1, 3, 3};
        ArbitraryArray *a = ArbitraryArray_new(sizeof(Point));
        ArbitraryArray_set_from_ptr(a, 0, &p);
        //ArbitraryArray_set_from_ptr(a, 1, &q);
        char *s = ArbitraryArray_to_string(a, point_to_string);
        ASSERT_STREQ(s, "{1.0,3.0,3.0}");
        ArbitraryArray_destroy(a);
        free(a);
    }
}
