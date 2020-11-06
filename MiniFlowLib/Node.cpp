#include "Node.hpp"

Node::Node(std::vector<Node*> inputs, std::string name_) {
	name = name_;
	value = nullptr;
	for (auto node : inputs) {
		inbounds.push_back(node);
		node->outbounds.push_back(this);
	}
}

Node::~Node() {
	if (value != nullptr) {
		delete value;
		value = nullptr;
	}
	if (inbounds.size() == 0) {
		inbounds.push_back(this);
	}
	cleanGradientsInbounds();
}

void Node::cleanGradientsInbounds() {
	for (size_t i = 0; i < gradients.size(); ++i) {
		if (gradients.find(inbounds[i]) == gradients.end()) {}
		else {
			if (gradients[inbounds[i]] != nullptr) {
				delete gradients[inbounds[i]];
				gradients[inbounds[i]] = nullptr;
			}
		}
	}
}
