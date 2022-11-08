// Muneeb Moin
// 20771958
// NE451 Assignment 3
// 2022-11-07

#include <iostream>
#include <cmath>
#include <fstream>

class Matrix {
private:
    int nRows, nCols;
    int** ndarr;
public:
    Matrix();
    Matrix(int, int);
    ~Matrix();

    //Accessors
    int& operator()(const unsigned&, const unsigned&);
    int getRows() const;
    int getCols() const;
    void printNdarr();

    //Mutators
    Matrix transpose();
    Matrix matMulByTranspose(Matrix&);
    void readFromFile(const char*);
};

Matrix::Matrix() :nRows(2), nCols(2), ndarr(new int* [2]) {
    for (int i = 0; i < nRows; i++) {
        ndarr[i] = new int[2];
    }
}

Matrix::Matrix(int r, int c) :nRows(r), nCols(c), ndarr(new int* [r]) {
    for (int i = 0; i < r; i++) {
        ndarr[i] = new int[c];
    }
}

Matrix::~Matrix() {
    for (int i = 0; i < nRows; i++) {
        delete[] ndarr[i];
    }
    delete[] ndarr;
    ndarr = nullptr;
}

int& Matrix::operator()(const unsigned& rowNo, const unsigned& ColNo) {
    return this->ndarr[rowNo][ColNo];
}

int Matrix::getRows() const {
    return nRows;
}

int Matrix::getCols() const {
    return nCols;
}

void Matrix::printNdarr() {
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nCols; j++) {
            std::cout << ndarr[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

Matrix Matrix::transpose() {
    //Tranpose any matrix. Classic transpose, no quirks.
    Matrix transposition(nCols, nRows);
    for (int i = 0; i < nCols; i++) {
        for (int j = 0; j < nRows; j++) {
            transposition(i, j) = ndarr[j][i];
        }
    }
    return transposition;
}

Matrix Matrix::matMulByTranspose(Matrix& B) {
    // NOTE: this multiplication operator is unconventional.
    // If need to use this operator as classic matrix multiplication operator, change B(j,k) to B(k,j).
    // Using that method, a transposed matrix will not be required.
    Matrix C(nRows, B.getCols());
    if (nCols == B.getRows()) {
        for (int i = 0; i < nRows; i++) {
            for (int j = 0; j < B.getCols(); j++) {
                int temp = 0;
                for (int k = 0; k < nCols; k++) {
                    temp += ndarr[i][k] * B(j, k);
                }
                C(i, j) = temp;
            }
        }
    }
    return C;
}

void Matrix::readFromFile(const char* filename) {

    std::ifstream file(filename);
    for (int i = 0; i < nRows;i++) {
        for (int j = 0; j < nCols;j++) {
            file >> ndarr[i][j];
        }
    }
    file.close();
}

int main()
{
    Matrix M1(2, 2);
    Matrix Mtemp(2, 2);
    M1.readFromFile("q10.txt");
    Mtemp.readFromFile("q11.txt");
    Matrix M2 = Mtemp.transpose();
    Matrix M3 = M1.matMulByTranspose(M2);

    std::cout << "Input Matrix #1:" << std::endl;
    M1.printNdarr();
    std::cout << std::endl;
    std::cout << "Input Matrix #2:" << std::endl;
    Mtemp.printNdarr();
    std::cout << std::endl;
    std::cout << "Output Matrix: Result of Mat#1 * Mat#2_transposed:" << std::endl;
    M3.printNdarr();
    std::cout << std::endl;
    return 0;
}
