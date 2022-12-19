//C++ program to find determinant of a matrix
#include <bits/stdc++.h>
using namespace std;


#define N 4

//Function to get determinant of matrix
int determinantOfMatrix(double mat[N][N],int n)
{

    double num1,num2,det=1,total=1;// initialize result
    int index;
 
    //temporary array for storing row
    double temp[n+1];

    //loop for traversing the diagonal elements
    for(int i=0;i<n;i++)
    {
        index=i;

        while(index<n && mat[index][i]==0)
        {
            index++;
        }
        
        if(index==n) //if there is non zero element
        {
            //the determinant of matrix as zero
            continue;
        }
		
        if(index != i)
        {
            //loop for swapping the diagonal element row and index row
            for(int j=0;j<n;j++)
            {
                swap(mat[index][j],mat[i][j]);
            }
            //determinant aign changes when we shift rows
            //go through determinant properties
            det=det*(-1);
        }
		
        for(int j=0;j<n;j++)
        {
            temp[j]=mat[i][j];
        }
		
        //traversing every row below the diagonal element
        for(int j=i+1;j<n;j++)
        {
            num1=temp[i];//value of diagonal element
            num2=mat[j][i];//value of next row element

            //traversing every column of row
            //and multiplying toevery row
            for(int k=0;k<n;k++)
            {
                //multiplying to make diagonal
                //element and next row element
                mat[j][k]=num1*mat[j][k]-num2*temp[k];
            }
            total=total*num1; //Det(kA)=kDet(A)
        }
    }
    for(int i=0;i<n;i++)
    {
       det=det*mat[i][i];
    }
    return (det/total);
}

//Driver code
int main()
{
    double mat[N][N]={{1,0,2,-1},{3,0,0,5},{2,3,4,5},{1,0,5,0}};

    printf("Determinant of the matrix is :%d",determinantOfMatrix(mat,N));

    return 0;
}
