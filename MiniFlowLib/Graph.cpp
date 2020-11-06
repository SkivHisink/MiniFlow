#include "Graph.hpp"
#include <map>
#include <set>

std::list<Node*> Graph::topologicalSort(std::vector<Node*>& inputNodes) {
	std::list<Node*> nodes;
	for (auto node : inputNodes) {
		nodes.push_back(node);
	}
	std::map<Node*, std::set<Node*>> inbounds;
	std::map<Node*, std::set<Node*>> outbounds;
	while (!nodes.empty()) {
		Node* node = nodes.front();
		nodes.pop_front();
		for (auto m : node->outbounds) {
			std::set<Node*> out;
			if (outbounds.find(node) == outbounds.end()) {
				out = std::set<Node*>();
			}
			else {
				out = outbounds[node];
			}
			out.insert(m);
			outbounds.insert(std::pair<Node*, std::set<Node*>>(node, out));
			std::set<Node*> in;
			if (inbounds.find(m) == inbounds.end()) {
				in = std::set<Node*>();
			}
			else {
				in = inbounds[m];
			}
			in.insert(node);
			if (inbounds.find(m) == inbounds.end()) {
				inbounds.insert(std::pair<Node*, std::set<Node*>>(m, in));
			}
			else {
				inbounds[m].merge(in);
			}
			nodes.push_back(m);
		}
	}
	std::list<Node*> res;
	for (auto node : inputNodes) {
		nodes.push_back(node);
	}
	while (!nodes.empty()) {
		Node* node = nodes.front();
		nodes.pop_front();
		res.push_back(node);
		for (auto m : node->outbounds) {
			auto a = outbounds[node].erase(m);
			auto b = inbounds[m].erase(node);
			if (inbounds[m].empty()) {
				nodes.push_back(m);
			}
		}
	}
	return res;
}

void Graph::forward(std::list<Node*>& nodes) {
	for (Node* node : nodes) {
		node->forward();
	}
}

void Graph::backward(std::list<Node*>& nodes) {
	for (int i = nodes.size() - 1; i >= 0; --i) {
		auto l_front = nodes.begin();
		std::advance(l_front, i);
		(*l_front)->backward();
	}
}

void Graph::sgdUpdate(std::vector<Input*>& trainables, double learningRate) {
	for (Node* t : trainables) {
		Value* partial = new Value;
		partial->copy_data(t->gradients[t]);
		Value* tmpPtr = partial;
		partial->dot(learningRate);
		 t->value->sub(partial);
		 delete partial;
	}
}
