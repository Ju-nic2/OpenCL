__kernel void simple(__global float *a, __global float *b)
{
	int address = get_global_id(0) + get_global_id(1)*get_global_size(0);
	// address = location in NDRange 1 demension + location In 2 demension * work_item_size in 1 demension
	b[address] = a[address]*2; 
}