#ifndef TYPED_MATRIX
#define TYPED_MATRIX

#include <assert.h>
#include <iostream>
#include <stdexcept>
#include <vector>

template <typename ElementType>
class TypedMatrix {

public:
    TypedMatrix();
    TypedMatrix(int n, int m);
    TypedMatrix(const TypedMatrix& other);

    ~TypedMatrix();

    const ElementType& get(int i, int j) const;
    int rows() const;
    int cols() const;

    
    void set(int i, int j, ElementType value);

    //operator 
    TypedMatrix& operator=(const TypedMatrix& other);
    TypedMatrix& operator+=(const TypedMatrix& other);
    TypedMatrix& operator*=(const TypedMatrix& other);
    bool operator==(const TypedMatrix& other) const;   
    TypedMatrix operator+(const TypedMatrix& other);
    TypedMatrix operator*(const TypedMatrix& other);

    int row;
    int column;

private:
    int rows_;
    int cols_;
    std::vector<std::vector<ElementType>>* buffer;
};

template <typename ElementType>
TypedMatrix<ElementType>::TypedMatrix() {
    this->buffer = new std::vector<std::vector<ElementType>>();
    this->buffer->resize(1);
    this->buffer->at(0) = std::vector<ElementType>();
    this->buffer->at(0).resize(1);
    this->buffer->at(0).at(0) = ElementType();
    this->rows_ = 1;
    this->cols_ = 1;
}


//Need to pass the n and m to the internal typedarray capacity
template <typename ElementType>
TypedMatrix<ElementType>::TypedMatrix(int n, int m) {
    this->rows_ = m;
    this->cols_ = n;
    this->buffer = new std::vector<std::vector<ElementType>>();
    this->buffer->resize(this->rows_);
    for(int i=0; i<this->rows_; i++){
        this->buffer->at(i) = std::vector<ElementType>();
        for(int j=0; j<this->cols_; j++){
            this->buffer->at(i).resize(this->cols_);
            this->buffer->at(i).at(j) = ElementType();
        }
    }
}

template <typename ElementType>
TypedMatrix<ElementType>::TypedMatrix(const TypedMatrix& other) : TypedMatrix() {
    //std::cout<<"Copy constructor!\n";
    *this = other;
}

// Destructor
template <typename ElementType>
TypedMatrix<ElementType>::~TypedMatrix() 
{
    delete buffer;
}

template <typename ElementType>
int TypedMatrix<ElementType>::cols() const{
    return this->cols_;
}

template <typename ElementType>
int TypedMatrix<ElementType>::rows() const{
    return this->rows_;
}

template <typename ElementType>
const ElementType& TypedMatrix<ElementType>::get(int i, int j) const
{
    if (i< 0 || i>=this->rows_ || j<0 || j>=this->cols_ ) {
        throw std::range_error("Out of range index in matrix!!!");
    }
    return this->buffer->at(i).at(j);
}

template <typename ElementType>
void TypedMatrix<ElementType>::set(int i, int j, ElementType val){
    if (i< 0 || i>=this->rows_ || j<0 || j>=this->cols_ ) {
        throw std::range_error("Out of range index in matrix!!!");
    }
    this->buffer->at(i).at(j) = val;
}

template <typename ElementType>
TypedMatrix<ElementType>& TypedMatrix<ElementType>::operator=(const TypedMatrix<ElementType>& other){
    //std::cout<<"Assignment operator!\n";
    if( this != &other){
        delete this->buffer;
        this->buffer = new std::vector<std::vector<ElementType>>();
        this->cols_ = other.cols_;
        this->rows_ = other.rows_;
        this->buffer->resize(other.rows_);
        for(int i=0; i<this->rows_; i++){
            this->buffer->at(i) = std::vector<ElementType>();
            for(int j=0; j<this->cols_; j++){
                this->buffer->at(i).resize(other.cols_);
                this->buffer->at(i).at(j) = other.get(i,j);
            }
        }
    }
    return *this;
}

template <typename ElementType>
TypedMatrix<ElementType>& TypedMatrix<ElementType>::operator+=(const TypedMatrix<ElementType>& other){
    if ( (this->cols_!=other.cols_) || (this->rows_!=other.rows_) ){
        throw std::range_error("Matrix dimension doesn't match.");
    }
    for(int i=0; i<this->rows_; i++){
        for(int j=0; j<this->cols_; j++){
            ElementType sum = this->get(i,j) + other.get(i,j);
            this->set(i, j, sum);
        }
    }
    return *this;
}

template <typename ElementType>
TypedMatrix<ElementType>& TypedMatrix<ElementType>::operator*=(const TypedMatrix<ElementType>& other){
    if ( (this->cols_!=other.cols_) || (this->rows_!=other.rows_) ){
        throw std::range_error("Matrix dimension doesn't match.");
    }
    for(int i=0; i<this->rows_; i++){
        for(int j=0; j<this->cols_; j++){
            ElementType prod = this->get(i,j) * other.get(i,j);
            this->set(i, j, prod);
        }
    }
    return *this;
}

template <typename ElementType>
bool TypedMatrix<ElementType>::operator==(const TypedMatrix<ElementType>& other) const{
    if ( (this->cols_!=other.cols_) || (this->rows_!=other.rows_) ){
        return false;
    } 
    for(int i=0; i<this->rows_; i++){
        for(int j=0; j<this->cols_; j++){
            if(!(this->get(i,j) == other.get(i,j)))
                return false;
        }
    }
    return true;
}

template <typename ElementType>
TypedMatrix<ElementType> TypedMatrix<ElementType>::operator+(const TypedMatrix<ElementType>& other){
    if ( (this->cols_!=other.cols_) || (this->rows_!=other.rows_) ){
        throw std::range_error("Matrix dimension doesn't match.");
    } 
    TypedMatrix<ElementType> sum(this->cols_, this->rows_);
    for(int i=0; i<this->rows_; i++){
        for(int j=0; j<this->cols_; j++){
            ElementType tmp = this->get(i,j) + other.get(i,j);
            sum.set(i,j,tmp);
        }
    }
    return sum;
}

template <typename ElementType>
TypedMatrix<ElementType> TypedMatrix<ElementType>::operator*(const TypedMatrix<ElementType>& other){
    if (this->cols_!=other.rows_){
        throw std::range_error("Matrix dimension doesn't match.");
    } 
    TypedMatrix<ElementType> prod(this->rows_, other.cols_);
    for(int i=0; i<this->rows_; i++){
        for(int j=0; j<other.cols_; j++){
            ElementType tmp = ElementType();
            for(int k=0; k<this->cols_; k++){
                tmp += this->get(i,k) * other.get(k,j);
            }
            prod.set(i, j, tmp);
        }
    }
    return prod;
}

template <typename ElementType>
std::ostream &operator<<(std::ostream &os, TypedMatrix<ElementType> &matrix)
{
    os << '[';
    for(int i=0; i<matrix.rows(); i++){
        if (i>0)
            os << ' ';
        os << '[';
        for(int j=0; j<matrix.cols(); j++){
            os << matrix.get(i, j);
            if (j<matrix.cols()-1){
                os << ",";
            }
        }
        os << ']';
        if (i<matrix.rows()-1)
            os << '\n';
    }
    os << ']';
    return os;
}



/*
template <typename ElementType>
void TypedMatrix<ElementType>::set(int i, int j, ElementType value)
{
    if (i > row || j > column)
    {
        throw std::range_error("The matrix index is out of range");
    }
    else
    {
        outer.at(j).at(i) = value;
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
*/

#endif