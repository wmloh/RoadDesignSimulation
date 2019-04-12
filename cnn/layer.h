#ifndef LAYER_H
#define LAYER_H

#include <iostream>
#include <Eigen/Dense>
#include <vector>
#include <tuple>

class Layer {
// size      - kernel dimension
// numKernel - number of layer
protected:
	// input sources
	std::vector<Layer *> inputs;

	// dimensions of kernel
	const std::tuple<int, int, int> kernelDim;

	// dimensions of output
	const std::pair<int, int> outputDim;

	// computed value
	Eigen::ArrayXXf value;

public:
	Layer(std::vector<Layer *> &&, std::pair<int, int>, int, int);
	~Layer();

	// performs operation on input
	virtual void compute() = 0;

	// performs backpropagation and sends error back
	virtual void update() = 0;

	// performs backpropagation and sends error back recursively
	virtual void updateRecursive() = 0;

	// gets computed output value
	Eigen::ArrayXXf &get();

	// getter method for kernel dimension
	const std::tuple<int, int, int> & getKernelDim();

	// getter method for output dimension
	const std::pair<int, int> & getOutputDim();

	// print method
	virtual void print() = 0;

	// verbose method
	virtual void verbose() = 0;

protected:
	// calls get() method from all inputs layers and sums them
	Eigen::ArrayXXf getInputs();

};

#endif