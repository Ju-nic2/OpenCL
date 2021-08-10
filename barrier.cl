__kernel void simpleKernel(__global float *a, __global float *b, __local float *l)
{
	l[get_local_id(0)] = a[get_local_id(0)];
	barrier(CLK_LOCAL_MEM_FENCE);
	unsigned int otherAddress = (get_local_id(0)+1) % get_local_size(0);
	b[get_local_id(0)] = l[get_local_id(0)] + l[otherAddress];
}