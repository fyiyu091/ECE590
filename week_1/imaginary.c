#include "imaginary.h"
#include <math.h>
#include <stdlib.h>

Imaginary add (Imaginary a, Imaginary b)
{
   return (Imaginary) {a.real + b.real, a.im + b.im};
}

Imaginary negate (Imaginary a)
{
   return (Imaginary) {-a.real, -a.im};
}

Imaginary conjugate (Imaginary a )
{
   return (Imaginary) {a.real, 0 - a.im};
}

Imaginary multiply (Imaginary a, Imaginary b)
{
   return (Imaginary) {a.real*b.real - a.im*b.im, a.real*b.im + a.im*b.real};
}

double magnitude (Imaginary a)
{
   return sqrt(abs(a.im*a.im + a.real*a.real));
}