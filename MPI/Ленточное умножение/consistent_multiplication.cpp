void MatrixMultiplication(double *&A, double *&B, double *&C, int &Size) {
	int i, j, k;
	Flip(B, Size);
	for (i=0; i < Size; i++) {
		for (j=0; j < Size; j++) {
			C[i*Size+j] = 0;
			for (k=0; k < Size; k++)
				C[i*Size+j] += A[i*Size+k]*B[j*Size+k];
		}
	}
}