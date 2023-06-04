#ifndef MATRIX_H_203
#define MATRIX_H_203

#include <memory> 

namespace advcpp{

template <typename T>
class Matrix{
public:
    explicit Matrix(size_t a_row, size_t a_columns);
    Matrix(const Matrix& a_other);
    Matrix& operator = (const Matrix& a_other);
    ~Matrix();
    
    T& operator()(size_t a_row, size_t a_column) noexcept;
    T const& operator()(size_t a_row, size_t a_column) const noexcept;   
    
    void Member(size_t a_row, size_t a_column, T a_member);
    T At(size_t a_row, size_t a_column) const;

    size_t GetRows() const;
    size_t GetColumns() const;
    
private:
    size_t m_rows;
    size_t m_columns;
    T* m_matrix;
};

} // advcpp

#include "inl/matrix.hxx"

#endif //MATRIX_H_203
