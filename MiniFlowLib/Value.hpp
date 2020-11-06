#pragma once
#include <string>
#include <vector>

class Value final {
public:
	Value() = default;
	Value(std::vector<std::vector<double>>& val);
	Value(std::vector<double>& val);
	Value(size_t row, size_t col);
	~Value() = default;
	Value& operator= (Value* newVal);
	void fill(double val);
	void fill(std::vector<std::vector<double>>& val);

	Value* add(Value* V);
	Value* dot(Value* V);
	Value* dot(double v);
	Value* copy_data(Value* copy_elem);
	Value* multiply(Value* V);
	Value* normalize();
	Value* normalizeColumn();
	Value* random();
	void set_M(std::vector<std::vector<double>> vec);
	Value* sigmoid();
	Value* sigmoidPrime();
	Value* slice(size_t start, size_t batchSize, Value* val);
	Value* sub(Value* V);
	Value* subFromEachRow(Value* V);
	Value* sumRow();
	Value* Transpose();
	Value* zero();

	double mean();
	double std();
	double sum();

	std::string toString();
	std::vector<std::vector<double>> get_M();
	size_t get_row();
	size_t get_col();

private:
	std::vector<std::vector<double>> M;
	size_t row;
	size_t col;
};