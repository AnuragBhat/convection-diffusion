#include<iostream>
#include<cstdlib>
#include<cmath>
#include<iomanip>
#include<vector>
#include<fstream>
#include<cstring>

using namespace std;
using std::setw;
using std::ofstream;

double** inv(vector<vector<double>>  &arr);
double* mult(vector<vector<double>> &arr,vector<double> &array);

int main(){

	//DEFINING THE PARAMETERS
	double dom[2] = {0.0,1.0};
	int Nelem,nodes,i,j,k,p,q,T[2];	  
	double h,L,Pe,nu,a,alpha;
	typedef vector<vector<double>> matrixd;	//DEFINING A DOUBLE ARRAY MATRIX TYPE
	typedef vector<double> matrixs;   //DEFINING A SINGLE ARRAY MATRIX TYPE
	typedef vector<vector<int>> matrixint;   //DEFINING A DOUBLE ARRAY INT MATRIX TYPE
	double **K_invf;
	double *U_f;
	double K_i[2][2], St[2][2];
	int nodes_Dir[2];
	int choice, num = 21;
	double numer, denom;
	string str;
	ofstream output;
	system("cls");
	
	cout << "Please enter the number of elements" << endl;
	cout << "The number of elements: "; 
	cin >> Nelem; cout << endl;
	
	h = (dom[1] - dom[0])/Nelem;	//STEP SIZE
	L = dom[1] - dom[0];
	
	cout << "Please enter the Peclet number" << endl;
	cout << "Peclet number: "; 
	cin >> Pe; cout << endl;
	
	cout << "Please enter the value of diffusion coefficient" << endl;
	cout << "Diffusion coefficient: "; 
	cin >> nu; cout << endl;

	flag:
	cout << "Select the method: \n[1] Galerkin Method\n[2] Petrov Galerkin Method" << endl;
	cin >> choice; cout << endl;
	
	a = Pe*2.0*nu/h;		   //DEFINING 'a' IN TERMS OF Pe NUMBER	
	alpha = (1.0/tanh(Pe)) - (1.0/Pe);		//DEFINING ALPHA (OPTIMUM VALUE)
	nodes = Nelem + 1;

	//ALLOCATING DIRICHLET NODES
	nodes_Dir[0] = 0;
	nodes_Dir[1] = nodes-1;
	
	//DEFINING MATRICES
	matrixint conn(Nelem, vector<int>(2)); //DEFINING CONNECTIVITY MATRIX
	matrixs X(nodes);	//DEFINING COORDINATE MATRIX
	matrixd K(nodes, vector<double>(nodes)); //DEFINING STIFFNESS MATRIX
	matrixs F(nodes);	//DEFINING FORCE MATRIX
	matrixs U(nodes); 	//DEFINING SOLUTION MATRIX
	matrixs U_exact(nodes); //DEFINING EXACT SOLUTION
	matrixd K_f(nodes-2,vector<double>(nodes-2));	//DEFINING REDUCED K MATRIX
	matrixs F_f(nodes-2);	//DEFINING REDUCED F MATRIX
	matrixd K_inv(nodes-2, vector<double>(nodes-2));
	matrixd Result(nodes, vector<double>(3)); //RESULT FILE TO OUTPUT

	//BUILDING COORDINATE MATRIX
	for (i=0;i<nodes;i++){
		X[i] = i*h;
	}
	cout << endl;
    //BUILDING CONNECTIVITY MATRIX
	cout << "\nThe connectivity matrix: " << endl;
	cout << setw(5);
	for (i=0;i<Nelem;i++){
		for (j=0;j<2;j++){
			conn[i][j] = i + j +1;
			cout << conn[i][j] << setw(5);
		}
		cout << endl;
	}	

	switch (choice){
		case 1: //GALERKIN
		str = "Galerkin";
		K_i[0][0] = (-a/2) + (nu/h);
		K_i[0][1] = (a/2) + (-nu/h);
		K_i[1][0] = (-a/2) + (-nu/h);
		K_i[1][1] = (a/2) + (nu/h);
		break;

		case 2: //PETROV GALERKIN
		str = "Petrov-Galerkin";
		//STABILITY TERM
		St[0][0] = alpha*a/2;
		St[0][1] = -alpha*a/2;
		St[1][0] = -alpha*a/2;
		St[1][1] = alpha*a/2;

		K_i[0][0] = (-a/2) + (nu/h) + St[0][0];
		K_i[0][1] = (a/2) + (-nu/h) + St[1][0]; 
		K_i[1][0] = (-a/2) + (-nu/h) + St[1][0];
		K_i[1][1] = (a/2) + (nu/h) + St[1][1];
		break;

		default:
		cout << "Wrong input, please try again\n" << endl;
		goto flag;
	}
	
	//INITIALIZING THE K MATRIX
	for (i=0;i<nodes;i++){
		for (j=0;j<nodes;j++){
			K[i][j] = 0.0;
		}
	}	
	//INITIALIZING THE F MATRIX
	for (i=0;i<nodes;i++){
		F[i] = 0.0;
	}
	//INITIALIZING THE U MATRIX
	for (i=0;i<nodes;i++){
		U[i] = 0.0;
	}

	//ASSEMBLING THE GLOBAL STIFFNESS MATRIX MATRIX
	for (i=0;i<Nelem;i++){
		T[0] = (conn[i][0]) - 1;
		T[1] = (conn[i][1]) - 1;
		K[T[0]][T[0]] = K[T[0]][T[0]] + K_i[0][0];
		K[T[0]][T[1]] = K[T[0]][T[1]] + K_i[0][1];
		K[T[1]][T[0]] = K[T[1]][T[0]] + K_i[1][0];
		K[T[1]][T[1]] = K[T[1]][T[1]] + K_i[1][1];
	}
		
	//PRINTING THE GLOBAL STIFFNESS MATRIX
	if (Nelem < num){
		cout << "\n\nThe stiffness matrix is: " << endl;
		cout << setw(4);
		for (i=0;i<nodes;i++){
			for (j=0;j<nodes;j++){
				cout <<	K[i][j] << setw(4);
			}
			cout << endl;
		} 
	}
	else {
		cout << "The element count is too large to display matrix on screen..";
	}
	//----------------------------SOLUTION GENERATION------------------------------//

	//ASSIGNING DIRICHLET VALUES
	U[nodes_Dir[0]] = 1.0;
	U[nodes_Dir[1]] = 0.0;
	
	//BUILDING THE F MATRIX
	for (i=0;i<nodes;i++){
		F[i] = F[i] - ((K[i][nodes_Dir[0]] * U[nodes_Dir[0]]) +  (K[i][nodes_Dir[1]] * U[nodes_Dir[1]]));
	}
	//BUILDING REDUCED K MATRIX
	p=0;
	for(i=1;i<nodes-1;i++){
		q=0;
		for (j=1;j<nodes-1;j++){
			K_f[p][q] = K[i][j];
			q++;
		}
		p++;
	}
	//PRINTING REDUCED K MATRIX
	if (Nelem < num){
		cout << "\n\nThe reduced K matrix:"<< endl;
		cout << setw(4);
		for(i=0;i<nodes-2;i++){
			for (j=0;j<nodes-2;j++){
				cout << K_f[i][j] << setw(4);			
			}
			cout << endl;
		} 
	}

	//BUILDING REDUCED FORCE MATRIX
	p=0;
	for(i=1;i<nodes-1;i++){
		F_f[p] = F[i];
		p++;
	}

	//PRINT FORCE VECTOR
	if (Nelem < num){
		cout << "\n\nThe Force vector: " << endl;
		cout << setw(4);
		for(i=0;i<nodes;i++){
			cout << F[i] << setw(4)<< endl;
		}

	//PRINT REDUCED FORCE VECTOR
		cout << "\n\nThe reduced Force vector: " << endl;
		cout << setw(4);
		for(i=0;i<nodes-2;i++){
			cout << F_f[i] << setw(4)<< endl;
		} 
	}
	K_invf = inv(K_f); //INVERSE OBTAINED BY PERFORMING GAUSSIAN ELIMINATION

	//STRUCTURING THE INVERSE MATRIX
	for (i=0;i<nodes-2;i++){
        for (j=0;j<(nodes-2);j++){
    	    K_inv[i][j] = K_invf[i][j+(nodes-2)];
        }
    }
	cout << endl << endl << "Generating solution...\n\n";
	//PRINTING THE INVERSE STIFFNESS REDUCED MATRIX
	/*
		cout << "\n\nThe inverse of the reduced K matrix: " << endl;
		cout << setw(12);
		for (i=0;i<nodes-2;i++){
			for (j=0;j<nodes-2;j++){
				cout << K_inv[i][j] << setw(12);
			}
			cout << endl;
		}
	*/
	//OBTAINING SOLUTION FROM
	// [K_f][U_f] = [F_f] 	
	U_f = mult(K_inv,F_f);

	//ASSEMBLING THE SOLUTION MATRIX
	p = 0;
	for (i=1;i<nodes-1;i++){
		U[i] = U_f[p];
		p++;
	}
	//CALCULATING EXACT SOLUTION
	for (i =0;i<nodes;i++){
		numer = 1.0 - exp((a*(X[i]-L))/nu);
		denom = 1.0 - exp(-a*L/nu);
		U_exact[i] = numer/denom;
	}
	if (Nelem < 101){
		cout << str << setw(10) << "Exact" << endl;
			for (i=0;i<nodes;i++){
				cout <<setw(7)<< U[i] <<setw(15)<< U_exact[i] << endl;
			}
	}

	for (i=0;i<nodes;i++){
		Result[i][0] = U[i];
		Result[i][1] = U_exact[i];
		Result[i][2] = X[i];
	}

	//GENERATING OUTPUT FILE WITH SOLUTION AND NODAL COORDINATE
	output.open("Result.dat");
	if (!output){
		cerr << "Error opening file" << endl;
		exit(1);
	}
	output << str << "\tExact Solution\tCoordinate" << endl;
	for (i=0;i<nodes;i++){
		for (j=0;j<3;j++){
			output << Result[i][j] << "\t";
		}
		output << endl;
	}
	output.close();
	cout << "Results has been generated";

	delete[] K_invf;
	delete[] U_f;
	return 0;
}

