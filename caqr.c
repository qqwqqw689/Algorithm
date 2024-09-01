#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<mpi.h>
#include<lapacke.h>
#include<cblas.h>
#include<math.h>

float guassrand()
{
	static float V1, V2, S;
	static int phase = 0;
	float num;

	if(phase == 0) 
	{
		do 
		{
			float U1 = (float)rand() / RAND_MAX;
			float U2 = (float)rand() / RAND_MAX;
			V1 = 2 * U1 - 1;
			V2 = 2 * U2 - 1;
			S = V1 * V1 + V2 * V2;
		} while(S >= 1 || S == 0);

		num = V1 * sqrt(-2 * log(S) / S);
	} 
	else
	{
		num = V2 * sqrt(-2 * log(S) / S);
	}
	phase = 1 - phase;
	return num;
}


/* Generate distributed input matrix A of size n * d*/
void getIpMat(int rank, int np, float *A, int ldA, int gn, int d)
{
        if(rank == 0)
        {
                int i, j, r;
                for(r=0; r<np; ++r)
                {
                        int begin = (gn * r)/np;
                        int end = (gn * (r + 1))/np;
                        int ln = end - begin;
                        float *Atmp =(float*)malloc(sizeof(float)*ln*d);
                        for(i=0;i<ln;++i)
                        {
                                for(j=0;j<d;++j)
                                {
                                        Atmp[i+(j*ldA)] = guassrand();
                                }
                        }
                        if(r == 0)
                        {
                                LAPACKE_slacpy(LAPACK_COL_MAJOR, 'A', ln, d, Atmp, ldA, A, ldA);
                        }
                        else
                                MPI_Send(Atmp, ln*d, MPI_FLOAT, r, 0, MPI_COMM_WORLD);
                        free(Atmp);
                }
        }
        else
        {
                MPI_Status status;
                int begin = (gn * rank)/np;
                int end = (gn * (rank + 1))/np;
                int ln = end - begin;
                MPI_Recv(A, ln*d, MPI_FLOAT, 0, 0, MPI_COMM_WORLD, &status);
        }
}

/*Check if the number of processor passed is power of 2*/
int isPowerOfTwo(int np) 
{ 
   if(np==0) 
   	return 0; 
  
   if(ceil(log2(np)) == floor(log2(np)))
	return 1;
   else
	return 0;
}

/*Extract R from Q*/
void extractR(int rank, float *A, int ldA, float *R, int ldR, int n, int d)
{
	int i,j;
	for(i=0; i<n; ++i)
	{
		for(j=0; j<d; ++j)
		{
			R[i+(j*ldR)] = A[i+(j*ldA)];
			if(i>j)
				R[i+(j*ldR)] = 0.0;
		}
	}
}

/* Stack Rs */
void stack(float *R1, float *R2, float *RR, int d)
{
    int i,j;
    for (j=0; j<d; j++) {
        for (i=0; i<d; i++) {
            RR[i+j*(2*d)] = R1[i+j*d];
            RR[i+d+j*(2*d)] = R2[i+j*d];
        }
    }
}

/* Ustack Rs */
void unstack(float *R1, float *R2, float *RR, int d)
{
    int i,j;
    for (j=0; j<d; j++) {
        for (i=0; i<d; i++) {
            R1[i+j*d] = RR[i+j*(2*d)];
            R2[i+j*d] = RR[i+d+j*(2*d)];
        }
    }
}

void printArray(char *Arrname,float *Arr, int ldArr, int n, int d)
{
        printf("%s :\n",Arrname);
        int i,j;
        for(i=0; i<n; ++i)
        {
                for(j=0; j<d; ++j)
                {
                        printf("%f\t",Arr[i+(j*ldArr)]);
                }
                printf("\n");
        }
}


/*Tall Skinny Communication avoidance QR
 * 1)First perform QR on each process
 * 2)Stack Rs by sharing accross alternate process
 * 3)Perform QR on the stacked Rs until you get the final Q
 * 4)Multiply all Qs back to process 0
 * ln = local n
 * d = no of columns
 * */
