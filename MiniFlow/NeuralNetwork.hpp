#pragma once
#include "Value.hpp"
#include "Linear.hpp"
#include "Sigmoid.hpp"
#include "MSE.hpp"
#include "Input.hpp"
#include <iostream>
#include <iterator>

class NeuralNetwork final {
public:
	NeuralNetwork(size_t features, size_t samples, size_t hidden, size_t epochs_, size_t batchSize_, double learningRate_);
	~NeuralNetwork();
	NeuralNetwork& operator=(const NeuralNetwork& NN) = delete;
	void topologic_sort();
	void print_sorted_result() const;
	void training(std::vector<std::vector<double>>& data, std::vector<double>& target, bool print_loss_per_epoch, bool print_nodes);
	void print_result() const;
	void print_number_of_examples() const;
private:
	size_t numFeatures;
	size_t numSamples;
	size_t numHidden;
	size_t epochs;
	size_t batchSize;
	size_t stepsPerEpoch;
	double learningRate;

	Value* W1_;
	Value* b1_;
	Value* W2_;
	Value* b2_;

	Input* X;
	Input* Y;
	Input* W1;
	Input* b1;
	Input* W2;
	Input* b2;

	Node* Linear1;
	Node* Sigmoid1;
	Node* Linear2;
	Node* cost;

	std::list<Node*> sortedNodes;
};

