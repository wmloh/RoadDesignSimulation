#include "convLayer.h"

ConvLayer::ConvLayer(std::vector<Layer *> &&inputs,
	const int kernelSize, const int numKernel, const int padding) :

	Layer{std::move(inputs), 
		std::make_pair(inputs.at(0)->getOutputDim().first - kernelSize + 1 + 2 * padding, numKernel),
	 	kernelSize, numKernel},
		W{}, b{}, padding{padding}, frozen{false} {}

ConvLayer::~ConvLayer() {}

void ConvLayer::compute() {
	const int outputDim = std::get<0>(kernelDim);
	const int inputDim = inputs.at(0)->getOutputDim().first;
	const int newDim = inputDim + 2 * padding;

	// tensor to store output
	Tensor outputMat;

	// adds padding if needed
	if(padding != 0) {
		inputMat = Eigen::ArrayXXf::Zero(newDim, newDim);
		inputMat.block(inputDim, inputDim, padding, padding) = getInputs();
	} else {
		inputMat = getInputs();
	}

	int kernelSize = std::get<0>(kernelDim);
	const int range = newDim - kernelSize + 1;


	for(int x = 0; x < range; ++x) {
		for(int y = 0; y < range; ++y) {
			auto conv = inputMat.block(kernelSize,kernelSize, x, y) * W;
			outputMat(x,y) = conv.sum() + b(x); // indexing vector might affect optimization
		}
	}

	value = outputMat;

}

void ConvLayer::print() {

}

void ConvLayer::verbose() {

}