void comm_avoidance_qr(int rank, int np, float *A, int ldA, float* R, int ldR, int ln, int d)
{
	float *tau = (float*)malloc(sizeof(float)*d);
    float *Q1 = (float*)malloc(sizeof(float)*d*d);
    float *Q2 = (float*)malloc(sizeof(float)*d*d);
	float *Q = (float*)malloc(sizeof(float)*2*d*d*log2(np));
	float *RR = (float*)malloc(sizeof(float)*2*d*d);
	float *R1 = (float*)malloc(sizeof(float)*d*d);
	float *R2 = (float*)malloc(sizeof(float)*d*d);
	float *stackedR = (float*)malloc(sizeof(float)*2*d*d);
	float *Qtmp = (float*)malloc(sizeof(float)*2*d*d);
    float *Atmp = (float*)malloc(sizeof(float)*2*ln*d);
	
	LAPACKE_sgeqrf(LAPACK_COL_MAJOR, ln, d, A, ldA, tau);
	extractR(rank, A, ldA, R1, ldR, d, d);
    LAPACKE_sorgqr(LAPACK_COL_MAJOR, ln, d, d, A, ldA, tau);

	int r;
    MPI_Status status;
    for (r=0; r<log2(np); r++) {
    	if (r== 0 || !( rank & ((1<<r)-1) )) {
			/** Receiver **/
        	if ( !(rank & (1<<r))  ) { 
        		MPI_Recv(R2, d*d, MPI_FLOAT, rank ^ (1<<r), 0, MPI_COMM_WORLD, &status);
        		stack(R1, R2, RR, d);
				/** library to perform QR on the stacked R **/ 
        		LAPACKE_sgeqrf(LAPACK_COL_MAJOR, 2*d, d, RR, 2*d, tau); 
				/** library to extract R1 from  upper traingular in RR **/
        		LAPACKE_slacpy(LAPACK_COL_MAJOR, 'U', d, d, RR, 2*d, R1, d);
				/** library to form Q explicitly in RR **/
        		LAPACKE_sorgqr(LAPACK_COL_MAJOR, 2*d, d, d, RR, 2*d, tau);
				/** library to store Q in Q[r] **/
        		LAPACKE_slacpy(LAPACK_COL_MAJOR, 'A', 2*d, d, RR, 2*d, &Q[2*d*d*r], 2*d);
        	} 
			/** Sender **/
			else 
			{
        	    MPI_Send(R1, d*d, MPI_FLOAT, rank ^ (1<<r), 0, MPI_COMM_WORLD);
        	}
    	}
	
    }
    	
	LAPACKE_slacpy(LAPACK_COL_MAJOR, 'A', d, d, R1, d, R, d);

    for (r=log2(np)-1; r>=0; r--) {
    	if (r== 0 || !( rank & ((1<<r)-1) )) {
			/** Send **/
        	if ( !(rank & (1<<r)) ) { 
            	/** Split Q{2d,d} into Q1{d,d} and Q2{d,d} **/
				unstack(Q1, Q2, &Q[2*d*d*r], d);
				/** Send Q2 to the next processor **/
            	MPI_Send(Q2, d*d, MPI_FLOAT, rank ^ (1<<r), 0, MPI_COMM_WORLD); 
        	} 
			else {
				/** Received Q1 from the previous processor **/
            	MPI_Recv(Q1, d*d, MPI_FLOAT, rank ^ (1<<r), 0, MPI_COMM_WORLD, &status);
        	}
        	if (r>0) {
				/** perform matrix multiplication of received Q1 and existing Q block **/
            	cblas_sgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, 2*d, d, d, 1.0, &Q[2*d*d*(r-1)], 2*d, Q1, d, 0, Qtmp, 2*d);
            	LAPACKE_slacpy(LAPACK_COL_MAJOR, 'A', 2*d, d, Qtmp, 2*d, &Q[2*d*d*(r-1)], 2*d);
        	}
    	}
    }

    cblas_sgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, ln, d, d, 1.0, A, ldA, Q1, d, 0, Atmp, ln);
    LAPACKE_slacpy(LAPACK_COL_MAJOR, 'A', ln, d, Atmp, ln, A, ldA);
    free(R1);free(R2); free(RR);
    free(tau);
    free(Q1); free(Q2); free(Q);
    free(Atmp); free(Qtmp);
}	



