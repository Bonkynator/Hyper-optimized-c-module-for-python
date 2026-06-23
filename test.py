import matrices

# Define a 2D matrix smoothly as a python iterable
matrix1 = [
    [4.0, 1.0],
    [2.0, 3.0]
]
matrix2=[
    [1,2],
    [2,3]
]

# Pass the single matrix structure directly
eigenvalues, eigenvectors = matrices.eigen_2x2(matrix1)
det = matrices.det_2x2(matrix1)
inverse = matrices.inverse_2x2(matrix1)
print("Eigenvalues:", eigenvalues)        
print("Eigenvectors Matrix:", eigenvectors) 
print("Determinant:", det)               
print("Inverse: ", inverse)
print(matrices.matmul_2x2(matrix1, matrix2))
