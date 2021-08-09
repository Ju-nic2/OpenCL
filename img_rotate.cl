

__kernel void img_rotate(__global float* dest_data, __global float* src_data, int W, int H, float sinTheta, float cosTheta)
{
	const int ix = get_global_id(0);
	const int iy = get_global_id(1);

	float x0 = W/2.0f;
	float y0 = H/2.0f;

	float xoff = ix - x0;
	float yoff = iy - y0;

	int xpos = (int)(xoff*cosTheta + yoff*sinTheta + x0);
	int ypos = (int)(yoff*cosTheta - xoff*sinTheta + y0);

	if( ((int)xpos >= 0) && ((int)xpos < W) && ((int)ypos >= 0) && ((int)ypos < H) )
	{
		dest_data[iy*W+ix] = src_data[ypos*W+xpos];
	}

}