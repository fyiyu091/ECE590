#ifndef TYPED_MATRIX
#define TYPED_MATRIX

#include <assert.h>
#include <iostream>
#include <stdexcept>
#include "typed_array.h"

template <typename ElementType>
class TypedMatrix {

public:
    TypedMatrix();
    TypedMatrix(int n, int m);

    ElementType& get(int i, int j) const;
    void set(int i, int j, ElementType value);
    TypedMatrix& operator=(const TypedMatrix& other);
    TypedMatrix& operator+=(const TypedMatrix& other);
    TypedMatrix& operator*=(const TypedMatrix& other);
    bool operator==(const TypedMatrix& other) const;   
    TypedMatrix operator+(const TypedMatrix& other);
    TypedMatrix operator*(const TypedMatrix& other);

    int row;
    int column;

private:
    TypedArray<ElementType> inner;
    TypedArray<TypedArray<ElementType>> outer;
};

template <typename ElementType>
TypedMatrix<ElementType>::TypedMatrix() {
    ElementType de_value = ElementType();
    inner.set(0, de_value); 
    outer.set(0, inner);
    row = 1;
    column = 1;
}

//Need to pass the n and m to the internal typedarray capacity
template <typename ElementType>
TypedMatrix<ElementType>::TypedMatrix(int n, int m) {
    //TypedArray<inner>(); 
    ElementType de_value = ElementType();
    row = m;
    column = n;
    for (int i = 0; i < row; i++)
    {
        inner.set(i, de_value);
    }
    for (int i = 0; i < column; i++)
    {
        outer.set(i, inner);
    }
}

template <typename ElementType>
ElementType& TypedMatrix<ElementType>::get(int i, int j) const
{
    if (i > row || j > column)
    {
        throw std::range_error("The matrix index is out of range");
    }
    else
    {  
        return outer.safe_get(j).safe_get(i);
    }
    
}

template <typename ElementType>
void TypedMatrix<ElementType>::set(int i, int j, ElementType value)
{
    if (i > row || j > column)
    {
        throw std::range_error("The matrix index is out of range");
    }
    else
    {
        outer.safe_get(j).set(i, value);
    }
}

// Operator overload
template <typename ElementType>
std::ostream &operator<<(std::ostream &os, TypedMatrix<ElementType> &matrix)
{
    os << '[';
    for (int i=0; i<matrix.row; i++) 
    {
        for (int j=0; j<matrix.column; j++)
        {
            os << matrix.get(i,j) << ' ';
            if (j == matrix.column - 1)
            {
                os << '\n';
            }
        }    
    }
    os << ']';
    return os;
}

template <typename ElementType>
TypedMatrix<ElementType>& TypedMatrix<ElementType>::operator=(const TypedMatrix& other)
{
    row = other.row;
    column = other.column;
    inner = other.inner;
    outer = other.outer;
    return *this;
}

template <typename ElementType>
TypedMatrix<ElementType>& TypedMatrix<ElementType>::operator+=(const TypedMatrix& other)
{
    if (row != other.row || column != other.column)
    {
        throw std::invalid_argument("The matrix size are not matching");
    }
    else
    {  
        for (int i=0; i<row; i++) 
        {
            for (int j=0; j<column; j++)
            {
                set(i,j,(get(i,j)+other.get(i,j)));
            }
        }
    }
    return *this;
}

template <typename ElementType>
TypedMatrix<ElementType>& TypedMatrix<ElementType>::operator*=(const TypedMatrix& other)
{
    if (row != other.row || column != other.column)
    {
        throw std::invalid_argument("The matrix size are not matching");
    }
    else
    {
        for (int i=0; i<row; i++) 
        {
            for (int j=0; j<column; j++)
            {
                set(i,j,(get(i,j)*other.get(i,j)));
            }
        }
    }
    return *this;
}

template <typename ElementType>
bool TypedMatrix<ElementType>::operator==(const TypedMatrix& other) const
{
     bool results=true;
     for (int i=0; i<row; i++) 
     {
        for (int j=0; j<column; j++)
        {
             if (get(i,j) == other.get(i,j))
             {
                 results = true;
             }
             else
             {
                 results = false;
             }
             
        }
     }
    return results;
}

template <typename ElementType>
TypedMatrix<ElementType> TypedMatrix<ElementType>::operator+(const TypedMatrix& other)
{
    auto results = TypedMatrix(row,column);
    if (row != other.row || column != other.column)
    {
        throw std::invalid_argument("The matrix size are not matching");
    }
    else
    {
        for (int i=0; i<row; i++) 
        {
            for (int j=0; j<column; j++)
            {
                results.set(i,j,(get(i,j)+other.get(i,j)));
            }
        }
    }
    
    
    return results;

}

// The matrix multiplication
template <typename ElementType>
TypedMatrix<ElementType> TypedMatrix<ElementType>::operator*(const TypedMatrix& other)
{
     if (column != other.row)
     {
         throw std::invalid_argument("The matrix size are not matching");
     }
     else
     {
        auto results = TypedMatrix(other.column,row);
        for (int i=0; i<row; i++)
        {
            for (int j=0; j<other.column; j++)
            {
                // Need the set to default function
                ElementType value = ElementType();
                for (int h=0; h<column; h++)
                {
                        value += get(i,h)*other.get(h,j);
                }
                results.set(i,j,value);
            }
        }
        return results;
     }
     
}


#endif