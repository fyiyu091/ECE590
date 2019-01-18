#ifndef IMAGINARY_H
#define IMAGINARY_H

typedef struct {
    double real;
    double im;
} Imaginary;

Imaginary add (Imaginary a, Imaginary b);
Imaginary negate (Imaginary a);
Imaginary conjugate (Imaginary a );
Imaginary multiply (Imaginary a, Imaginary b);
double magnitude (Imaginary a);

#endif
