#define MATRIX_X 8192
#define MATRIX_Y 8192
#define LOCAL_X 16
#define LOCAL_Y 16

__kernel void nonOptimized(__global float* src1, __global float* des)
{

	int dx[9] = {-1, 0, -1,-1, 0, 1,-1, 0, 1};
	int dy[9] = {-1,-1, -1, 0, 0, 0, 1, 1, 1};

	int global_x = get_global_id(0);
	int global_y = get_global_id(1);
	
	float now = src1[global_x + MATRIX_Y*global_y];

	int count = 0;
	for(int i = 0; i < 9; i++)
	{
		int neigbor_x = global_x + dx[i];
		int neigbor_y = global_y + dy[i];
		if(neigbor_x >= 0 && neigbor_x < MATRIX_X && neigbor_y >= 0 && neigbor_y < MATRIX_Y)
		{
			float neigbor = src1[neigbor_x + MATRIX_Y*neigbor_y];
			if(neigbor == 1){
				count+=1;
			}
		}
	}

	if(now == 1)
	{
		count--;
		if(count >= 3 && count <= 6){
			des[global_x + MATRIX_Y*global_y] = 1;
		}
		else{ 
			des[global_x + MATRIX_Y*global_y] = 0;
		}
	}
	else{
		if(count == 4) {
			des[global_x + MATRIX_Y*global_y] = 1;
		}else{
			des[global_x + MATRIX_Y*global_y] = 0;
		}
	}

	

}

__kernel void useCaching(__global float* src1,__local float* cache, __global float* des)
{
	
	int dx[9] = {-1, 0, -1,-1, 0, 1,-1, 0, 1};
	int dy[9] = {-1,-1, -1, 0, 0, 0, 1, 1, 1};

	int global_x = get_global_id(0);
	int global_y = get_global_id(1);

	int local_x = get_local_id(0);
	int local_y = get_local_id(1);
	// caching data to local mem
	cache[local_x + local_y*LOCAL_Y] = src1[global_x + global_y*MATRIX_Y];
	barrier(CLK_LOCAL_MEM_FENCE);

	//access to local memeory
	float now = cache[local_x + local_y*LOCAL_Y];
	int count = 0;
	for(int i = 0; i < 9; i++)
	{
		int neigbor_x = local_x + dx[i];
		int neigbor_y = local_y + dy[i];
		if(neigbor_x >= 0 && neigbor_x < LOCAL_X && neigbor_y >= 0 && neigbor_y < LOCAL_Y)
		{
			float neigbor = cache[neigbor_x + LOCAL_X*neigbor_y];
			if(neigbor == 1){
				count+=1;
			}
		}
	}

	//write to global mem
	if(now == 1)
	{
		count--;
		if(count >= 3 && count <= 6){
			des[global_x + MATRIX_Y*global_y] = 1;
		}
		else{ 
			des[global_x + MATRIX_Y*global_y] = 0;
		}
	}
	else{
		if(count == 4) {
			des[global_x + MATRIX_Y*global_y] = 1;
		}else{
			des[global_x + MATRIX_Y*global_y] = 0;
		}
	}
	
	
}