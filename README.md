# PP-Assignment

// To create a matrix of any size or type
Matrix<type,numberofrows,numberofcolumns> matrixname;

// Initilizes values to 0 when created but values can be added through the following methods
Matrix<int,2,3> myMatrix;
myMatrix={1,2,3,
          4,5,6};

// or individually

myMatrix(1,1)= 1;
myMatrix(1,2)= 2;

// The values of one matrix can also be assignned to another as long as the number of rows and columns as equal
Matrix<int,2,3> myMatrix;
myMatrix={1,2,3,
          4,5,6};
          
Matrix<int,2,3> newMatrix;

newMatrix = myMatrix;
          
          



