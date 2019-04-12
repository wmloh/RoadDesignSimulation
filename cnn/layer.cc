#include "layer.h"

template <int size, int numKernel>
Layer<size,numKernel>::Layer(std::vector<Layer &> && inputs, std::tuple<int, int, int> outputDim) 
	:inputs{std::move(inputs)},
	 kernelDim{size, std::get<2>(inputs[0].get(0).getOutputDim()), numKernel},
	 outputDim{std::move(outputDim)}, value{}{}

template <int size, int numKernel>
Layer<size,numKernel>::~Layer() {}

template <int size, int numKernel>
const std::tuple<int, int, int> & Layer<size,numKernel>::getKernelDim() {
	return kernelDim;
}

template <int size, int numKernel>
const std::pair<int, int> & Layer<size,numKernel>::getOutputDim() {
	return outputDim;
}

template <int size, int numKernel>
Eigen::ArrayXXf Layer<size,numKernel>::getInputs() {
	Eigen::ArrayXXf mat;

	for(auto & layer : inputs) {
		mat += layer.get();
	}

	return mat;
}
