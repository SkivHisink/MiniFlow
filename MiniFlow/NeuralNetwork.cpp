#include "NeuralNetwork.hpp"
#include "Graph.hpp"
#include <time.h>

NeuralNetwork::NeuralNetwork(size_t features, size_t samples, size_t hidden, size_t epochs_, size_t batchSize_, double learningRate_) {
	srand(time(0));
	numFeatures = features;
	numSamples = samples;
	numHidden = hidden;
	epochs = epochs_;
	batchSize = batchSize_;
	stepsPerEpoch = numSamples / batchSize_;
	learningRate = learningRate_;

	W1_ = new Value(numFeatures, numHidden);
	W1_ = W1_->random();
	b1_ = new Value(1, numHidden);
	b1_ = b1_->zero();
	W2_ = new Value(numHidden, 1);
	W2_ = W2_->random();
	b2_ = new Value(1, 1);
	b2_ = b2_->zero();
	X = new Input("X");
	Y = new Input("Y");
	W1 = new Input(W1_, "W1");
	b1 = new Input(b1_, "b1");
	W2 = new Input(W2_, "W2");
	b2 = new Input(b2_, "b2");

	Linear1 = new Linear(X, W1, b1, "l1");
	Sigmoid1 = new Sigmoid(Linear1, "s1");
	Linear2 = new Linear(Sigmoid1, W2, b2, "l2");
	cost = new MSE(Y, Linear2, "cost");
}

NeuralNetwork::~NeuralNetwork() {
	delete cost;
	delete Linear2;
	delete Sigmoid1;
	delete Linear1;
	delete b2;
	delete W2;
	delete b1;
	delete W1;
	delete Y;
	delete X;
}

void NeuralNetwork::topologic_sort() {
	Graph graph;
	std::vector<Node*> inputNodes = { X, Y, W1, b1, W2, b2 };
	sortedNodes = graph.topologicalSort(inputNodes);
}
void NeuralNetwork::print_sorted_result() const {
	for (Node* node : sortedNodes) {
		std::cout << node->name << " ";
	}
	std::cout << std::endl;
}
void NeuralNetwork::print_number_of_examples() const {
	std::cout << "Total number of examples: " << numSamples << std::endl;

}

void NeuralNetwork::training(std::vector<std::vector<double>>& data, std::vector<double>& target, bool print_loss_per_epoch, bool print_nodes) {
	Graph graph;
	std::vector<Input*> trainables = { W1, b1, W2, b2 };
	Value* X_ = new Value(data);
	X_->normalizeColumn();
	Value* Y_ = new Value(target);
	Y_->Transpose();
	for (size_t i = 0; i < epochs; ++i) {
		double loss = 0.0;
		for (size_t j = 0; j < stepsPerEpoch; ++j) {
			size_t randomRowIndex = static_cast<size_t>(((rand()) / (static_cast<double>(RAND_MAX) + 1.0) * numSamples));
			if (X->value != nullptr) {
				delete X->value;
				X->value = nullptr;
			}
			if (Y->value != nullptr) {
				delete Y->value;
				Y->value = nullptr;
			}
			X->value = new Value;
			X_->slice(randomRowIndex, batchSize, X->value);
			Y->value = new Value;
			Y_->slice(randomRowIndex, batchSize, Y->value);
			graph.forward(sortedNodes);
			graph.backward(sortedNodes);
			graph.sgdUpdate(trainables, learningRate);
			auto l_front = sortedNodes.begin();
			std::advance(l_front, sortedNodes.size() - 1);
			loss += (*l_front)->value->mean();
		}
		if (print_loss_per_epoch) {
			std::cout << "Epoch " << i << ", Loss: " << loss / stepsPerEpoch << std::endl;
		}
	}
	if (print_nodes) {
		for (Node* param : trainables) {
			std::cout << "Node " << param->name << " is " << param->value->toString() << std::endl;
		}
	}
	if (X->value != nullptr) {
		delete X->value;
		X->value = nullptr;
	}
	if (Y->value != nullptr) {
		delete Y->value;
		Y->value = nullptr;
	}
	X->value = new Value;
	X_->slice(0, 10, X->value);
	Y->value = new Value;
	Y->value = Y_->slice(0, 10, Y->value);
	graph.forward(sortedNodes);
	delete Y_;
	delete X_;
}

void NeuralNetwork::print_result() const {
	auto l_front = sortedNodes.begin();
	std::advance(l_front, sortedNodes.size() - 2);
	Value* a = (*l_front)->value;
	a->Transpose();
	Value* n = Y->value->Transpose();
	std::cout << "Calculate result " << a->toString();
	std::cout << "Expected result " << n->toString();
	if (X->value != nullptr) {
		delete X->value;
		X->value = nullptr;
	}
	if (Y->value != nullptr) {
		delete Y->value;
		Y->value = nullptr;
	}
}