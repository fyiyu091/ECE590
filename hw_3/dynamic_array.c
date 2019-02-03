#include "dynamic_array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* private functions *********************************************************/

/* Position in the buffer of the array element at position index */
static int index_to_offset ( const DynamicArray * da, int index ) {
    return index + da->origin;
}

/* Position of the element at buffer position 'offset' */
static int offset_to_index ( const DynamicArray * da, int offset ) {
    return offset - da->origin;
}

/* Non-zero if and only if offset lies ouside the buffer */
static int out_of_buffer ( DynamicArray * da, int offset ) {
    return offset < 0 || offset >= da->capacity;
}

/* Makes a new buffer that is twice the size of the old buffer,
   copies the old information into the new buffer, and deletes
   the old buffer */
static void extend_buffer ( DynamicArray * da ) {

    double * temp = (double *) calloc ( 2 * da->capacity, sizeof(double) );
    int new_origin = da->capacity - (da->end - da->origin)/2,
           new_end = new_origin + (da->end - da->origin);

    for ( int i=0; i<DynamicArray_size(da); i++ ) {
        temp[new_origin+i] = DynamicArray_get(da,i);
    }

    free(da->buffer);
    da->buffer = temp;

    da->capacity = 2 * da->capacity;
    da->origin = new_origin;
    da->end = new_end;

    return;

}

/* public functions **********************************************************/
static int num_da = 0;
static DynamicArray ** da_ptr = (DynamicArray **) calloc (100, sizeof(DynamicArray));
static int da_ptr_index = 0;

DynamicArray * DynamicArray_new(void) {
    DynamicArray * da = (DynamicArray *) malloc(sizeof(DynamicArray));
    da->capacity = DYNAMIC_ARRAY_INITIAL_CAPACITY;    
    da->buffer = (double *) calloc ( da->capacity, sizeof(double) ); 
    da->origin = da->capacity / 2;
    da->end = da->origin;
    da_ptr[da_ptr_index] = da;
    da_ptr_index++;
    num_da++;
    return da;
}

void DynamicArray_destroy(DynamicArray * da) {
    free(da->buffer);
    da->buffer = NULL;
    num_da--;
    da_ptr_index = 0;
    return;
}

int DynamicArray_size(const DynamicArray * da) {
    assert(da->buffer != NULL);
    return da->end - da->origin;
}

char * DynamicArray_to_string(const DynamicArray * da) {
    assert(da->buffer != NULL);
    char * str = (char *) calloc (20,DynamicArray_size(da)),
         temp[20];
    int j = 1;
    str[0] = '[';
    for ( int i=0; i < DynamicArray_size(da); i++ ) {
        if ( DynamicArray_get(da,i) == 0 ) {
            snprintf ( temp, 20, "0" );
        } else {
            snprintf ( temp, 20, "%.5lf", DynamicArray_get(da,i) ); 
        }
        if ( i < DynamicArray_size(da) - 1 ) {
            sprintf( str + j, "%s,", temp);
            j += strlen(temp) + 1;
        } else {
            sprintf( str + j, "%s", temp);
            j += strlen(temp);
        }

    }
    str[j] = ']';
    return str;
}

//Start of The hw_3 functions
double DynamicArray_min ( const DynamicArray * da )
{
    assert(da->buffer != NULL);
    assert(DynamicArray_size(da) > 0);
    double min = DynamicArray_get(da,0);
    for (int i = 0; i < DynamicArray_size(da); i++)
    {
        if (DynamicArray_get(da,i) < min)
        {
            min = DynamicArray_get(da,i);
        }
    }
    return min;
}

double DynamicArray_max ( const DynamicArray * da )
{
    assert(da->buffer != NULL);
    assert(DynamicArray_size(da) > 0);
    double max = DynamicArray_get(da,0);
    for (int i = 0; i < DynamicArray_size(da); i++)
    {
        if (DynamicArray_get(da,i) > max)
        {
            max = DynamicArray_get(da,i);
        }
    }
    return max;
}

