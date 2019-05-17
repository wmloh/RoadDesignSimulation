#ifndef LAYER_H
#define LAYER_H

#include <iostream>
#include <Eigen/Dense>
#include <vector>
#include <memory>

typedef std::vector<std::unique_ptr<Eigen::ArrayXXf>> Tensor;

class Layer {
protected:
	// input sources
	std::vector<Layer *> inputs;

	// dimensions of kernel
	// <kernelSize, kernelRows, kernelDepth>
	const std::tuple<int, int, int> kernelDim;

	// dimensions of output
	// <outputSize, outputDepth>
	const std::pair<int, int> outputDim;

	// summed input tensor
	Tensor inputMat;

	// computed value
	Tensor value;

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
	Tensor &get();

	// getter method for kernel dimension
	const std::tuple<int, int, int> & getKernelDim();

	// getter method for output dimension
	const std::pair<int, int> & getOutputDim();

	// print method
	virtual std::string print() = 0;

	// verbose method
	virtual void verbose() = 0;

protected:
	// calls get() method from all inputs layers and sums them
	Tensor getInputs();

	friend std::ostream &operator<<(std::ostream &, Layer &);

};

#endif