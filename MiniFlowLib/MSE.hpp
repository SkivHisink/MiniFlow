#pragma once
#include "Node.hpp"
#include <string>

class MSE final :public Node {
public:
	MSE() = delete;
	MSE(Node* Y, Node* A, std::string name) : Node({ Y, A }, "MSE-" + name) {};
	~MSE();
	void forward() override;
	void backward() override;
private:
	int m = -1;
	Value* diff = nullptr;
};