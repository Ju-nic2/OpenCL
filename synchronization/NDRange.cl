__kernel void simple(__global float *a, __global float *b)
{
	int address = get_global_id(0) + get_global_id(1)*get_global_size(0);
	// address = location in NDRange 1 demension + location In 2 demension * work_item_size in 1 demension
	b[address] = a[address]*2; 
}

// ** NDRange functions.
// 1. uint get_work_dim() : returns dimension

// 2. uint get_global_size(uint dimension) : return work-items's global size in demension 
// ex) in N*N range N/2 work-group -> return N

// 3. uint get_global_id(uint dimension) : return work-item's global index in demension
// ex) in N*N rnage , (x,y) work-item -> return x*y

// 4. uint get_local_size(uint dimension) : return work-group size in demension
// ex) if N*N range has 4 work-group which size is N/2, return N/2

// 5. uint get_local_id(uint dimension) : return local index to use offset which means how far from start of work-group in demension. 
// ex)  return work-item's x points in "work-group", NOT whole NDRange.

// 6. uint get_num_groups(uint dimension) : return work-group Nums in demension
// ex ) if N*N range it return N/work-group-size

// 7. uint get_num_groups(uint dimension) : return work-group's index in demension
// ex)  if N*N range it return  first work-item's global_id(index) / size of work-group.