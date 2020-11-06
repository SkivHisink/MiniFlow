#include "Input.hpp"

void Input::backward() {
	Value* total = new Value;
	total->copy_data(this->value)->zero();
	for (Node* node : outbounds) {
		total->add(node->gradients[this]);
	}
	for (size_t i = 0; i < gradients.size(); ++i) {
		if (gradients.find(this) == gradients.end()) {}
		else {
			if (gradients[this] != nullptr) {
				delete gradients[this];
				gradients[this] = nullptr;
			}
		}
	}
	gradients.insert_or_assign(this, total);
}
void Input::forward() {

}