#include <stdio.h>
#include <stdlib.h>
#include<stdarg.h>
#include <CL/cl.h>
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
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

void getDeviceInfo(cl_device_id* devices, cl_uint* numDevices_)
{
    cl_uint err;
    cl_uint numPlatforms = 0;
    err = clGetPlatformIDs(0, NULL, &numPlatforms);
    //allocate space for each platform
    cl_platform_id* platforms = NULL;
    platforms = (cl_platform_id*)malloc(numPlatforms * sizeof(cl_platform_id));
    for (int i = 0; i < numPlatforms; i++)
    {
        //get platform info
        err = clGetPlatformIDs(numPlatforms, platforms, NULL);
        //get device num
        cl_uint numDevices = 0;
        err = clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, 0, NULL, &numDevices);
        //return to main
        *numDevices_ = numDevices;
        //allocate space for each device
        devices = (cl_device_id*)malloc(numDevices * sizeof(cl_device_id));
        //get device info
        err = clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, numDevices, devices, NULL);
        //0 -> GPU  && 1 ->CPU
        for (int j = 0; j < numDevices; j++)
        {   
                size_t valueSize;
                clGetDeviceInfo(devices[j], CL_DEVICE_NAME, 0, NULL, &valueSize);
                char* value = (char*)malloc(valueSize);
                clGetDeviceInfo(devices[j], CL_DEVICE_NAME, valueSize, value, NULL);
                printf(" %s\n", value);
                free(value);
                system("pause");
        }
    }
    free(platforms);

}
int main()
{

    LARGE_INTEGER beginClock, endClock, clockFreq;
    LARGE_INTEGER tot_beginClock, tot_endClock, tot_clockFreq;

    QueryPerformanceFrequency(&tot_clockFreq);
    //for status check
    cl_int err = CL_SUCCESS;

    //read OpenCL Kernel
        
    //**fix program build Error ** 
    //remove ReadSourceFromFile function and change to this line 
    size_t src_size = 0;
    std::fstream kernelFile("kernel.cl");
    std::string content((std::istreambuf_iterator<char>(kernelFile)),std::istreambuf_iterator<char>());
    const char* kernelCharArray = new char[content.size()];
    kernelCharArray = content.c_str();
    
    if (CL_SUCCESS != err)
    {
        fprintf(stderr, "Error: ReadSourceFromFile returned %s.\n", TranslateOpenCLError(err));
    }
    QueryPerformanceCounter(&tot_beginClock);
    //host data
    int* A = NULL;
    int* B = NULL;
    int* result = NULL;

    const int elements = 100000000;
    size_t datasize = sizeof(int) * elements;

    A = (int*)malloc(datasize);
    B = (int*)malloc(datasize);
    result = (int*)malloc(datasize);

    for (int i = 0; i < elements; i++)
    {
        A[i] = i;
        B[i] = i;

    }

    // get Device info
    cl_device_id* devices = NULL;
    cl_uint numDevices;
    getDeviceInfo(devices, &numDevices);
    
    //create context and connect to device
    cl_context context;
    context = clCreateContext(NULL, numDevices, devices, NULL, NULL, &err);
    
    //create command queue and connect to device
    cl_command_queue cmdQueue;
    cmdQueue = clCreateCommandQueue(context, devices[0], 0, &err);
    
    //create buffer for host arraies
    cl_mem bufA;
    bufA = clCreateBuffer(context, CL_MEM_READ_ONLY, datasize, NULL, &err);

    cl_mem bufB;
    bufB = clCreateBuffer(context, CL_MEM_READ_ONLY, datasize, NULL, &err);

    cl_mem bufR;
    bufR = clCreateBuffer(context, CL_MEM_WRITE_ONLY, datasize, NULL, &err);
    
    //write array  to Buffer
    err = clEnqueueWriteBuffer(cmdQueue, bufA, CL_FALSE, 0, datasize, A, 0, NULL, NULL);
    err = clEnqueueWriteBuffer(cmdQueue, bufB, CL_FALSE, 0, datasize, B, 0, NULL, NULL);
    
    //create program
    cl_program program = clCreateProgramWithSource(context, 1, (const char**)&kernelCharArray, NULL, &err);
    
    //compile program for device
    err = clBuildProgram(program, 1, devices, "", NULL, NULL);
    if (err == CL_BUILD_PROGRAM_FAILURE)
    {
        size_t log_size = 0;
        clGetProgramBuildInfo(program, *devices, CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);

        std::vector<char> build_log(log_size);
        clGetProgramBuildInfo(program, *devices, CL_PROGRAM_BUILD_LOG, log_size, &build_log[0], NULL);

        LogError("Error happened during the build of OpenCL program.\nBuild log:%s", &build_log[0]);
    }
    fprintf(stdout, "Error: returned %s.\n", TranslateOpenCLError(err));
    //create vector add kernel
    cl_kernel kernel;
    kernel = clCreateKernel(program, "vecadd", &err);

    //connect buffers with kernel
    err = clSetKernelArg(kernel, 0, sizeof(cl_mem), &bufA);
    err = clSetKernelArg(kernel, 1, sizeof(cl_mem), &bufB);
    err = clSetKernelArg(kernel, 2, sizeof(cl_mem), &bufR);

    //for excecute , define NDRange Index size (global work size)
    size_t globalWorkSize[1];
    globalWorkSize[0] = elements;

    err = clEnqueueNDRangeKernel(cmdQueue, kernel, 1, NULL, globalWorkSize, NULL, 0, NULL, NULL);

    //read data from device output buffer to host output buffer
    clEnqueueReadBuffer(cmdQueue, bufR, CL_TRUE, 0, datasize, result, 0, NULL, NULL);

    //print output
    for (long long i = 0; i < elements; i++)
    {
        //printf("%d ", result[i]);
    }
    printf("\n");
    QueryPerformanceCounter(&tot_endClock);
    double totalTime = (double)(tot_endClock.QuadPart - tot_beginClock.QuadPart) / tot_clockFreq.QuadPart;
    printf("Total processing Time : %f ms\n", totalTime * 1000);
    //delete OpenCl resource
    clReleaseKernel(kernel);
    clReleaseProgram(program);
    clReleaseCommandQueue(cmdQueue);
    clReleaseMemObject(bufA);
    clReleaseMemObject(bufB);
    clReleaseMemObject(bufR);
    clReleaseContext(context);

    //delete Host resource
    free(A);
    free(B);
    free(result);
    free(devices);
    return 0;
}

