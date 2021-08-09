#include <CL/cl.h>

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <random>

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <stdarg.h>
const char* TranslateOpenCLError(cl_int errorCode)
{
    switch (errorCode)
    {
    case CL_SUCCESS:                            return "CL_SUCCESS";
    case CL_DEVICE_NOT_FOUND:                   return "CL_DEVICE_NOT_FOUND";
    case CL_DEVICE_NOT_AVAILABLE:               return "CL_DEVICE_NOT_AVAILABLE";
    case CL_COMPILER_NOT_AVAILABLE:             return "CL_COMPILER_NOT_AVAILABLE";
    case CL_MEM_OBJECT_ALLOCATION_FAILURE:      return "CL_MEM_OBJECT_ALLOCATION_FAILURE";
    case CL_OUT_OF_RESOURCES:                   return "CL_OUT_OF_RESOURCES";
    case CL_OUT_OF_HOST_MEMORY:                 return "CL_OUT_OF_HOST_MEMORY";
    case CL_PROFILING_INFO_NOT_AVAILABLE:       return "CL_PROFILING_INFO_NOT_AVAILABLE";
    case CL_MEM_COPY_OVERLAP:                   return "CL_MEM_COPY_OVERLAP";
    case CL_IMAGE_FORMAT_MISMATCH:              return "CL_IMAGE_FORMAT_MISMATCH";
    case CL_IMAGE_FORMAT_NOT_SUPPORTED:         return "CL_IMAGE_FORMAT_NOT_SUPPORTED";
    case CL_BUILD_PROGRAM_FAILURE:              return "CL_BUILD_PROGRAM_FAILURE";
    case CL_MAP_FAILURE:                        return "CL_MAP_FAILURE";
    case CL_MISALIGNED_SUB_BUFFER_OFFSET:       return "CL_MISALIGNED_SUB_BUFFER_OFFSET";                          //-13
    case CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST:    return "CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST";   //-14
    case CL_COMPILE_PROGRAM_FAILURE:            return "CL_COMPILE_PROGRAM_FAILURE";                               //-15
    case CL_LINKER_NOT_AVAILABLE:               return "CL_LINKER_NOT_AVAILABLE";                                  //-16
    case CL_LINK_PROGRAM_FAILURE:               return "CL_LINK_PROGRAM_FAILURE";                                  //-17
    case CL_DEVICE_PARTITION_FAILED:            return "CL_DEVICE_PARTITION_FAILED";                               //-18
    case CL_KERNEL_ARG_INFO_NOT_AVAILABLE:      return "CL_KERNEL_ARG_INFO_NOT_AVAILABLE";                         //-19
    case CL_INVALID_VALUE:                      return "CL_INVALID_VALUE";
    case CL_INVALID_DEVICE_TYPE:                return "CL_INVALID_DEVICE_TYPE";
    case CL_INVALID_PLATFORM:                   return "CL_INVALID_PLATFORM";
    case CL_INVALID_DEVICE:                     return "CL_INVALID_DEVICE";
    case CL_INVALID_CONTEXT:                    return "CL_INVALID_CONTEXT";
    case CL_INVALID_QUEUE_PROPERTIES:           return "CL_INVALID_QUEUE_PROPERTIES";
    case CL_INVALID_COMMAND_QUEUE:              return "CL_INVALID_COMMAND_QUEUE";
    case CL_INVALID_HOST_PTR:                   return "CL_INVALID_HOST_PTR";
    case CL_INVALID_MEM_OBJECT:                 return "CL_INVALID_MEM_OBJECT";
    case CL_INVALID_IMAGE_FORMAT_DESCRIPTOR:    return "CL_INVALID_IMAGE_FORMAT_DESCRIPTOR";
    case CL_INVALID_IMAGE_SIZE:                 return "CL_INVALID_IMAGE_SIZE";
    case CL_INVALID_SAMPLER:                    return "CL_INVALID_SAMPLER";
    case CL_INVALID_BINARY:                     return "CL_INVALID_BINARY";
    case CL_INVALID_BUILD_OPTIONS:              return "CL_INVALID_BUILD_OPTIONS";
    case CL_INVALID_PROGRAM:                    return "CL_INVALID_PROGRAM";
    case CL_INVALID_PROGRAM_EXECUTABLE:         return "CL_INVALID_PROGRAM_EXECUTABLE";
    case CL_INVALID_KERNEL_NAME:                return "CL_INVALID_KERNEL_NAME";
    case CL_INVALID_KERNEL_DEFINITION:          return "CL_INVALID_KERNEL_DEFINITION";
    case CL_INVALID_KERNEL:                     return "CL_INVALID_KERNEL";
    case CL_INVALID_ARG_INDEX:                  return "CL_INVALID_ARG_INDEX";
    case CL_INVALID_ARG_VALUE:                  return "CL_INVALID_ARG_VALUE";
    case CL_INVALID_ARG_SIZE:                   return "CL_INVALID_ARG_SIZE";
    case CL_INVALID_KERNEL_ARGS:                return "CL_INVALID_KERNEL_ARGS";
    case CL_INVALID_WORK_DIMENSION:             return "CL_INVALID_WORK_DIMENSION";
    case CL_INVALID_WORK_GROUP_SIZE:            return "CL_INVALID_WORK_GROUP_SIZE";
    case CL_INVALID_WORK_ITEM_SIZE:             return "CL_INVALID_WORK_ITEM_SIZE";
    case CL_INVALID_GLOBAL_OFFSET:              return "CL_INVALID_GLOBAL_OFFSET";
    case CL_INVALID_EVENT_WAIT_LIST:            return "CL_INVALID_EVENT_WAIT_LIST";
    case CL_INVALID_EVENT:                      return "CL_INVALID_EVENT";
    case CL_INVALID_OPERATION:                  return "CL_INVALID_OPERATION";
    case CL_INVALID_GL_OBJECT:                  return "CL_INVALID_GL_OBJECT";
    case CL_INVALID_BUFFER_SIZE:                return "CL_INVALID_BUFFER_SIZE";
    case CL_INVALID_MIP_LEVEL:                  return "CL_INVALID_MIP_LEVEL";
    case CL_INVALID_GLOBAL_WORK_SIZE:           return "CL_INVALID_GLOBAL_WORK_SIZE";                           //-63
    case CL_INVALID_PROPERTY:                   return "CL_INVALID_PROPERTY";                                   //-64
    case CL_INVALID_IMAGE_DESCRIPTOR:           return "CL_INVALID_IMAGE_DESCRIPTOR";                           //-65
    case CL_INVALID_COMPILER_OPTIONS:           return "CL_INVALID_COMPILER_OPTIONS";                           //-66
    case CL_INVALID_LINKER_OPTIONS:             return "CL_INVALID_LINKER_OPTIONS";                             //-67
    case CL_INVALID_DEVICE_PARTITION_COUNT:     return "CL_INVALID_DEVICE_PARTITION_COUNT";                     //-68
//    case CL_INVALID_PIPE_SIZE:                  return "CL_INVALID_PIPE_SIZE";                                  //-69
//    case CL_INVALID_DEVICE_QUEUE:               return "CL_INVALID_DEVICE_QUEUE";                               //-70    

    default:
        return "UNKNOWN ERROR CODE";
    }
}