double DynamicArray_mean ( const DynamicArray * da )
{
    assert(da->buffer != NULL);
    assert(DynamicArray_size(da) > 0);
    double sum = 0.0;
    double mean;
    for (int i = 0; i < DynamicArray_size(da); i++)
    {
        sum = DynamicArray_get(da,i) + sum;
    }
    mean = sum / DynamicArray_size(da);
    return mean;
}

double DynamicArray_median ( const DynamicArray * da )
{
    assert(da->buffer != NULL);
    assert(DynamicArray_size(da) > 0);
    assert(da->buffer != NULL);
    DynamicArray * tda = (DynamicArray *) malloc (sizeof(DynamicArray));
    tda->capacity = da->capacity;
    tda->origin = da->origin;
    tda->end = da->end;
    tda->buffer = (double *) calloc ( tda->capacity, sizeof(double));  
    for (int i = 0; i < DynamicArray_size(da); i++)
    {
        DynamicArray_set(tda, i, DynamicArray_get(da, i));
    }
    double median;
    double tmp;
    for (int i = 0; i < DynamicArray_size(tda); i++)
    {
        for (int j = i + 1; j < DynamicArray_size(tda); j++)
        {
             if (DynamicArray_get(tda,i) > DynamicArray_get(tda,j))
             {
                 tmp = DynamicArray_get(tda,i);
                 DynamicArray_set(tda, i, DynamicArray_get(tda,j));
                 DynamicArray_set(tda, j, tmp);
             }
        }
    }
    if (DynamicArray_size(tda)%2 != 0)
    {
       median = DynamicArray_get(tda,(DynamicArray_size(tda)-1)/2);
    }
    else
    {
       median = (DynamicArray_get(tda,(DynamicArray_size(tda)/2 - 1)) + DynamicArray_get(tda,(DynamicArray_size(tda)/2))) / 2;
    }
    return median;
    
}

double DynamicArray_sum ( const DynamicArray * da )
{
    assert(da->buffer != NULL);
    double sum = 0;
    for (int i = 0; i < DynamicArray_size(da); i++)
    {
        sum = sum + DynamicArray_get(da,i);
    }
    return sum;
}

double DynamicArray_first ( const DynamicArray * da )
{
    assert(da->buffer != NULL);
    assert(DynamicArray_size(da) > 0);
    return DynamicArray_get(da, 0);
}

double DynamicArray_last ( const DynamicArray * da )
{
    assert(da->buffer != NULL);
    assert(DynamicArray_size(da) > 0);
    return DynamicArray_get(da, DynamicArray_size(da) - 1);
}

DynamicArray * DynamicArray_copy ( const DynamicArray * da )
{
    assert(da->buffer != NULL);
    DynamicArray * rda = (DynamicArray *) malloc (sizeof(DynamicArray));
    rda->capacity = da->capacity;
    rda->origin = da->origin;
    rda->end = da->end;
    rda->buffer = (double *) calloc ( rda->capacity, sizeof(double));  
    for (int i = 0; i < DynamicArray_size(da); i++)
    {
        DynamicArray_set(rda, i, DynamicArray_get(da, i));
    }
    da_ptr[da_ptr_index] = rda;
    da_ptr_index++;
    num_da++;
    return rda;
}

DynamicArray * DynamicArray_range ( double a, double b, double step)
{
    int num = ((b - a) / step) + 1;
    DynamicArray * da= DynamicArray_new();
    for (int i = 0; i < num; i++)
    {
        double the_value = a + i*step;
        DynamicArray_set(da, i, the_value);
    }
    return da;
}

DynamicArray * DynamicArray_concat ( const DynamicArray * a, const DynamicArray * b )
{
    assert(a->buffer != NULL);
    assert(b->buffer != NULL);
    int i;
    DynamicArray * results= DynamicArray_new();
    for (i = 0; i < DynamicArray_size(a); i++)
    {
        DynamicArray_set(results, i, DynamicArray_get(a, i));
    }
    for (int j = 0; j < DynamicArray_size(b); j++)
    {
        DynamicArray_set(results, i + j, DynamicArray_get(b, j));
    }
    return results;
}

