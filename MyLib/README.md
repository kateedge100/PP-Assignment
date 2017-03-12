#Maths Library README

This is the README for my maths library, the submitted folder contains the folders

MyLib: Contains all header files for my library as well as header files GLFunctions.h and SDLOpenGL.h used for the demo program.
       Also contains the folder Tests containing tests for matrices, vectors and functions.

LibDemo: Contains a simple OpenGL programme (originallt written by Jon Macey) and modified by me to run using my maths library.

TestProgram:  A test program set up with my library in order to assist in trying out the libraries features and make it easier to mark.


# Matrix

To create a matrix of any size or type:

Matrix<type,number of rows, number of columns> matrixname;

Initilizes values to 0 when created but values can be added through the following methods:

Initializer list:

Matrix<int,2,3> myMatrix={1,2,3,4,5,6};

Individually:

Matrix<int,2,3> myMatrix;
myMatrix(1,1)= 1;
myMatrix(1,2)= 2;

The values of one matrix can also be assignned to another:

Matrix<int,2,3> myMatrix={1,2,3,4,5,6};
Matrix<int,2,3> newMatrix;
newMatrix = myMatrix;

-Matrix Operators:
  -assignment = (matrix only)
  -equility == (matrix only)
  -addition + (matrix or scalar)
  -subtraction - (matrix or scalar)
  -multiplication *(matrix or scalar)
  -division / (scalar only)
  -negative - (matrix only)


-Matrix Functions:
  -Inverse
  -Determinant
  -Minor Matrix
  -Transpose
  -Orthogonal Test
  -Resize

# Vectors

As a vector is just a special type of a matrix it is created in the same class as a matrix with a boolean m_vector being set to true if
either ROWS or COLS is set to 1 upon being constructed. This means that vectors are constructed in the exact same way as matrices.

For a 3D row vector:
Matrix<float,1,3> myVec{1,2,3}

-Vector Operations:
 -assignment = (vector only)
 -equility == (vector only)
 -addition + (vector or scalar)
 -subtraction - (vector or scalar)
 -multiplication *(vector or scalar)
 -division / (vector or scalar)
 -negative - (vector only)

-Vector Functions:
  -Magnitude
  -Dot
  -Angle
  -Cross
  -Rotate
  -Normalize
  -Resize

For functions that can only be used on a vector the function vectorCheck is called and will throw an error if its a matrix

# Quarternions
As quaternions are a fixed size the template only offers a type parameter.

To create a quaternion you can either:

Use default constructor that initializes the quaternion to zero : Quaternion<T> myQ;

Use the initializer constructor: Quaternion<T> myQ(1,2,3,4);

-Quaternion Operators:
  -assignment = (quaternion only)
  -equility == (quaternion only)
  -addition + (quaternion or scalar)
  -subtraction - (quaternion or scalar)
  -multiplication *(quaternion or scalar)
  -division / (scalar only)
  -negative - (quaternion only)

-Quaternion Functions:
  -Norm
  -Conjugate
  -Inverse
