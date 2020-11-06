#include"Sigmoid.hpp"

void Sigmoid::backward()  {
	Value* grads = new Value;
	grads->copy_data(inbounds[0]->value)->zero();
	for (Node* node : outbounds) {
		Value* cost = new Value;
		grads->add(cost->copy_data(inbounds[0]->value)->sigmoidPrime()->multiply(node->gradients[this]));
		delete cost;
	}
	cleanGradientsInbounds();
	gradients.insert_or_assign(inbounds[0], grads);
}

void Sigmoid::forward() {
	Node* input = inbounds[0];
	if (value != nullptr) {
		delete value;
		value = nullptr;
	}
	value = new Value;
	value->copy_data(input->value);
	value->sigmoid();
}
