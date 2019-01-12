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

#include "image.h"
#include "image_cl.h"

#include <fstream>
#include <string>


//================================================================================================================================================


namespace NeuralNetworksLib
{
#if defined(USE_CL) && defined(USE_CNTK_MODELS)

	namespace CL
	{
		class CNNPP
		{
		public:
			static void create_cl_program(cl_device_id _device, cl_context _context);
			static void destroy_cl_program();

			static void set_src_surf(Image_32f* src, int layer, int surface);
			static void set_dst_surf(Image_32f* dst, int layer, int surface);

			static void set_kernel_on_device(cl_context _context, cl_command_queue _queue, float* kernel, int size, int layer, int surface);
			static void set_conv_b_on_device(cl_context _context, cl_command_queue _queue, float* conv_b, int layer, int surface);
			static void set_lrelu_w1_on_device(cl_context _context, cl_command_queue _queue, float* lrelu_w1, int layer, int surface);
			static void set_lrelu_w2_on_device(cl_context _context, cl_command_queue _queue, float* lrelu_w2, int layer, int surface);
			//static void set_bn_w_on_device(cl_context _context, cl_command_queue _queue, float* bn_w, int layer, int surface);
			static void set_bn_b_on_device(cl_context _context, cl_command_queue _queue, float* bn_b, int layer, int surface);
			static void set_hl_w_on_device(cl_context _context, cl_command_queue _queue, float* hl_w, int surface);
			static void set_hl_b_on_device(cl_context _context, cl_command_queue _queue, float* hl_b, int surface);
			static void set_hl_tanh_w_on_device(cl_context _context, cl_command_queue _queue, float* hl_tanh_w, int surface);
			static void set_hl_bn_w_on_device(cl_context _context, cl_command_queue _queue, float* hl_bn_w, int surface);
			static void set_hl_bn_b_on_device(cl_context _context, cl_command_queue _queue, float* hl_bn_b, int surface);
			static void set_ol_w_on_device(cl_context _context, cl_command_queue _queue, float* ol_w, int surface);
			static void set_ol_b_on_device(cl_context _context, cl_command_queue _queue, float* ol_b, int surface);
			static void set_ol_tanh_w_on_device(cl_context _context, cl_command_queue _queue, float* ol_tanh_w);
			static void set_ol_scale_on_device(cl_context _context, cl_command_queue _queue, float* ol_scale);
			static void set_index_output_on_device(cl_context _context, cl_command_queue _queue, int index_output);

			static void release_cl_buffers();

			static void run_L1(Size2d ROI, Size block_size, cl_command_queue _queue);
			static void run_L2(Size2d ROI, Size block_size, cl_command_queue _queue);
			static void run_L3(Size2d ROI, Size block_size, cl_command_queue _queue);
			static void run_HL(Size2d ROI, Size block_size, cl_command_queue _queue);
		};
	}

#endif
}