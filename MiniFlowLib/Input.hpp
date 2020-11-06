#pragma once
#include "Node.hpp"


class Input final : public Node {
public:
	Input() = delete;
	Input(Value* val, std::string name) : Node({}, "Input-" + name) {
		this->value = val;
	}
	Input(std::string name) : Node({}, "Input-" + name) {};
	void forward() override;
	void backward() override;
};