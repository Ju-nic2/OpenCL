#include <CL/cl.h>

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include<stdarg.h>
using namespace std;

int main()
{
	int W = 1024;
	int H = 1024;
	int *src_image = NULL;
	int* des_image = NULL;
	int datasize = W * H;
	src_image = (int*)malloc(sizeof(int) * datasize);
	des_image = (int*)malloc(sizeof(int) * datasize);
	for (int i = 0; i < datasize; i++)
	{
		src_image[i] = i;
		des_image[i] = 0;
	}
	cl_int err;

	//step 1 : environment setting
	cl_platform_id platform;
	err = clGetPlatformIDs(1, &platform, NULL);

	cl_device_id device;
	err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, 1, &device, NULL);

	cl_context_properties cps[3] = { CL_CONTEXT_PLATFORM , (cl_context_properties)platform, 0};
	cl_context context = clCreateContext(cps, 1, &device, NULL, NULL, &err);

	cl_command_queue cmdqueue = clCreateCommandQueue(context, device, 0, &err);

	//step 2 : declare buffer and move data
	cl_mem src_image_buffer = clCreateBuffer(context, CL_MEM_READ_ONLY, W * H , NULL, &err);
	cl_mem des_image_buffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY, W * H , NULL, &err);

	err = clEnqueueWriteBuffer(cmdqueue, src_image_buffer, CL_FALSE, 0, W * H, src_image, 0, NULL, NULL);
	
	//step 3 : runtime Kernel compile
	size_t src_size = 0;
	std::fstream kernelFile("img_rotate.cl");
	std::string content((std::istreambuf_iterator<char>(kernelFile)), std::istreambuf_iterator<char>());
	const char* kernelCharArray = new char[content.size()];
	kernelCharArray = content.c_str();

	cl_program program = clCreateProgramWithSource(context, 1, (const char**)&kernelCharArray, NULL, &err);
	err = clBuildProgram(program, 1, &device, "", NULL, NULL);
	cl_kernel kernel = clCreateKernel(program, "img_rotate", &err);

	//step 4 : run program
	float cos_theta = cos(30);
	float sin_theta = sin(30);

	err = clSetKernelArg(kernel, 0, sizeof(cl_mem), &des_image_buffer);
	err = clSetKernelArg(kernel, 1, sizeof(cl_mem), &src_image_buffer);
	err = clSetKernelArg(kernel, 2, sizeof(cl_int), &W);
	err = clSetKernelArg(kernel, 3, sizeof(cl_int), &H);
	err = clSetKernelArg(kernel, 4, sizeof(cl_float), &sin_theta);
	err = clSetKernelArg(kernel, 5, sizeof(cl_float), &cos_theta);

	size_t globalws[2] = { W,H };
	size_t localws[2] = { 16,16 };

	err = clEnqueueNDRangeKernel(cmdqueue, kernel, 2, NULL, globalws, localws, 0, NULL, NULL);

	//step 5 : return the result to host
	err = clEnqueueReadBuffer(cmdqueue, des_image_buffer, CL_TRUE, 0, W * H , des_image, 0, NULL , NULL);

	for (int i = 0; i < datasize; i++)
	{
		printf("%d ", des_image[i]);
	}
	system("pause");

}