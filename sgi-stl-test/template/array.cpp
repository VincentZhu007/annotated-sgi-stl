//
// Created by Vincent Zhu on 2021/7/30.
//

#include <iostream>
#include <exception>

template<typename T, size_t N>
class Array {
public:
    T& operator[](size_t i)
    {
        if (i >= N) {
            throw std::out_of_range("out of range");
        }
        return element_[i];
    }
private:
    T element_[N];

};

int main(int argc, char *argv[]) throw(std::out_of_range)
{
    Array<int, 10> intArray;
    Array<double, 20> doubleArray;
    try {
        intArray[0] = 100;
        doubleArray[19] = 3.14;
        std::cout << "int array [0]: " << intArray[0] << std::endl;
        std::cout << "double array [19]: " << doubleArray[19] << std::endl;
        std::cout << "int array [10]: " << intArray[10] << std::endl;
    } catch (std::out_of_range e) {
        std::cerr << "caught exception: " << e.what() << std::endl;
    }

    return 0;
}
