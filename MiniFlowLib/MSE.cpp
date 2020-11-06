#include "MSE.hpp"

MSE::~MSE() {
	if (diff != nullptr) {
		delete diff;
		diff = nullptr;
	}
}

void MSE::forward() {
	Node* Y = inbounds[0];
	Node* A = inbounds[1];
	m = Y->value->get_row();
	if (diff != nullptr) {
		delete diff;
		diff = nullptr;
	}
	if (value != nullptr) {
		delete value;
		value = nullptr;
	}
	diff = new Value;
	diff->copy_data(Y->value);
	diff->sub(A->value);
	Value* res = new Value;
	res->copy_data(diff);
	res->Transpose()->dot(diff)->dot(1/m);
	value = res;
}

void MSE::backward() {
	cleanGradientsInbounds();
	Value* val = new Value;
	val->copy_data(diff);
	gradients.insert_or_assign(inbounds[0], val->dot(2.0 / m));
	val = new Value;
	val->copy_data(diff);
	gradients.insert_or_assign(inbounds[1], val->dot(-2.0 / m));
}