void LogInfo(const char* str, ...)
{
    if (str)
    {
        va_list args;
        va_start(args, str);

        vfprintf(stdout, str, args);

        va_end(args);
    }
}

void LogError(const char* str, ...)
{
    if (str)
    {
        va_list args;
        va_start(args, str);

        vfprintf(stderr, str, args);

        va_end(args);
    }
}
int main()
{
	
	int HA = 16;
	int WA = 16;
	int HB = 16;
	int WB = 16;
	
	float* A = NULL;
	float* B = NULL;
	float* C = NULL;
	
	A = (float*)malloc(sizeof(float) * HA * WA);
	B = (float*)malloc(sizeof(float) * HB * WB);

	C = (float*)malloc(sizeof(float) * HA * WB);

	std::random_device rd;

	std::mt19937 gen(rd());

	std::uniform_int_distribution<int> dis(0, 10);

	for (int i = 0; i < HA * WA; i++) {
		A[i] = (float)dis(gen)/10;
		//std::cout << A[i] << std::endl;
	}
	for (int i = 0; i < WB * HB; i++) {
		B[i] = (float)dis(gen)/10;
	}
    for (int i = 0; i < HA * WB; i++)
    {
        C[i] = 0.0f;
    }
	cl_int err;

	//step 1 : environment setting
	cl_platform_id platform;
	err = clGetPlatformIDs(1, &platform, NULL);

	cl_device_id device;
	err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, 1, &device, NULL);

	cl_context_properties cps[3] = { CL_CONTEXT_PLATFORM , (cl_context_properties)platform, 0 };
	cl_context context = clCreateContext(cps, 1, &device, NULL, NULL, &err);

	cl_command_queue cmdqueue = clCreateCommandQueue(context, device, 0, &err);

	//step 2 : declare buffer and move data
	cl_mem A_buffer = clCreateBuffer(context, CL_MEM_READ_ONLY, WA * HA * sizeof(float), NULL, &err);
	cl_mem B_buffer = clCreateBuffer(context, CL_MEM_READ_ONLY, WB * HB * sizeof(float), NULL, &err);
	cl_mem Result_buffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY, HA * WB * sizeof(float), NULL, &err);

	err = clEnqueueWriteBuffer(cmdqueue, A_buffer, CL_TRUE, 0, WA * HA * sizeof(float), (void*)A, 0, NULL, NULL);
	err = clEnqueueWriteBuffer(cmdqueue, B_buffer, CL_TRUE, 0, WB * HB * sizeof(float), (void*)B, 0, NULL, NULL);

	//step 3 : runtime Kernel compile
	size_t src_size = 0;
	std::fstream kernelFile("vecmulti.cl");
	std::string content((std::istreambuf_iterator<char>(kernelFile)), std::istreambuf_iterator<char>());
	const char* kernelCharArray = new char[content.size()];
	kernelCharArray = content.c_str();

	cl_program program = clCreateProgramWithSource(context, 1, (const char**)&kernelCharArray, NULL, &err);
    err = clBuildProgram(program, 1, &device, "", NULL, NULL);

    if (CL_SUCCESS != err)
    {
        LogError("Error1: %s.\n", TranslateOpenCLError(err));

    }
	cl_kernel kernel = clCreateKernel(program, "simpleMultiply", &err);
	clReleaseProgram(program);
    if (CL_SUCCESS != err)
    {
        LogError("Error2: %s.\n", TranslateOpenCLError(err));

    }
	//step 4 : run program
	err = clSetKernelArg(kernel, 0, sizeof(cl_mem), &Result_buffer);
	err = clSetKernelArg(kernel, 1, sizeof(cl_int), &WA);
	err = clSetKernelArg(kernel, 2, sizeof(cl_int), &HA);
	err = clSetKernelArg(kernel, 3, sizeof(cl_int), &WB);
	err = clSetKernelArg(kernel, 4, sizeof(cl_int), &HB);
	err = clSetKernelArg(kernel, 5, sizeof(cl_mem), &A_buffer);
	err = clSetKernelArg(kernel, 6, sizeof(cl_mem), &B_buffer);
	if (CL_SUCCESS != err)
	{
		LogError("Error: %s.\n", TranslateOpenCLError(err));
		
	}
	size_t globalws[2] = { HA,WB };
	size_t localws[2] = { 16,16 };

	err = clEnqueueNDRangeKernel(cmdqueue, kernel, 2, NULL, globalws, localws, 0, NULL, NULL);

	//step 5 : return the result to host
	err = clEnqueueReadBuffer(cmdqueue, Result_buffer, CL_TRUE, 0, HA * WB * sizeof(float), (void*)C, 0, NULL, NULL);

	for (int i = 0; i < HA; i++)
	{
        for(int j = 0; j < WB; j++)
		    printf("%.2f ", C[i*HA + j]);
        printf("\n");
	}
	system("pause");

}
