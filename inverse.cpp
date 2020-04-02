#include<iostream>
using namespace std;
#include<vector>
using std::vector;

double** inv(vector<vector<double>>  &arr);
int main(){
    vector<vector<double>> A;
    double** B;
    double C[4][4];
    int i,j;
    A = {{12.0,3.0,4.0,5.0},{2.0,4.0,3.0,2.0}
        ,{8.0,4.0,3.0,5.0},{3.0,4.0,2.0,6.0}};

    B = inv(A);
    cout << "\n\n The required inverse is: "<<endl;
    
    for (i=0;i<4;i++){
        for (j=0;j<4;j++){
        C[i][j] = B[i][j+4];
        cout << C[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}


double** inv(vector<vector<double>> &arr){

    int i,j,k,n;
    int size1,size2,size;
    double sizemat,sizemat1,sizemat2;
    double **mat =NULL;
    double d = 0.0;
    n = arr.size();

    mat = new double*[2*n];
    for (i = 0; i < 2*n; ++i)
    {
        mat[i] = new double[2*n]();
    }
    
    cout << "Please enter the coefficients:" << endl;
    //Inputs the coefficients of the matrix
    for(i = 0; i < n; ++i)
    {
        for(j = 0; j < n; ++j)
        {
            mat[i][j] = arr[i][j];
        }
    }
    
    cout << endl << "Input matrix:" << endl;
    for (i = 0; i < n; ++i)
    {
        for (j = 0; j < n; ++j)
        {
            cout << mat[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
    
    // Initializing Right-hand side to identity matrix
    for(i = 0; i < n; ++i)
    {
        for(j = 0; j < 2*n; ++j)
        {
            if(j == (i+n))
            {
                mat[i][j] = 1;
            }
        }
    }
    
    // Partial pivoting
    for(i = n; i > 1; --i)
    {
        if(mat[i-1][1] < mat[i][1])
        {
            for(j = 0; j < 2*n; ++j)
            {
                d = mat[i][j];
                mat[i][j] = mat[i-1][j];
                mat[i-1][j] = d;
            }
        }
    }
    cout << endl;
    
    // Pivoted output
    cout << "Pivoted output: " << endl;
    for(i = 0; i < n; ++i)
    {
        for(j = 0; j < 2*n; ++j)
        {
            cout << mat[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
    
    // Reducing To Diagonal Matrix
    for(i = 0; i < n; ++i)
    {
        for(j = 0; j < 2*n; ++j)
        {
            if(j != i)
            {
                d = mat[j][i] / mat[i][i];
                for(k = 0; k < n*2; ++k)
                {
                    mat[j][k] -= mat[i][k]*d;
                }
            }
        }
    }
    cout << endl;
    
    // Reducing To Unit Matrix
    for(i = 0; i < n; ++i)
    {
        d = mat[i][i];
        for(j = 0; j < 2*n; ++j)
        {
            mat[i][j] = mat[i][j]/d;
        }
    }
    
    size1 = arr.size();
    size2 = arr[1].size();
    size = size1*size2;
    sizemat1 = sizeof(mat)/sizeof(mat[1]);
    sizemat2 = sizeof(mat[1])/sizeof(double);
    sizemat = sizemat1*sizemat2;

    // Print inverse of the input matrix
    cout<<"size of mat: "<< sizemat << endl;
    cout<<"size of input array"<<size << endl<<endl<<endl;

    for(i=0; i < n; ++i)
    {
        for(j = n; j < 2*n; ++j)
        {
            cout << mat[i][j] << "\t";
        }
        cout << endl;
   }
    
    // Deleting the memory allocated
    //for (i = 0; i < n; ++i)
   // {
   //    delete[] mat[i];
   // }
   // delete[] mat;
    return mat;

 }
