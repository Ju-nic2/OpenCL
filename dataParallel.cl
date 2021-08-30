__kernel void dataparallel(__global float* src1,__global float* src2,__global float* des)
{
	int address = 4*get_global_id(0);
	des[address]   = src1[address]   + src2[address];
	des[address+1] = src1[address+1] - src2[address+1];
	des[address+2] = src1[address+2] / src2[address+2];
	des[address+3] = src1[address+3] * src2[address+3];
}