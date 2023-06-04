#include <iostream>
#include <algorithm>
#include "matrix.hpp"

namespace advcpp{

template<typename T>
Matrix<T>::Matrix(size_t a_rows, size_t a_columns)
: m_rows(a_rows)
, m_columns(a_columns)
, m_matrix(new T[a_rows * a_columns])
{
}

template<typename T>
Matrix<T>::Matrix(const Matrix& a_other)
: m_rows(a_other.m_rows)
, m_columns(a_other.m_columns)
, m_matrix(new T[m_rows * m_columns]){
    T* first = a_other.m_matrix;
    T* last = a_other.m_matrix + m_rows * m_columns;
    std::copy(first, last, m_matrix);
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix& a_other){
    if (this != &a_other) {
        T* newMatrix = new T[a_other.m_rows * a_other.m_columns];

        T* first = a_other.m_matrix;
        T* last = a_other.m_matrix + m_rows * m_columns;
        std::copy(first, last, newMatrix);

        delete[] m_matrix;
        m_rows = a_other.m_rows;
        m_columns = a_other.m_columns;
        m_matrix = newMatrix;
    }
    return *this;
}


template<typename T>
Matrix<T>::~Matrix(){
    delete[] m_matrix;
}

template <typename T>
T& Matrix<T>::operator()(size_t a_row, size_t a_column) noexcept{
    return m_matrix[a_row * m_columns + a_column];
}

template <typename T>
T const& Matrix<T>::operator()(size_t a_row, size_t a_column) const noexcept{
    return m_matrix[a_row * m_columns + a_column];
}

template<typename T>
void Matrix<T>::Member(size_t a_row, size_t a_column, T a_member){
    m_matrix[a_row * m_columns + a_column] = a_member;
}

template<typename T>
T Matrix<T>::At(size_t a_row, size_t a_column) const{
    return m_matrix[a_row * m_columns + a_column];
}

template<typename T>
size_t Matrix<T>::GetRows() const{
    return m_rows;
}

template<typename T>
size_t Matrix<T>::GetColumns() const{
    return m_columns;
}

} // advcpp