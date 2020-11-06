#include "Linear.hpp"
void Linear::forward() {
	Value* X = new Value;
	Value* W = inbounds[1]->value;
	Value* b = inbounds[2]->value;
	X->copy_data(inbounds[0]->value);
	X = X->dot(W)->add(b);
	if (value != nullptr) {
		delete value;
		value = nullptr;
	}
	value = X;
}

void Linear::backward()  {
	Value* gradX = new Value;
	gradX->copy_data(inbounds[0]->value)->zero();
	Value* gradW = new Value; 
	gradW->copy_data(inbounds[1]->value)->zero();
	Value* gradB =  new Value; 
	gradB->copy_data(inbounds[2]->value)->zero();

	for (Node* node : outbounds) {
		Value* cost = new Value;
		Value* tmpPtr = new Value;
		cost->copy_data(node->gradients[this]);
		tmpPtr->copy_data(inbounds[1]->value)->Transpose();
		gradX->add(cost->dot(tmpPtr));
		tmpPtr->copy_data(inbounds[0]->value)->Transpose();
		gradW->add(tmpPtr->dot(node->gradients[this]));
		cost->copy_data(node->gradients[this])->sumRow();
		gradB->add(cost);
		delete tmpPtr;
		delete cost;
	}
	cleanGradientsInbounds();
	gradients.insert_or_assign(inbounds[0], gradX);
	gradients.insert_or_assign(inbounds[1], gradW);
	gradients.insert_or_assign(inbounds[2], gradB);
}