double** inv(vector<vector<double>>  &arr){
	int i,j,k,n;
    int size1,size2,size;
    double sizemat,sizemat1,sizemat2;
    double **mat =NULL;
    double d = 0.0;
    n = arr.size();

    mat = new double*[2*n];
    for (i=0;i<2*n;++i){
        mat[i] = new double[2*n]();
    }
    
    cout << "\n\nGenerating inverse of the matrix.....";
    //Inputs the coefficients of the matrix
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            mat[i][j] = arr[i][j];
        }
    }
    
    // Initializing Right-hand side to identity matrix
    for(i=0;i<n;i++){
        for(j=0;j<2*n;j++){
            if(j==(i+n)){
                mat[i][j] = 1;
            }
        }
    }
    
    // Partial pivoting
    for(i=n;i>1;i--){
        if(mat[i-1][1] < mat[i][1]){
            for(j=0;j<2*n;j++){
                d = mat[i][j];
                mat[i][j] = mat[i-1][j];
                mat[i-1][j] = d;
            }
        }
    }

    // Reducing To Diagonal Matrix
    for(i=0;i<n;i++){
        for(j=0;j<2*n;j++){
            if(j != i){
                d = mat[j][i] / mat[i][i];
                for(k=0;k<2*n;k++){
                    mat[j][k] -= mat[i][k]*d;
                }
            }
        }
    }
    
    // Reducing To Unit Matrix
    for(i=0;i<n;i++){
        d = mat[i][i];
        for(j=0;j<2*n;j++){
            mat[i][j] = mat[i][j]/d;
        }
    }
    return mat;
}	

double* mult(vector<vector<double>> &arrd,vector<double> &arrs){
	int i,j,n;
	double* mat = NULL;
	n = arrd.size();

	mat = new double[n];
	//PERFORMING MATRIX MULTIPLICATION
	//OF A 2-D MATRIX WITH A 1-D VECTOR
	for (i=0;i<n;i++){
			for (j=0;j<n;j++){
				mat[i] += arrd[i][j] * arrs[j]; 
			}
	}
	return mat;
}
