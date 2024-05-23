#pragma once
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>


#include "RgaUtils.h"
#include "rknn_api.h"

class Inference
{
public:
	Inference();

	bool LoadModel(const char* modelfile);

	~Inference();

protected:
	rknn_context ctx;
	rknn_input_output_num io_num;
};