void fnorm(int rank, float *testA, int ldtestA, float *A, int ldA, float *R, int ldR, int gn, int d, int ln)
{
	float fnorm = 0.0, fnormK = 0.0;
	float *K = (float*)malloc(sizeof(float)*gn*d);
	float *Q = (float*)malloc(sizeof(float)*gn*d);
	float *QR = (float*)malloc(sizeof(float)*gn*d);
	MPI_Gather(testA, (ln * d), MPI_FLOAT, K, (ln * d), MPI_FLOAT, 0, MPI_COMM_WORLD);
	MPI_Gather(A, (ln * d), MPI_FLOAT, Q, (ln * d), MPI_FLOAT, 0, MPI_COMM_WORLD);

	if(rank == 0)
	{
		int i,j;
		for(i=0; i<gn; ++i)
        {
            for(j=0; j<d; ++j)
            {
                float result = K[i + (j * gn)] * K[i + (j * gn)];
                fnormK = fnormK + result;
            }
        }

		cblas_sgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, gn, d, d, 1.0, Q, gn, R, d, 0.0, QR, gn);

		for(i=0; i<gn; ++i)
        {
        	for(j=0; j<d; ++j)
        	{
            	float result = QR[i + (j * gn)] * QR[i + (j * gn)];
            	fnorm = fnorm + result;
        	}
        }
		printf("The fnorm(QR)::%f, fnorm(K)::%f\n", sqrt(fnorm), sqrt(fnormK));	
	}
	free(K);free(QR);free(Q);
}

int main(int argc, char *argv[])
{
	int i,j, rank,np;
	int gn = atoi(argv[1]);
	int d = atoi(argv[2]);

	/** Initialize MPI **/
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &np);

	/** Generate a block local to a process **/
	int begin = (gn * rank)/np;
    int end = (gn * (rank + 1))/np;
    int ln = end - begin; 

	float *A =(float*)malloc(sizeof(float)*ln*d);
	float *R =(float*)malloc(sizeof(float)*d*d);
	
	/**leading dimension of the matrices**/
	int ldA = ln;
	int ldR = d;

	/**Check if the number of processors passed is power of 2**/
	if(rank == 0)
	{
		if(isPowerOfTwo(np) == 0)
		{
			printf("Please pass the number of processors in the power of 2\n");
			return 0;
		}
		if(d >= gn)
        {
            printf("The program only works for Tall - skinny matrix (n,d) where d<n");
            return 0;
        }
	}

	if (ln <= d)
    {
        if(rank == 0)
        {
            printf("ERROR: block size (ln) %d must be larger than number of columns (d) %d; reduce np %d.\n", ln, d, np);
            return 0;
        }
	}
                

	/** Generate distributed input matrix A using Gaussian random no*/
	getIpMat(rank, np, A, ldA, gn, d);
	
	/** testA is added temporarily for testing putposes only**/ 
        float *testA =(float*)malloc(sizeof(float)*ln*d);
	LAPACKE_slacpy(LAPACK_COL_MAJOR, 'A', ln, d, A, ldA, testA, ldA);
	
	/** Perform Communication avoidance QR **/
	double timestart = MPI_Wtime();
		comm_avoidance_qr(rank, np, A, ldA, R, ldR,  ln, d);
	double timeend = MPI_Wtime();


	if(rank == 0)
		printf("Execution time %f secs\n", timeend-timestart);

	/** Calculate the fnorm(A-QR). if the fnorm is less than or close to 10^6, the test was successful
 	* 	testA is the A - distributed input matrix
 	* 	Q is A after performing CAQR - distributed Q
 	* 	R is R after performing TSQR**/
	fnorm(rank, testA, ldA, A, ldA, R, ldR, gn, d, ln);

	MPI_Finalize();
	free(A);	
	return 0;
}
