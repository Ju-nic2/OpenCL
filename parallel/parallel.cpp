#include <CL/cl.h>

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <random>
#include <immintrin.h>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <windows.h>
#include <stdarg.h>
#include "utils.h"


#if defined(_WIN32)
#include <windows.h>
typedef LARGE_INTEGER simpleTime;

void simpleGetTime(simpleTime* timestamp)
{
    QueryPerformanceCounter(timestamp);
}

double simpleTimeDiffMsec(simpleTime tfinish, simpleTime tstart)
{
    static LARGE_INTEGER tFreq = { 0 };

    if (!tFreq.QuadPart) QueryPerformanceFrequency(&tFreq);

    double freq = (double)tFreq.QuadPart;
    return 1000.0 * ((double)tfinish.QuadPart - (double)tstart.QuadPart) / freq;
}

float half_to_float(unsigned short in)
{
    int tmp[4] = { in,0,0,0 };
    __m128 out = _mm_cvtph_ps(*((__m128i*)tmp));

    return ((float*)&out)[0];
}

unsigned short float_to_half(float in)
{

    float tmp[4] = { in,0,0,0 };
    __m128i out = _mm_cvtps_ph(*((__m128*)tmp), 0);

    return ((unsigned short*)&out)[0];
}
#endif   // _WIN32
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

#define DATA 0
#define TASK 1

static cl_device_id device = NULL;
static cl_context context = NULL;

static cl_command_queue cmdqueue = NULL;
static cl_platform_id platform = NULL;

cl_uint dataSize = 256 * 4;

float* input1 = (float*)malloc(sizeof(float) * dataSize);
float* input2 = (float*)malloc(sizeof(float) * dataSize);
float* des = (float*)malloc(sizeof(float) * dataSize);

cl_mem input_buffer1 = NULL;
cl_mem input_buffer2 = NULL;
cl_mem output_buffer = NULL;

void init()
{
    cl_int err;
    err = clGetPlatformIDs(1, &platform, NULL);

    err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, 1, &device, NULL);
    cl_context_properties cps[3] = { CL_CONTEXT_PLATFORM , (cl_context_properties)platform, 0 };
    context = clCreateContext(cps, 1, &device, NULL, NULL, &err);
    cmdqueue = clCreateCommandQueue(context, device, 0, &err);

    input_buffer1 = clCreateBuffer(context, CL_MEM_READ_ONLY, dataSize * sizeof(float), NULL, &err);
    input_buffer2 = clCreateBuffer(context, CL_MEM_READ_ONLY, dataSize * sizeof(float), NULL, &err);
    output_buffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY, dataSize * sizeof(float), NULL, &err);

    err = clEnqueueWriteBuffer(cmdqueue, input_buffer1, CL_TRUE, 0, dataSize * sizeof(float), (void*)input1, 0, NULL, NULL);
    err = clEnqueueWriteBuffer(cmdqueue, input_buffer2, CL_TRUE, 0, dataSize * sizeof(float), (void*)input2, 0, NULL, NULL);

}
cl_program getProgram(int flag)
{
    cl_int err;
    size_t src_size = 0;
    if (flag == DATA) {
        std::fstream kernelFile("dataParallel.cl");
        std::string content((std::istreambuf_iterator<char>(kernelFile)), std::istreambuf_iterator<char>());
        const char* kernelCharArray = new char[content.size()];
        kernelCharArray = content.c_str();

        cl_program program = clCreateProgramWithSource(context, 1, (const char**)&kernelCharArray, NULL, &err);
        err = clBuildProgram(program, 1, &device, "", NULL, NULL);
        return program;
    }
    else
    {
        std::fstream kernelFile("taskParallel.cl");
        std::string content((std::istreambuf_iterator<char>(kernelFile)), std::istreambuf_iterator<char>());
        const char* kernelCharArray = new char[content.size()];
        kernelCharArray = content.c_str();
        cl_program program = clCreateProgramWithSource(context, 1, (const char**)&kernelCharArray, NULL, &err);
        err = clBuildProgram(program, 1, &device, "", NULL, NULL);
        return program;
    }
  
 
}

void runKernel(int flag)
{
    cl_int err;
    cl_program program = getProgram(flag);
    if (flag == DATA) {
        cl_kernel kernel = clCreateKernel(program, "dataparallel", &err);
        err = clSetKernelArg(kernel, 0, sizeof(cl_mem), &input_buffer1);
        err = clSetKernelArg(kernel, 1, sizeof(cl_mem), &input_buffer2);
        err = clSetKernelArg(kernel, 2, sizeof(cl_mem), &output_buffer);

        //Change the numbers. 
        size_t globalws[1] = { 256 };
        size_t localws[1] = { 1 };

       
        simpleTime tStart, tEnd;
        simpleGetTime(&tStart);
        for (int i = 0; i < 1000; i++) {
            err = clEnqueueNDRangeKernel(cmdqueue, kernel, 1, NULL, globalws, localws, 0, NULL, NULL);
           
        }
        clFinish(cmdqueue);
        simpleGetTime(&tEnd);
        const double cpu_msec = simpleTimeDiffMsec(tEnd, tStart);
        printf("Data paralle Time : %f\n", cpu_msec);
        err = clEnqueueReadBuffer(cmdqueue, output_buffer, CL_TRUE, 0, dataSize * sizeof(float), des, 0, NULL, NULL);
     
    }
    else
    {
        cl_kernel kernel[4] = { NULL, NULL, NULL, NULL };
        kernel[0] = clCreateKernel(program, "dataplus", &err);
        kernel[1] = clCreateKernel(program, "datasub", &err);
        kernel[2] = clCreateKernel(program, "datadiv", &err);
        kernel[3] = clCreateKernel(program, "datamul", &err);
        for (int i = 0; i < 4; i++)
        {
            err = clSetKernelArg(kernel[i], 0, sizeof(cl_mem), &input_buffer1);
            err = clSetKernelArg(kernel[i], 1, sizeof(cl_mem), &input_buffer2);
            err = clSetKernelArg(kernel[i], 2, sizeof(cl_mem), &output_buffer);        
        }
        simpleTime tStart, tEnd;
        simpleGetTime(&tStart);
        for (int i = 0; i < 1000; i++) {
            for (int i = 0; i < 4; i++)
            {
                err = clEnqueueTask(cmdqueue, kernel[i], 0, NULL, NULL);
               
            }
        }
        clFinish(cmdqueue);
        simpleGetTime(&tEnd);
        const double cpu_msec = simpleTimeDiffMsec(tEnd, tStart);
        printf("Task paralle Time : %f\n", cpu_msec);
        err = clEnqueueReadBuffer(cmdqueue, output_buffer, CL_TRUE, 0, dataSize * sizeof(float), des, 0, NULL, NULL);
    }
}

int main()
{

    for (int i = 0; i < 256; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            input1[i * 4 + j] = i * 4 + j;
            input2[i * 4 + j] = i * 4 + j;
            des[i * 4 + j] = 0;
        }
    }
    
    init();
    runKernel(DATA);
  
    init();
    runKernel(TASK);

    


    for (int i = 0; i < 256; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            //printf("%.2f ",des[i * 4 + j]);
        }
        //printf("\n");
    }

  
    system("pause");

}