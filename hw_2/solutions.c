#include "solutions.h"
#include <stdlib.h>
#include <stdio.h>
#include <float.h>

int running_total(int a) {
    static int b = 0;
    b = a + b;
    return b;
}

void reverse_in_place(int * a, int b) {
    int c[b];
    for (int j = 0; j < b; j++){
        c[j] = a[j];
    }
    for(int i = 0; i < b; i++) {
        a[i] = c[b - i - 1];
    }
    return;
}

int * reverse(int * a, int b) {
    int * y = (int *) calloc(b, sizeof(int));
    for (int i = 0; i < b; i++) {
        y[i] = a[b - i -1];
    }
    return y;
}

int num_instances(int * a, int b, int value) {
    int num = 0;
    for (int i = 0; i < b; i++) {
        if (a[i] == value) {
            num++;
        }
    }
    return num;
}

int * to_set(int * a, int length, int * n) {
    int * b = (int *) calloc(length, sizeof(int));
    int i,j,num;
    num = 0;
    for (i = 0; i < length; i++) {
        for (j = 0; j < num; j++) {
            if (a[i] == b[j]) {
                break;
            }
        }
        if (j == num)
        {
            b[num] = a[i];
            num++;
        }
    }
    *n = num;
    return b;
}

Point * map(Point * a, int length, Point (*f) (Point)) {
    Point * b = (Point *) calloc(length, sizeof(Point));
    for (int i = 0; i < length; i++) {
        b[i] = f(a[i]);
    }
    return b;
}

static int stack_size = 100;
static double * t_stack;
static int top;
static Status RPN_status = NOT_INITIALIZED_ERROR;

void rpn_init() {
     t_stack = (double *) calloc(stack_size, sizeof(double));
     RPN_status = OK;
     top = 0;
}

Status rpn_error(){
     return RPN_status;
}

void rpn_free() {
     free(t_stack);
     RPN_status = NOT_INITIALIZED_ERROR;
}

void rpn_push(double x) {
    if (RPN_status != OK)
    {
        return;
    }
    else
    {
    t_stack[top] = x;
    top++;
    if (top > 95) {
        stack_size = stack_size + 100;
        t_stack = (double *) realloc(t_stack, stack_size);
    }
    }
}

double rpn_pop() {
    if (RPN_status != OK)
    {
        return 0.0;
    }
    else if (top == 0) {
        RPN_status = POP_ERROR;
        return 0.0;
    }
    else {
        top--;
        return t_stack[top];
    }
}

void rpn_negate() {
    if (RPN_status != OK)
    {
        return;
    }
    else if (top == 0) {
        RPN_status = NEGATE_ERROR;
    }
    else {
        t_stack[top - 1] = -t_stack[top - 1]; 
    }
}

void rpn_add() {
    if (RPN_status != OK)
    {
        return;
    }
    else if (top <= 1) {
        RPN_status = ADD_ERROR;
    }
    else {
        top = top - 1;
        t_stack[top - 1] = t_stack[top] + t_stack[top - 1]; 
        if (t_stack[top - 1] >= DBL_MAX || t_stack[top - 1] <= -DBL_MAX) 
        {
            RPN_status = OVERFLOW_ERROR;
            t_stack[top - 1] = 0.0;
        }
    }
}   

void rpn_multiply() {
    if (RPN_status != OK)
    {
        return;
    }
    else if (top <= 1) {
        RPN_status = MULT_ERROR;
    }
    else {
        top = top - 1;
        t_stack[top - 1] = t_stack[top] * t_stack[top - 1]; 
        if (t_stack[top - 1] >= DBL_MAX || t_stack[top - 1] <= -DBL_MAX) 
        {
            RPN_status = OVERFLOW_ERROR;
            t_stack[top - 1] = 0.0;
        }
    }
}
