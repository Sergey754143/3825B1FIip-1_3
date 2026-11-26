#pragma once
#include <stdexcept>
#include "../../includes/Lab2/utmatrix.h"


template <class ValType>
TMatrix<ValType>::TMatrix(int s) : TVector<TVector<ValType>>(s, 0) {
    if (s < 0 || s > MAX_MATRIX_SIZE) {
        throw std::out_of_range("TMatrix: invalid size");
    }
    for (int i = 0; i < s; ++i) {
        (*this)[i] = TVector<ValType>(s - i, i);
    }
}

template <class ValType>
TMatrix<ValType>::TMatrix(const TMatrix& mt) : TVector<TVector<ValType>>(mt) {}

template <class ValType>
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType>>& mt) : TVector<TVector<ValType>>(mt) {
    int n = this->GetSize();
    if (n < 0 || n > MAX_MATRIX_SIZE) {
        throw std::out_of_range("TMatrix: invalid matrix size");
    }
    for (int i = 0; i < n; ++i) {
        const TVector<ValType>& row = (*this)[i];
        if (row.GetStartIndex() != i || row.GetSize() != n - i) {
            throw std::out_of_range("TMatrix: source vector does not match triangular structure");
        }
    }
}

template <class ValType>
bool TMatrix<ValType>::operator==(const TMatrix& mt) const {
    return TVector<TVector<ValType>>::operator==(mt);
}

template <class ValType>
bool TMatrix<ValType>::operator!=(const TMatrix& mt) const {
    return !(*this == mt);
}

template <class ValType>
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix& mt) {
    if (this == &mt) {
        return *this;
    }
    TVector<TVector<ValType>>::operator=(mt);
    return *this;
}

template <class ValType>
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix& mt) const {
    if (this->GetSize() != mt.GetSize()) {
        throw std::invalid_argument("TMatrix::operator+: size mismatch");
    }
    TVector<TVector<ValType>> result = TVector<TVector<ValType>>::operator+(mt);
    return TMatrix<ValType>(result);
}

template <class ValType>
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix& mt) const {
    if (this->GetSize() != mt.GetSize()) {
        throw std::invalid_argument("TMatrix::operator-: size mismatch");
    }
    TVector<TVector<ValType>> result = TVector<TVector<ValType>>::operator-(mt);
    return TMatrix<ValType>(result);
}