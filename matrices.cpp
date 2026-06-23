#include <array>
#include <cmath>
#include <utility>
#include <stdexcept>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

using Vector2d = std::array<double, 2>;
using Matrix2d = std::array<Vector2d, 2>;

std::pair<Vector2d, Matrix2d> eigen_2x2(const Matrix2d& matrix){

    double a = matrix[0][0];
    double b = matrix[0][1];
    double c = matrix[1][0];
    double d = matrix[1][1];

    // Eigenvectors for diagonal matrix
    if (std::abs(b) < 1e-15 && std::abs(c) < 1e-15) {
        return {
            {a, d},
            {{{1.0, 0.0}, {0.0, 1.0}}} 
        };
    }

    // Taking p and m to decrease multiplications in the discriminant
    double m = (a + d) * 0.5;
    double p = (a - d) * 0.5;

    // Finding the discriminant now with fewer multiplications
    double delta = p * p + b * c;

    // Ignoring complex eigenvalues
    if (delta < 0.0) throw std::runtime_error("Complex eigenvalues are not supported.");
       
    // Square root of the discriminant 
    double sqrt_D = std::sqrt(delta);

    // Eigenvalues
    double eigen1 = m + sqrt_D;
    double eigen2 = m - sqrt_D;

    // Initializing the vector elements
    double v1x, v1y, v2x, v2y;

    /* Calculating Eigenvectors by getting rid of catastrophic cancellation 
       by only adding or subtracting p and sqrt_D when they are of the same sign */
    if (p > 0.0) {
        v1x = p + sqrt_D;   v1y = c;
        v2x = b;            v2y = -p - sqrt_D;
    } else {
        v1x = b;            v1y = sqrt_D - p;
        v2x = p - sqrt_D;   v2y = c; 
    }

    // Squared norms
    double n1_sq = v1x * v1x + v1y * v1y;
    double n2_sq = v2x * v2x + v2y * v2y;

    // If any of the eigen vectors collapse to zero
    if (n1_sq < 1e-300) {
        v1x = v2x; v1y = v2y; n1_sq = n2_sq;
    } else if (n2_sq < 1e-300) {
        v2x = v1x; v2y = v1y; n2_sq = n1_sq;
    }

    // Final Normalization 
    double inorm1 = 1.0 / std::sqrt(n1_sq);
    double inorm2 = 1.0 / std::sqrt(n2_sq);

    return {
        {eigen1, eigen2},
        {{{v1x * inorm1, v1y * inorm1}, {v2x * inorm2, v2y * inorm2}}}
    };
}

int factorial(int n){
    // work on a better optimization
    if (n == 0)
        return 1;
    return n*factorial(n-1);
}

int choose(int n, int r){
    //implement the optimized factorial function
    return 0;
}

double determinant_2x2(const Matrix2d& matrix){
    const double a = matrix[0][0];
    const double b = matrix[0][1];
    const double c = matrix[1][0];
    const double d = matrix[1][1];
    return (a * d) - (b * c);
}

Matrix2d inverse_2x2(const Matrix2d &matrix){
 
    const double a = matrix[0][0];
    const double b = matrix[0][1];
    const double c = matrix[1][0];
    const double d = matrix[1][1];

    const double det = (a * d) - (b * c);
    
    if(std::abs(det) < 1e-15) throw std::runtime_error("Matrix is singular and cannot be inverted.");
    
    const double inverse_det = 1.0 / det;
    
    return{{
        { d * inverse_det, -b * inverse_det },
        {-c * inverse_det,  a * inverse_det }
    }};
}

Matrix2d matmul_2x2(const Matrix2d &matrix1, const Matrix2d &matrix2){
    const double a1 = matrix1[0][0];
    const double a2 = matrix2[0][0];
    const double b1 = matrix1[0][1];
    const double b2 = matrix2[0][1];
    const double c1 = matrix1[1][0];
    const double c2 = matrix2[1][0];
    const double d1 = matrix1[1][1];
    const double d2 = matrix2[1][1];

    return{{
        {a1*a2 + b1*c2, a1*b2 + b1*d2},
        {c1*a2 + d1*c2, c1*b2 + d1*d2}
    }};

}

Matrix2d matadd_2x2(const Matrix2d &matrix1, const Matrix2d &matrix2){
    const double a1 = matrix1[0][0];
    const double a2 = matrix2[0][0];
    const double b1 = matrix1[0][1];
    const double b2 = matrix2[0][1];
    const double c1 = matrix1[1][0];
    const double c2 = matrix2[1][0];
    const double d1 = matrix1[1][1];
    const double d2 = matrix2[1][1];

    return{{
        {a1 + a2, b1 + b2},
        {c1 + c2 , d1 + d2}
    }};

}


PYBIND11_MODULE(matrices, m){
    m.doc() = "Matrix helper functions handling 2x2 matrix types natively";

    m.def(
        "eigen_2x2",
        &eigen_2x2,
        py::arg("matrix"),
        "Returns eigenvalues and eigenvectors given a 2x2 matrix object [[a, b], [c, d]]");
   
    m.def(
        "det_2x2",
        &determinant_2x2,
        py::arg("matrix"),
        "Returns the determinant given a 2x2 matrix object [[a, b], [c, d]]");
    m.def(
        "inverse_2x2",
        &inverse_2x2,
        py::arg("matrix"),
        "Returns the inverse matrix given a 2x2 matric object [[a, b], [c, d]]");
    m.def(
        "matmul_2x2",
        &matmul_2x2,
        py::arg("matrix1"),
        py::arg("matrix2"),
        "Mutiplies two matrix objects and returns the resultant matrix");
    m.def(
        "matadd_2x2",
        &matadd_2x2,
        py::arg("matrix1"),
        py::arg("matrix2"),
        "Adds two matrix objects and returns the resultant matrix");
}

