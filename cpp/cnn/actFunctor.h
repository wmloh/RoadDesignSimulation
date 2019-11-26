#ifndef ACTFUNCTOR_H
#define ACTFUNCTOR_H

#include <iostream>

class ActFunctor {

public:
	ActFunctor();
	~ActFunctor();

	// function call
	virtual float operator()(float) = 0;

	// computes gradient
	virtual float grad(float) = 0;
};

class ReLU : public ActFunctor {

public:
	ReLU();
	~ReLU();

	float operator()(float) override;

	float grad(float) override;
};

class Sigmoid : public ActFunctor {

public:
	Sigmoid();
	~Sigmoid();

	float operator()(float) override;

	float grad(float) override;
};

class Tanh : public ActFunctor {

public:
	Tanh();
	~Tanh();

	float operator()(float) override;

	float grad(float) override;
};


class FastTanh : public ActFunctor {

public:
	FastTanh();
	~FastTanh();

	float operator()(float) override;

	float grad(float) override; 
};

#endif