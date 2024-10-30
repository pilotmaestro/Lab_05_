#include<iostream>
#include<chrono>
#include<cmath>
#include<memory>

namespace cc {
    const int len_val {14}; // байт для числа
    const std::string chars_value("+0123456789"); // value
}

struct Matrix {
    size_t size;
    double** array;

    void fill();

    void reduce();

    void out();

    void outColor();

    Matrix(size_t size_);

    Matrix(const Matrix& matrix);

    Matrix(Matrix&& matrix);

    ~Matrix();
};

bool isSize(std::string val);

int main() {

    std::string size;

    do {
        std::cout << "Введите значение размера матрицы: ";
        std::cin >> size;
    } while(!isSize(size));

    Matrix matrix(std::stoul(size));

    matrix.fill();

    matrix.out();

    std::cout << std::endl;

    matrix.reduce();

    matrix.outColor();

//    std::cout << std::endl;

//    matrix.out();

}

bool isSize(std::string val) {

    if (val.find_first_not_of(cc::chars_value) != std::string::npos) {
        std::cout << "Некорректное значение ... " << std::endl;
        return false;
    }
    if (val.rfind('+') != 0 && val.rfind('+') != std::string::npos) {
        std::cout << "Некорректное значение ... " << std::endl;
        return false;
    }
    if (val.size() > cc::len_val) {
        std::cout << "Слишком длинное ... " << std::endl;
        return false;
    }
    if (std::stoi(val) < 1) {
        std::cout << "Некорректное значение ... " << std::endl;
        return false;
    }
    return true;
}

void Matrix::fill() {
    std::srand(unsigned(std::time(0)));
    for(size_t i = 0; i < size; i++) {
        for(size_t j = 0; j < size; j++) {
            array[i][j] = rand() % 100;
        }
    }
}

void Matrix::reduce() {

    // обнуление ниже диагонали

    double k(0.0);

    for(size_t i = 1; i < size; i++) {
        for(size_t j = 0; j < i; j++) {
            k = array[i][j] / array[j][j];
            for(size_t n = 0; n < size; n++) {
                array[i][n] = array[i][n] - (array[j][n] * k);
                if (i != n) {
                    array[i][n] = std::round(array[i][n]);
                }
            }
        }
    }

    // обнуление выше диагонали

    for(ssize_t i = size - 2; i >= 0; i--) {
        for(ssize_t j = size - 1; j > i; j--) {
            k = array[i][j] / array[j][j];
            for(ssize_t n = 0; n < static_cast<ssize_t>(size); n++) {
                array[i][n] = array[i][n] - (array[j][n] * k);
                if (i != n) {
                    array[i][n] = std::round(array[i][n]);
                }
            }
        }
    }
}

void Matrix::out() {

    std::unique_ptr<size_t> maxPlaces(new size_t [size]);

    for(size_t i = 0; i < size; i++) *(maxPlaces + i) = 0;


    for(size_t j = 0; j < size; j++) {
        for(size_t i = 0; i < size; i++) {
            size_t max(std::to_string(array[i][j]).size());
            if (max > maxPlaces[j]) {
                maxPlaces[j] = std::to_string(array[i][j]).size();
            }
        }
    }

    for(size_t i = 0; i < size; i++) {
        for(size_t j = 0; j < size; j++) {

            std::string cell(std::to_string(array[i][j]));
            cell.append(maxPlaces[j] - cell.size(), ' ');

            std::cout << cell << " ";
        }
        std::cout << std::endl;
    }
}

void Matrix::outColor() {
    size_t maxPlaces[size];
    for(size_t i = 0; i < size; i++) maxPlaces[i] = 0;


    for(size_t j = 0; j < size; j++) {
        for(size_t i = 0; i < size; i++) {
            size_t max(std::to_string(array[i][j]).size());
            if (max > maxPlaces[j]) {
                maxPlaces[j] = std::to_string(array[i][j]).size();
            }
        }
    }

    for(size_t i = 0; i < size; i++) {
        for(size_t j = 0; j < size; j++) {

            std::string cell(std::to_string(array[i][j]));
            cell.append(maxPlaces[j] - cell.size(), ' ');
            if (i != j) {
                std::cout << "\e[0;32m" << cell << "\e[0m" << " ";
            }
            else {
                std::cout << "\e[1;31m" << cell << "\e[0m" << " ";
            }
        }
        std::cout << std::endl;
    }
}



Matrix::Matrix(size_t size_) : size(size_), array(nullptr) {
    array = new double* [size];

    for(size_t i = 0; i < size; i++) {
        array[i] = new double[size];
        for(size_t j = 0; j < size; j++) { array[i][j] = 0.0; }
    }
}

Matrix::Matrix(const Matrix& matrix) : size(matrix.size), array(nullptr) {
    array = new double* [size];

    for(size_t i = 0; i < size; i++) {
        array[i] = new double[size];
        for(size_t j = 0; j < size; j++) { array[i][j] = matrix.array[i][j]; }
    }
}

Matrix::Matrix(Matrix&& matrix) : size(matrix.size), array(nullptr) { std::swap(array, matrix.array); }

Matrix::~Matrix() {
    for(size_t i = 0; i < size; i++) {
        delete [] array[i];
    }

    delete [] array;
}
