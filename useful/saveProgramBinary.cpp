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


//Saving binary files for a specific device (fileName - device)
bool SaveProgramBinary(cl_program program, cl_device_id device, const char* fileName)
{
	cl_uint numDevice = 0;
	cl_int err;
	//get device's num associated program
	err = clGetProgramInfo(program, CL_PROGRAM_NUM_DEVICES, sizeof(cl_uint), &numDevice, NULL);

	//get all device associated program
	cl_device_id* devices = (cl_device_id*)malloc(sizeof(cl_device_id) * numDevice);
	err = clGetProgramInfo(program, CL_PROGRAM_DEVICES, sizeof(cl_device_id)*numDevice, devices, NULL);

	//get size of each program
	size_t* programBinarySIze = (size_t*)malloc(sizeof(size_t) * numDevice);
	err = clGetProgramInfo(program, CL_PROGRAM_BINARY_SIZES, sizeof(size_t) * numDevice, programBinarySIze, NULL);

	//get binary file of each program
	unsigned char** programBinaries = (unsigned char**)malloc(sizeof(unsigned char*) * numDevice);
	for (cl_uint i = 0; i < numDevice; i++)
	{
		programBinaries[i] = (unsigned char*)malloc(sizeof(unsigned char) * programBinarySIze[i]);
	}
	err = clGetProgramInfo(program, CL_PROGRAM_BINARIES, sizeof(unsigned char*) * numDevice, programBinaries, NULL);

	//save binary file for a specific device
	for (cl_uint i = 0; i < numDevice; i++)
	{
		if (devices[i] == device) {
			FILE* fp = fopen(fileName, "wb");
			fwrite(programBinaries[i], programBinarySIze[i], 1, fp);
			fclose(fp);
			break;
		}
	}

	//clean up memories
	free(devices);
	free(programBinarySIze);
	for (cl_uint i = 0; i < numDevice; i++)
	{	
		free(programBinaries[i]);
	}
	free(programBinaries);
	return true;
}
