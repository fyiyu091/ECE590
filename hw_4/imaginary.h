#ifndef IMAGINARY
#define IMAGINARY

#include <iostream>

class Imaginary {

public:

    // Constructors
    Imaginary();
    Imaginary(double a, double b) : real(a), ima(b) {};

    // Assignment
    Imaginary& operator+=(const Imaginary& other);
    Imaginary& operator*=(const Imaginary& other);
    bool operator==(const Imaginary& other) const;
    Imaginary operator*(const Imaginary& other) const;
    Imaginary operator+(const Imaginary& other) const;

    // The naming of the re and im???
    double re();
    double im();

    Imaginary conjugate();

    double magnitude();

    void set(int index, double value);

private:
    double real, ima;
    double INITIAL_VALUE = 0;

};

#endif