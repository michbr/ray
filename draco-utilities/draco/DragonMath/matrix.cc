#include "dragonmath.h"

using namespace std;

template <class T> Matrix<T>::Matrix(int x, int y) {
        m = new T[y*x];
        h = y;
        w = x;
}

template <class T> T& Matrix<T>::operator()(int x, int y) {
        return m[w*x + y];
}

template <class T> const T* Matrix<T>::toArray() {
        return m;
}
