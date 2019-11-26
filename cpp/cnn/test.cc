#include <iostream>
#include <Eigen/Dense>
#include <memory>
#include <vector>


typedef std::vector<std::unique_ptr<Eigen::ArrayXXf>> Tensor;

int main() {
	auto x = std::make_unique<int>(5);
	std::cout << *x << std::endl;

	std::unique_ptr<int> &i = x;
	std::cout << *i << std::endl; 
}