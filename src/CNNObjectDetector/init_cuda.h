/*
*	Copyright (c) 2018, Ilya Kalinovskiy
*	All rights reserved.
*
*	This is an implementation of the algorithm described in the following paper:
*		I.A. Kalinovskiy, V.G. Spitsyn,
*		Compact Convolutional Neural Network Cascade for Face Detection,
*		http://arxiv.org/abs/1508.01292.
*
*	Redistribution and use of this program as source code or in binary form, with or without modifications, are permitted provided that the following conditions are met:
*		1. Redistributions may not be sold, nor may they be used in a commercial product or activity without prior permission from the copyright holder (contact him at kua_21@mail.ru).
*		2. Redistributions may not be used for military purposes.
*		3. Any published work which utilizes this program shall include the reference to the paper available at http://arxiv.org/abs/1508.01292
*		4. Redistributions must retain the above copyright notice and the reference to the algorithm on which the implementation is based on, this list of conditions and the following disclaimer.
*
*	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
*	IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/


#pragma once

#include "config.h"

#ifdef USE_CUDA
#	include <cuda_runtime.h>
#endif


//================================================================================================================================================


namespace NeuralNetworksLib
{
#ifdef USE_CUDA

	namespace CUDA
	{
		#ifdef _DEBUG
			#define cuERR(func)																													\
			do {																																\
				cudaError_t error = func;																										\
				if (error != 0)															  														\
				{																																\
					printf("CUDA Error: line %d of file \"%s\" <%s> = %s\n", __LINE__, __FILE__, __FUNCTION__, cudaGetErrorString(error));		\
				}																																\
			} while (false)
		#else
			#define cuERR(func) func
		#endif

		int InfoDevice();
		int InitDevice(int device_id, bool info = false);
		void ReleaseDevice();
	}

#endif
}