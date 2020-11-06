#pragma once
#include "Node.hpp"

class Sigmoid final :public Node {
public:
	Sigmoid() = delete;
	Sigmoid(Node* input, std::string name) :Node({ input }, "Sigmoid-" + name) {};
	void forward() override;
	void backward() override;
};
