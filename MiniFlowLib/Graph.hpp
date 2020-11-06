#pragma once
#include "Input.hpp"
#include <list>

class Graph final {
public:
	std::list<Node*> topologicalSort(std::vector<Node*>& inputNodes);
	void forward(std::list<Node*>& nodes);
	void backward(std::list<Node*>& nodes);
	void sgdUpdate(std::vector<Input*>& trainables, double learningRate);
};