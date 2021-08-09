
__kernel void simpleMultiply(__global float* output, int widthA, int heightA, int widthB, int heightB, __global float *A, __global float *B)
{
	int row = get_global_id(1);
	int col = get_global_id(0);

	float sum = 0.0f;
	for(int i = 0; i <widthA; i++)
	{
		sum += A[row*widthA + i] * B[i*widthB + col];
	}

	output[row*widthB+col] = sum;
}
