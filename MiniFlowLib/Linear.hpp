#pragma once
#include "Node.hpp"
class Linear final : public Node {
public:
	Linear() = delete;
	Linear(Node* X, Node* W, Node* b, std::string name) :Node({ X, W, b }, "Linear-" + name) {};
	void forward() override;
	void backward() override;
};
