#include <iostream>

template <class T>
class Matrix {
        private:
                T * m;
                int h;
                int w;

        public:
                Matrix(int x, int y);
                const T * toArray();
                T& operator()(int x, int y);
                friend std::ostream & operator<<(std::ostream& os, const Matrix<T> & a) {
                        for (int i = 0; i < a.h*a.w; i++) {
                                //os << "[";
                                //for (int j = 0; j < a.w; j++) {
                                        //if (j != 0) os << ", ";
                                        //os << i + j*a.h;
                                        os << a.m[i] << " ";
                                //}
                                //os << "]" << std::endl;
                        }
                        return os;
                }
};
