#include "layer.h"

Layer::Layer(std::vector<Layer *> && inputs, std::pair<int, int> outputDim, int size, int numKernel) 
	:inputs{std::move(inputs)},
	 kernelDim{size, inputs.at(0)->getOutputDim().second, numKernel},
	 outputDim{outputDim},
	 intputMat{},
	 value{}
	 {}

Layer::~Layer() {}

const std::tuple<int, int, int> & Layer::getKernelDim() {
	return kernelDim;
}

const std::pair<int, int> & Layer::getOutputDim() {
	return outputDim;
}

Tensor &Layer::get() {
	return value;
}

Tensor Layer::getInputs() {
	Tensor tensor;

	// gets the output dimensions of the inputs (assumes the first layer is representative)
	int outputSize, outputDepth;
	std::tie(outputSize, outputDepth) = inputs.at(0)->outputDim;

	for(int depth = 0; depth < outputDepth; ++depth) {
		// constructs a unique_ptr to hold the temporary results
		std::unique_ptr<Eigen::ArrayXXf> mat = std::make_unique<Eigen::ArrayXXf>(Eigen::ArrayXXf::Zero(outputSize, outputSize));
		for(auto & layer : inputs) {
			*mat += *(layer->get().at(depth));
		}

		tensor.emplace_back(std::move(mat));
	}

	tensor.shrink_to_fit();

	return tensor;
}

std::ostream &operator<<(std::ostream &out, Layer &layer) {
	out << layer.print();
	return out;
}