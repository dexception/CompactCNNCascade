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
#include "image.h"

#include <vector>
#include <string>


using namespace NeuralNetworksLib::SIMD;


//================================================================================================================================================


namespace NeuralNetworksLib
{
#ifdef USE_CNTK_MODELS

	class CNNModelsConverter
	{
	private:
		struct Layer_buffer
		{
			int map_count = 0;

			Size2d conv_buffer_size;
			std::vector<Array_32f> conv_buffer;

			Size2d pool_buffer_size;
			std::vector<Array_32f> pool_buffer;

			Size2d sum_buffer_size;
			std::vector<Array_32f> sum_buffer;
		};
		struct Layer_filter
		{
			Size2d ROI;

			Size2d size;
			std::vector<Array_32f> kernels;
		};
		struct CNN
		{
			Size min_image_size;

			int layer_count = 0;
			std::vector<Layer_buffer> layer_buffer;
			Array_32f_ref pool3_buffer_ref;

			Size2d hl_buffer_size;
			std::vector<Array_32f> hl_buffer;

			Size2d ol_buffer_size;
			Array_32f ol_buffer;

			Layer_filter conv_l1;
			Layer_filter conv_l2;
			Layer_filter conv_l3;

			std::vector<Array_32f> conv_bias;
			std::vector<Array_32f> leakyReLU_w1;
			std::vector<Array_32f> leakyReLU_w2;

			std::vector<Array_32f> bn_weight;
			std::vector<Array_32f> bn_bias;

			int snn_hl_size = 0;
			int snn_connect_count = 0;
			int hl_scale = 0;
			std::vector<Array_32f> snn_hl_weight;
			Array_32f snn_hl_bias;
			Array_32f snn_hl_tanh_w;

			Array_32f snn_hl_bn_weight;
			Array_32f snn_hl_bn_bias;

			int snn_ol_neuron_count = 0;
			std::vector<Array_32f> snn_ol_weight;
			Array_32f snn_ol_bias;
			float snn_ol_tanh_w = 0.f;

			float af_scale = 0.f;
			bool max_pool = false;
			bool snn_full_connect = false;
		};

		CNN cnn;

		void Clear();
		void ParserDump(std::vector<float>& param, std::vector<std::string>& dump, std::string l_name, std::string p_name, int idx = -1);
		
	public:
		CNNModelsConverter() { }
		~CNNModelsConverter() { Clear(); }

		inline bool isEmpty() const { return cnn.min_image_size.width == 0 || cnn.min_image_size.height == 0; }

		void LoadCNTKModel(std::string file_name, bool preprocessing = true);
		void SaveToBinaryFile(std::string file_name, void* hGrd = 0);
	};

#endif
}