DynamicArray * DynamicArray_take (const DynamicArray * a, int b)
{
    assert(a->buffer != NULL);
    DynamicArray * results = DynamicArray_new();
    if (b >= 0)
    {
       if (b <= DynamicArray_size(a))
       {
          for (int j = 0; j < b; j++)
          {
            DynamicArray_set(results, j, DynamicArray_get(a, j));
          }
       }
       else
       {
           for(int i = 0; i < DynamicArray_size(a); i++)
           {
               DynamicArray_set(results, i, DynamicArray_get(a, i));  
           }
           for (int i = 0; i < b - DynamicArray_size(a); i++)
           {
             DynamicArray_set(results, i+DynamicArray_size(a), 0.0);  
           }

       }
       
    }
    else
    {
       if (-b <= DynamicArray_size(a))
       {
          for (int j = 0; j < -b; j++)
          {
            DynamicArray_set(results, j, DynamicArray_get(a, DynamicArray_size(a)+b+j));
          }
       }
       else
       {
           for(int i = 0; i < DynamicArray_size(a); i++)
           {
               DynamicArray_set(results, i, DynamicArray_get(a, i));  
           }
           for (int i = 0; i < -b - DynamicArray_size(a); i++)
           {
             DynamicArray_set(results, i+DynamicArray_size(a), 0.0);  
           }

       }
    }
    return results;
}

int DynamicArray_is_valid(const DynamicArray * da)
{
    if (da->buffer == NULL)
    {
        return 0;
    }
    else
    {
        return 1;
    }
    
}

int DynamicArray_num_arrays()
{
    return num_da;
}

int DynamicArray_destroy_all()
{
    for (int i = 0; i < num_da; i++)
    {
        free(da_ptr[i] -> buffer);
        da_ptr[i] -> buffer = NULL;
    }
    num_da = 0;
    da_ptr_index = 0;
    return 0;
}

//End of the hw_3 functions

void DynamicArray_print_debug_info(const DynamicArray * da) {

    char * s = DynamicArray_to_string(da);
    printf ( "  %s\n", s);
    printf ( "  capacity: %d\n  origin: %d\n  end: %d\n  size: %d\n\n",
      da->capacity, 
      da->origin, 
      da->end,
      DynamicArray_size(da));

    free(s);

}

void DynamicArray_set(DynamicArray * da, int index, double value) {
    assert(da->buffer != NULL);
    assert ( index >= 0 );
    while ( out_of_buffer(da, index_to_offset(da, index) ) ) {
        extend_buffer(da);
    }
    da->buffer[index_to_offset(da, index)] = value;
    if ( index >= DynamicArray_size(da) ) {
        da->end = index_to_offset(da,index+1);
    }

}

double DynamicArray_get(const DynamicArray * da, int index) {
    assert(da->buffer != NULL);
    assert ( index >= 0 );
    if ( index >= DynamicArray_size(da) ) {
        return 0;
    } else {
        return da->buffer[index_to_offset(da,index)];
    }
}

void DynamicArray_push(DynamicArray * da, double value ) {
    DynamicArray_set(da, DynamicArray_size(da), value );
}

void DynamicArray_push_front(DynamicArray * da, double value) {
    assert(da->buffer != NULL);
    while ( da->origin == 0 ) {
        extend_buffer(da);
    }
    da->origin--;
    DynamicArray_set(da,0,value);
}

double DynamicArray_pop(DynamicArray * da) {
    assert(DynamicArray_size(da) > 0);
    double value = DynamicArray_last(da);
    DynamicArray_set(da, DynamicArray_size(da)-1, 0.0);
    da->end--;
    return value;
}

double DynamicArray_pop_front(DynamicArray * da) {
    assert(DynamicArray_size(da) > 0);
    double value = DynamicArray_first(da);
    da->origin++;
    return value;    
}

DynamicArray * DynamicArray_map(const DynamicArray * da, double (*f) (double)) {
    DynamicArray * result = DynamicArray_copy(da);
    for ( int i=0; i<DynamicArray_size(da); i++ ) {
        DynamicArray_set(result, i, f(DynamicArray_get(da, i)));
    }
    return result;
}