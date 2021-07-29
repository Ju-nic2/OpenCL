// TODO: Add OpenCL kernel code here.

__kernel void vecadd(__global int *A, __global int *B, __global int *result)
{
	int idx = get_global_id(0);
	result[idx] = A[idx] + B[idx];
}