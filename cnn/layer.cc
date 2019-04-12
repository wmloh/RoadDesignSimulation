#include "layer.h"

Layer::Layer(std::vector<Layer *> && inputs, std::pair<int, int> outputDim, int size, int numKernel) 
	:inputs{std::move(inputs)},
	 kernelDim{size, inputs.at(0)->getOutputDim().second, numKernel},
	 outputDim{outputDim} {}

Layer::~Layer() {}

const std::tuple<int, int, int> & Layer::getKernelDim() {
	return kernelDim;
}

const std::pair<int, int> & Layer::getOutputDim() {
	return outputDim;
}

Eigen::ArrayXXf &Layer::get() {
	return value;
}

Eigen::ArrayXXf Layer::getInputs() {
	Eigen::ArrayXXf mat;

	for(auto & layer : inputs) {
		mat += layer->get();
	}

	return mat;
}
