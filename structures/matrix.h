#pragma once

#include <cstddef>
#include <algorithm>
template <typename T>
class matrix {
public:
    matrix();
    matrix(size_t rows, size_t cols);
    matrix(size_t rows, size_t cols, T def);
    matrix(const matrix& mat);
    matrix(matrix&& mat);
    matrix& operator=(matrix mat);
    T& operator()(ssize_t col, ssize_t row) noexcept;
    const T& At(ssize_t col, ssize_t row) const noexcept;
    matrix& Resize(size_t rows, size_t cols);
    ~matrix();

    ssize_t GetRowsCnt() const;
    ssize_t GetColsCnt() const;

private:
    size_t rows_ = 0;
    size_t cols_ = 0;
    T* data_ = nullptr;
};
template <typename T>
matrix<T>::matrix() {
}

template <typename T>
matrix<T>::matrix(const matrix<T>& mat) : matrix(mat.rows_, mat.cols_) {
    for (size_t y = 0; y < rows_; ++y) {
        std::copy_n(mat.data_ + y * cols_, cols_, data_ + y * mat.cols_);
    }
}

template <typename T>
matrix<T>::matrix(size_t rows, size_t cols) : rows_(rows), cols_(cols) {
    data_ = new T[rows * cols];
}

template <typename T>
matrix<T>::matrix(size_t rows, size_t cols, T def) : matrix(rows, cols) {
    for (size_t i = 0; i < rows * cols; ++i) {
        data_[i] = def;
    }
}

template <typename T>
matrix<T>::matrix(matrix&& mat) {
    std::swap(mat.data_, data_);
    std::swap(mat.rows_, rows_);
    std::swap(mat.cols_, cols_);
}

template <typename T>
matrix<T>& matrix<T>::operator=(matrix mat) {
    std::swap(mat.data_, data_);
    std::swap(mat.rows_, rows_);
    std::swap(mat.cols_, cols_);
    return *this;
}

template <typename T>
const T& matrix<T>::At(ssize_t y, ssize_t x) const noexcept {
    x = std::min<ssize_t>(static_cast<ssize_t>(cols_ - 1), std::max<ssize_t>(0, x));
    y = std::min<ssize_t>(static_cast<ssize_t>(rows_ - 1), std::max<ssize_t>(0, y));
    return data_[y * cols_ + x];
}

template <typename T>
T& matrix<T>::operator()(ssize_t y, ssize_t x) noexcept {
    x = std::min<ssize_t>(static_cast<ssize_t>(cols_ - 1), std::max<ssize_t>(0, x));
    y = std::min<ssize_t>(static_cast<ssize_t>(rows_ - 1), std::max<ssize_t>(0, y));
    return data_[y * cols_ + x];
}

template <typename T>
matrix<T>& matrix<T>::Resize(size_t rows, size_t cols) {
    T* tmp = new T[rows * cols];
    for (size_t y = 0; y < std::min(rows, rows_); ++y) {
        std::copy_n(data_ + y * cols_, std::min(cols, cols_), tmp + y * cols);
    }
    std::swap(tmp, data_);
    delete[] tmp;
    rows_ = rows;
    cols_ = cols;
    return *this;
}

template <typename T>
matrix<T>::~matrix() {
    delete[] data_;
}

template <typename T>
ssize_t matrix<T>::GetRowsCnt() const {
    return rows_;
}

template <typename T>
ssize_t matrix<T>::GetColsCnt() const {
    return cols_;
}