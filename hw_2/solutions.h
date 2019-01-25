#ifndef SOLUTIONS_H
#define SOLUTIONS_H

#include <stdlib.h>
#include <stdio.h>

int running_total(int a);

void reverse_in_place(int * a, int b);

int * reverse(int * a, int b);

int num_instances(int * a, int b, int value);

int * to_set(int * a, int b, int * n);

typedef struct {
    double x, y, z;
} Point;

Point * map(Point * a, int length, Point (*f) (Point));

void rpn_init();

typedef enum status{
    NOT_INITIALIZED_ERROR, OK, POP_ERROR, NEGATE_ERROR, MULT_ERROR, ADD_ERROR, OVERFLOW_ERROR
}Status;

Status rpn_error();

void rpn_print();

void rpn_free();

void rpn_push(double x);

double rpn_pop();

void rpn_negate();

void rpn_add();

void rpn_multiply();

#endif