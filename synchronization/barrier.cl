__kernel void simple(__global  int *a, __global int *b, __local int *r)
{

	//** __local is local memory space 
	//it shared in same work-group 
	r[get_local_id(0)] = a[get_global_id(0)];
	//synchronization work-items in work-group, No work group <-> work group 
	//must wait, untill all work-items In same work-group arrive barrier.
	barrier(CLK_LOCAL_MEM_FENCE);

	unsigned int otherAddress = (get_local_id(0) + 1) % get_local_size(0);
	b[get_global_id(0)] = r[get_local_id(0)] - r[otherAddress];
}