#include "kernel.h"
#include <cmath>

Kernel::Kernel(RAND_INIT randType, ACT_FNC func, int kernelSize ,int kernelRows, int kernelDepth, float alpha) :
	kernelSize{kernelSize},
	alpha{alpha} {
	W = initialize(kernelSize, kernelRows, kernelDepth, randType);
	b = Eigen::VectorXf::Random(kernelDepth);

	switch(func) {
		case ACT_FNC::RELU:
			func = std::make_unique<ReLU>();
			break;
		case ACT_FNC::SIGMOID:
			func = std::make_unique<Sigmoid>();
			break;
		case ACT_FNC::TANH:
			func = std::make_unique<Tanh>();
			break;
		case ACT_FNC::FAST_TANH:
			func = std::make_unique<FastTanh>();
			break;
	}
}

Tensor Kernel::map(const Tensor &input, int inputSize, int inputRow) const {
	Tensor output;
	int range = inputSize - kernelSize + 1; // convolution operation range

	// for each output depth
	for(int depth = 0; depth < kernelDepth; ++depth) {

		// output matrix for a certain depth
		std::unique_ptr<Eigen::ArrayXXf> mat = std::make_unique<Eigen::ArrayXXf>(Eigen::ArrayXXf::Zero(range, range));
		// weight for the corresponding depth
		Tensor &depth_weight = W.at(depth);

		// for each inputRow
		for(int row = 0; row < inputRow; ++row) {

			// for each x,y-element
			for(int x = 0; x < range; ++x) {
				for(int y = 0; y < range; ++y) {
					(*mat)(x,y) = (*func)(((*input.at(row)).block(x,y,kernelSize,kernelSize) * (*depth_weight.at(row))).sum() + b(depth));
				}
			}

		}

		output.emplace_back(std::move(mat));
	}

	return output;
}

void Kernel::update(Tensor &error, Tensor &input, int errorSize, int inputSize) {
	int range = inputSize - errorSize + 1;

	float convCost;
	float totalCost;
	const int kernelElementCount = range * range;

	for(int depth = 0; depth < kernelDepth; ++depth) {
		
		// variable to keep count of average cost
		totalCost = 0;

		// references to matrices
		std::unique_ptr<Eigen::ArrayXXf> &kernel = W.at(depth);
		std::unique_ptr<Eigen::ArrayXXf> &errorMat = error.at(depth);
		std::unique_ptr<Eigen::ArrayXXf> &inputMat = input.at(depth);

		// update loop for weights
		for(int x = 0; x < range; ++x) {
			for(int y = 0; y < range; ++y) {
				convCost = (inputMat->block(x,y, errorSize, errorSize) * errorMat).sum();
				totalCost += convCost;
				(*kernel)(x,y) -= alpha * convCost;
			}
		}

		// update for bias
		b(depth) -= alpha * (totalCost / kernelElementCount);
	}
}

std::vector<Tensor> Kernel::initialize(int kernelSize, int kernelRows, int kernelDepth, RAND_INIT randType) {
	// generally used with ReLU functions
	std::vector<Tensor> weights;

	// multiplicative factor
	float limit;

	if(randType == RAND_INIT::HE) {
		limit = std::sqrt((float) 2/(kernelSize * kernelSize));
	} else if(randType == RAND_INIT::XAVIER) {
		limit = (float) 1/std::sqrt(kernelSize);
	} else if(randType == RAND_INIT::SIMPLE) {
		limit = (float) 1;
	}

	for(int j = 0; j < kernelDepth; ++j) {
		Tensor tensor;
		for(int i = 0; i < kernelRows; ++i) {
			std::unique_ptr<Eigen::ArrayXXf> mat = std::make_unique<Eigen::ArrayXXf>(Eigen::ArrayXXf::Random(kernelSize, kernelSize));
			*mat *= limit;
			tensor.emplace_back(std::move(mat));
		}
		weights.emplace_back(std::move(tensor));
	}
	
	return weights;
}
