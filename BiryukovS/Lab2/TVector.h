#pragma once
#include "TMatrix.h"
#include <stdexcept>

template <class ValType>
TVector<ValType>::TVector(int s, int si) : Size(s), StartIndex(si), pVector(nullptr) {
    if (s < 0 || si < 0 || s > MAX_VECTOR_SIZE || si > MAX_VECTOR_SIZE - s) {
        throw std::out_of_range("TVector: invalid size or start index");
    }
    if (Size > 0) {
        pVector = new ValType[Size]();
    }
}

template <class ValType>
TVector<ValType>::TVector(const TVector& v) : Size(v.Size), StartIndex(v.StartIndex), pVector(nullptr) {
    if (Size > 0) {
        pVector = new ValType[Size];
        for (int i = 0; i < Size; ++i) {
            pVector[i] = v.pVector[i];
        }
    }
}

template <class ValType>
TVector<ValType>::~TVector() {
    delete[] pVector;
    pVector = nullptr;
    Size = 0;
    StartIndex = 0;
}

template <class ValType>
ValType& TVector<ValType>::operator[](int pos) {
    if (pos < StartIndex || pos >= StartIndex + Size) {
        throw std::out_of_range("TVector::operator[]: index out of range");
    }
    return pVector[pos - StartIndex];
}

template <class ValType>
const ValType& TVector<ValType>::operator[](int pos) const {
    if (pos < StartIndex || pos >= StartIndex + Size) {
        throw std::out_of_range("TVector::operator[]: index out of range");
    }
    return pVector[pos - StartIndex];
}

template <class ValType>
bool TVector<ValType>::operator==(const TVector& v) const {
    if (Size != v.Size) {
        return false;
    }
    if (StartIndex != v.StartIndex) {
        return false;
    }
    for (int i = 0; i < Size; ++i) {
        if (pVector[i] != v.pVector[i]) {
            return false;
        }
    }
    return true;
}

template <class ValType>
bool TVector<ValType>::operator!=(const TVector& v) const {
    return !(*this == v);
}

template <class ValType>
TVector<ValType>& TVector<ValType>::operator=(const TVector& v) {
    if (this == &v) {
        return *this;
    }
    ValType* temp = nullptr;
    if (v.Size > 0) {
        temp = new ValType[v.Size];
        for (int i = 0; i < v.Size; ++i) {
            temp[i] = v.pVector[i];
        }
    }
    delete[] pVector;
    pVector = temp;
    Size = v.Size;
    StartIndex = v.StartIndex;
    return *this;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator+(const ValType& val) const {
    TVector result(Size, StartIndex);
    for (int i = 0; i < Size; ++i) {
        result.pVector[i] = pVector[i] + val;
    }
    return result;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator-(const ValType& val) const {
    TVector result(Size, StartIndex);
    for (int i = 0; i < Size; ++i) {
        result.pVector[i] = pVector[i] - val;
    }
    return result;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator*(const ValType& val) const {
    TVector result(Size, StartIndex);
    for (int i = 0; i < Size; ++i) {
        result.pVector[i] = pVector[i] * val;
    }
    return result;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator+(const TVector& v) const {
    if (Size != v.Size || StartIndex != v.StartIndex) {
        throw std::invalid_argument("TVector::operator+: incompatible operands");
    }
    TVector result(Size, StartIndex);
    for (int i = 0; i < Size; ++i) {
        result.pVector[i] = pVector[i] + v.pVector[i];
    }
    return result;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator-(const TVector& v) const {
    if (Size != v.Size || StartIndex != v.StartIndex) {
        throw std::invalid_argument("TVector::operator-: incompatible operands");
    }
    TVector result(Size, StartIndex);
    for (int i = 0; i < Size; ++i) {
        result.pVector[i] = pVector[i] - v.pVector[i];
    }
    return result;
}

template <class ValType>
ValType TVector<ValType>::operator*(const TVector& v) const {
    if (Size != v.Size || StartIndex != v.StartIndex) {
        throw std::invalid_argument("TVector::operator*: incompatible operands");
    }
    ValType sum = ValType{};
    for (int i = 0; i < Size; ++i) {
        sum = sum + pVector[i] * v.pVector[i];
    }
    return sum;
}