__kernel void dataplus(__global float* src1,__global float* src2,__global float* des)
{
	int base = 0;
	
	for(int i = 0; i < 256*4; i+=4)
	{
		des[base+i] = src1[base+i]   + src2[base+i];
	}
}

__kernel void datasub(__global float* src1,__global float* src2,__global float* des)
{
	int base = 1;
	for(int i = 0; i < 256*4; i+=4)
	{
		des[base+i]   = src1[base+i]   - src2[base+i];
	}
}

__kernel void datadiv(__global float* src1,__global float* src2,__global float* des)
{
	int base = 2;
	for(int i = 0; i < 256*4; i+=4)
	{
		des[base+i]   = src1[base+i]   / src2[base+i];
	}
}

__kernel void datamul(__global float* src1,__global float* src2,__global float* des)
{
	int base = 3;
	for(int i = 0; i < 256*4; i+=4)
	{
		des[base+i]   = src1[base+i]   * src2[base+i];
	}
}
