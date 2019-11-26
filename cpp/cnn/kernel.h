#ifndef KERNEL_H
#define KERNEL_H

#include "layer.h"
#include "actFunctor.h"

// Random initialization options
enum class RAND_INIT{SIMPLE, HE, XAVIER};

// Activation function options
enum class ACT_FNC{RELU, SIGMOID, TANH, FAST_TANH};

class Kernel {

	// kernel size
	int kernelSize;

	// 4 dimensional weights
	std::vector<Tensor> W;

	// vector of biases
	Eigen::VectorXf b;

	// activation function
	std::unique_ptr<ActFunctor> func;

	// learning rate
	float alpha;

public:
	Kernel(RAND_INIT, ACT_FNC, int, int, int, float);
	~Kernel();

	// maps the input using weights and biases
	Tensor map(const Tensor &, int, int) const;

	// performs backpropagation of weights and biases
	// TODO: Currently only support basic gradient descent
	void update(Tensor &);

protected:
	// random initializer methods for weights
	std::vector<Tensor> initialize(int, int, int, RAND_INIT)
};

#endif