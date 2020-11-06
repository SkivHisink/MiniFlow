#pragma once
#include <list>
#include <map>
#include "Value.hpp"
class Node {
public:
	Node() = delete;
	Node(std::vector<Node*> inputs, std::string name);
	virtual ~Node();
	virtual void forward() {};
	virtual void backward() {};
	void cleanGradientsInbounds();
	Value* value = nullptr;
	std::string name;
	std::map<Node*, Value*> gradients;
	std::vector<Node*> inbounds;
	std::vector<Node*> outbounds;
};