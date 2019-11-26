#include "actFunctor.h"
#include <algorithm>
#include <cmath>
#include <math.h>

ActFunctor::ActFunctor() {}
ActFunctor::~ActFunctor() {}

ReLU::ReLU() : ActFunctor{} {}
Sigmoid::Sigmoid() : ActFunctor{} {}
Tanh::Tanh() : ActFunctor{} {}
FastTanh::FastTanh() {}

ReLU::~ReLU() : ActFunctor{} {}
Sigmoid::~Sigmoid() : ActFunctor{} {}
Tanh::~Tanh() : ActFunctor{} {}
FastTanh::~FastTanh() {}

float ReLU::operator()(float x) {
	return std::max(0, x);
}

float ReLU::grad(float x) {
	return 1 ? x >= 0 : 0;
}

float Sigmoid::operator()(float x) {
	return ((float) 1)/(1 + std::exp(x));
}

float Sigmoid::grad(float x) {
	float val = operator(x);
	return val * (1 - val);
}

float Tanh::operator()(float x) {
	return tanh(x);
}

float Tanh::grad(float x) {
	return 1 - pow(tanh(x),2);
}

float FastTanh::operator()(float x) {
	return x / (1 + fabs(x));
}

float FastTanh::grad(float x) {
	return ((float) 1) / (1 + pow(fabs(x)), 2);
}