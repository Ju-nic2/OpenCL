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


//create program from binary file
cl_program createProgramBinary(cl_context context, cl_device_id device, const char* fileName)
{
	FILE* fp;
	fopen(fileName, "rb");
	if (fp == NULL) return NULL;
	
	//get file size 
	size_t binarySize;
	fseek(fp, 0, SEEK_END);
	binarySize = ftell(fp);

	//read binary file form disk
	unsigned char* programBinary = (unsigned char*)malloc(sizeof(unsigned char) * binarySize);
	fseek(fp, 0, SEEK_SET);
	fread(programBinary, binarySize, 1, fp);
	fclose(fp);

	cl_int err;
	cl_int binaryStatus;
	cl_program program;

	program = clCreateProgramWithBinary(context, 1, &device, &binarySize, (unsigned char**)&programBinary, &binaryStatus, &err);
	
	//** 'build program' makes program complete execution file.**
	err = clBuildProgram(program, 1,&device, "", NULL, NULL);
	return program;
}