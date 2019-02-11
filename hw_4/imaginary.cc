#include <assert.h>
#include <stdexcept>
#include "imaginary.h"
#include <math.h>


//Default constructor
Imaginary::Imaginary() 
{
    real = INITIAL_VALUE;
    ima = INITIAL_VALUE;
}

double Imaginary::re()
{
    return real;
}

double Imaginary::im()
{
    return ima;
}

Imaginary Imaginary::conjugate()
{
    auto the_conju = Imaginary();
    the_conju.real = real;
    the_conju.ima = -ima;
    return the_conju;
}

double Imaginary::magnitude()
{
    return sqrt(real*real+ima*ima);
}

// Operator overload
Imaginary& Imaginary::operator+=(const Imaginary& other)
{
    double the_real = real;
    double the_ima = ima;
    real = the_real + other.real;
    ima = the_ima + other.ima;
    return *this;
}

Imaginary& Imaginary::operator*=(const Imaginary& other)
{
    double the_real = real;
    double the_ima = ima;
    real = the_real*other.real - the_ima*other.ima;
    ima = the_real*other.ima + the_ima*other.real;
    return *this;
}

bool Imaginary::operator==(const Imaginary& other) const
{
    bool results;
    if (real == other.real && ima == other.ima)
    {
        results = true;
    }
    else
    {
        results = false;
    }
    return results;
}

Imaginary Imaginary::operator*(const Imaginary& other) const
{
    auto results = Imaginary();
    results.real = real*other.real - ima*other.ima;
    results.ima = real*other.ima + ima*other.real;
    return results;
}

Imaginary Imaginary::operator+(const Imaginary& other) const
{
    auto results = Imaginary();
    results.real = real + other.real;
    results.ima = ima + other.ima;
    return results;
}