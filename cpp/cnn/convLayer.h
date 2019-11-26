#ifndef CONVLAYER_H
#define CONVLAYER_H

#include "layer.h"
#include "kernel.h"


class ConvLayer : public Layer {

	// Kernel object
	Kernel kern;

	// weights of kernel
	Tensor W;

	// bias of kernel
	Eigen::ArrayXf b;

	// padding size
	int padding;

	// frozen weights and biases
	bool frozen;

public:
	ConvLayer(std::vector<Layer *> &&, const int, const int, const int padding);
	~ConvLayer();

	void compute() override;

	std::string print() override;

	void verbose() override;


};

#endif