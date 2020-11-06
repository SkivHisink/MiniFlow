#include "Value.hpp"
#include <cmath>
Value& Value::operator= (Value* newVal) {
	newVal->M = M;
	newVal->col = col;
	newVal->row = row;
	return *this;
}
Value::Value(std::vector<std::vector<double>>& val) {
	row = val.size();
	col = val[0].size();
	M.assign(row, std::vector<double>(col));
	fill(val);
}
std::vector<std::vector<double>> Value::get_M() {
	return M;
}
Value::Value(std::vector<double>& val) {
	row = 1;
	col = val.size();
	M.assign(row, std::vector<double>(col));
	for (size_t i = 0; i < val.size(); ++i) {
		M[0][i] = val[i];
	}
}

Value::Value(size_t row_, size_t col_) {
	M.assign(row, std::vector<double>(col));
	row = row_;
	col = col_;
}

Value* Value::add(Value* V) {
	std::vector<std::vector<double>> res;
	res.assign(row, std::vector<double>(col));
	if (row == V->row && col == V->col) {
		for (size_t i = 0; i < row; ++i) {
			for (size_t j = 0; j < col; ++j) {
				res[i][j] = M[i][j] + V->M[i][j];
			}
		}
		set_M(res);
		return this;
	}
	if (V->row == 1 && col == V->col) {
		for (size_t i = 0; i < row; ++i) {
			;
			for (size_t j = 0; j < col; ++j) {
				res[i][j] = M[i][j] + V->M[0][j];
			}
		}
		set_M(res);
		return this;
	}
	return nullptr;
}

Value* Value::dot(Value* V) {
	std::vector<std::vector<double>> res;
	Value temp_val;
	if (col != V->row) {
		return nullptr;
	}
	res.assign(row, std::vector<double>(V->col));
	for (size_t i = 0; i < row; ++i) {
		for (size_t j = 0; j < V->col; ++j) {
			res[i][j] = 0.0;
			for (size_t k = 0; k < col; ++k) {
				res[i][j] += M[i][k] * V->M[k][j];
			}
		}
	}
	set_M(res);
	return this;
}

Value* Value::dot(double v) {
	std::vector<std::vector<double>> res;
	res.assign(row, std::vector<double>(col));
	for (size_t i = 0; i < row; ++i) {
		for (size_t j = 0; j < col; ++j) {
			res[i][j] = M[i][j] * v;
		}
	}
	set_M(res);
	return this;
}

double Value::mean() {
	double res = 0.0;
	for (size_t i = 0; i < row; ++i) {
		for (size_t j = 0; j < col; ++j) {
			res += M[i][j];
		}
	}
	return res / (static_cast<double>(row) * col);
}

void Value::fill(double val) {
	for (size_t i = 0; i < row; ++i) {
		for (size_t j = 0; j < col; ++j) {
			M[i][j] = val;
		}
	}
}

void Value::fill(std::vector<std::vector<double>>& val) {
	for (size_t i = 0; i < val.size(); ++i) {
		for (size_t j = 0; j < val[0].size(); ++j) {
			M[i][j] = val[i][j];
		}
	}
}



Value* Value::multiply(Value* V) {
	std::vector<std::vector<double>> res;
	if (row != V->row || col != V->col) {
		return nullptr;
	}
	res.assign(row, std::vector<double>(col));
	for (size_t i = 0; i < row; ++i) {
		for (size_t j = 0; j < V->col; ++j) {
			res[i][j] = M[i][j] * V->M[i][j];
		}
	}
	set_M(res);
	return this;
}

Value* Value::normalize() {
	std::vector<std::vector<double>> res;
	res.assign(row, std::vector<double>(col));
	double mean_ = mean();
	double std_ = std();
	for (size_t i = 0; i < row; ++i) {
		for (size_t j = 0; j < col; ++j) {
			res[i][j] = (M[i][j] - mean_) / std_;
		}
	}
	set_M(res);
	return this;
}
Value* Value::copy_data(Value* copy_elem) {
	set_M(copy_elem->get_M());
	return this;
}

Value* Value::normalizeColumn() {
	std::vector<std::vector<double>> res;
	res.assign(row, std::vector<double>(col));
	Value* t = new Value;
	t = Transpose();
	for (size_t i = 0; i < t->row; ++i) {
		Value* c;
		Value* val = new Value(t->M[i]);
		val->normalize();
		c = val->normalize();
		for (size_t j = 0; j < t->col; ++j) {
			res[j][i] = c->M[0][j];
		}
		delete c;
	}
	set_M(res);
	return this;
}

Value* Value::random() {
	//col = col_;
	//row = row_;
	M.assign(row, std::vector<double>(col));
	for (size_t i = 0; i < row; ++i) {
		for (size_t j = 0; j < col; ++j) {
			M[i][j] = (rand()) / (static_cast<double>(RAND_MAX) + 10.0);
		}
	}

	return this;
}

Value* Value::sigmoid() {
	std::vector<std::vector<double>> res;
	Value temp_val;
	res.assign(row, std::vector<double>(col));
	for (size_t i = 0; i < row; ++i) {
		for (size_t j = 0; j < col; ++j) {
			res[i][j] = 1.0 / (1.0 + exp(0.0 - M[i][j]));
		}
	}
	M = res;
	return this;
}

Value* Value::sigmoidPrime() {
	std::vector<std::vector<double>> res;
	Value temp_val;
	res.assign(row, std::vector<double>(col));
	for (size_t i = 0; i < row; ++i) {
		for (size_t j = 0; j < col; ++j) {
			double sigmoid = 1.0 / (1.0 + exp(0.0 - M[i][j]));
			res[i][j] = sigmoid * (1 - sigmoid);
		}
	}
	set_M(res);
	return this;
}

Value* Value::slice(size_t start, size_t batchSize, Value* val) {
	if (batchSize >= row) {
		val->M = {};
		val->col = 0;
		val->row = 0;
		return val;
	}
	std::vector<std::vector<double>> res;
	res.assign(batchSize, std::vector<double>(col));
	for (size_t i = 0; i < batchSize; ++i) {
		size_t index = (start + i) % row;
		for (size_t j = 0; j < col; ++j) {
			res[i][j] = M[index][j];
		}
	}
	val->set_M(res);
	return val;
}

double Value::std() {//Standard Deviation
	double mean_ = mean();
	double res = 0.0;
	for (size_t i = 0; i < row; ++i) {
		for (size_t j = 0; j < col; ++j) {
			res += (M[i][j] - mean_) * (M[i][j] - mean_);
		}
	}
	return sqrt(res / (static_cast<double>(row) * col));
}

Value* Value::sub(Value* V) {//
	std::vector<std::vector<double>> res;
	res.assign(row, std::vector<double>(col));
	if (row == V->row && col == V->col) {
		for (size_t i = 0; i < row; ++i) {
			for (size_t j = 0; j < col; ++j) {
				res[i][j] = M[i][j] - V->M[i][j];
			}
		}
		M = res;
		return this;
	}
	if (V->row == 1 && col == V->col) {
		for (size_t i = 0; i < row; ++i) {
			for (size_t j = 0; j < col; ++j) {
				res[i][j] = M[i][j] - V->M[0][j];
			}
		}
		M = res;
		return this;
	}
	return this;
}

Value* Value::subFromEachRow(Value* V) {
	std::vector<std::vector<double>> res;
	Value temp_val;
	if (V->row != 1 || col != V->col) {
		temp_val.M = res;
		temp_val.col = 0;
		temp_val.row = 0;
		return &temp_val;
	}
	res.assign(row, std::vector<double>(col));
	for (size_t i = 0; i < row; ++i) {
		for (size_t j = 0; j < col; ++j) {
			res[i][j] = M[i][j] - V->M[0][j];
		}
	}
	temp_val.M = res;
	temp_val.col = col;
	temp_val.row = row;
	return &temp_val;
}

Value* Value::sumRow() {
	std::vector< std::vector<double>> res;
	Value temp_val;
	res.assign(1, std::vector<double>(col, 0.0));
	for (size_t j = 0; j < col; ++j) {
		for (size_t i = 0; i < row; ++i) {
			res[0][j] += M[i][j];
		}
	}
	temp_val.M = res;
	temp_val.col = col;
	temp_val.row = row;
	return &temp_val;
}

double Value::sum() {
	double res = 0.0;
	for (size_t i = 0; i < row; ++i) {
		for (size_t j = 0; j < col; ++j) {
			res += M[i][j];
		}
	}
	return res;
}

Value* Value::Transpose() {
	std::vector<std::vector<double>> res;
	res.assign(col, std::vector<double>(row));
	for (size_t i = 0; i < row; ++i) {
		for (size_t j = 0; j < col; ++j) {
			res[j][i] = M[i][j];
		}
	}
	M = res;
	size_t tmp = col;
	col = row;
	row = tmp;
	return this;
}

void Value::set_M(std::vector<std::vector<double>> vec) {
	M = vec;
	row = vec.size();
	if (vec.size() != 0)
		col = vec[0].size();
	else
		col = 0;
}

std::string Value::toString() {
	std::string sb;
	sb.append("(" + std::to_string(row) + ", " + std::to_string(col) + ")\n");
	for (size_t i = 0; i < row; ++i) {
		sb.append("[");
		for (size_t j = 0; j < col; ++j) {
			sb.append(std::to_string(M[i][j]) + " ");
		}
		sb.append("]\n");
	}
	return sb;
}

size_t Value::get_row()
{
	return row;
}

size_t Value::get_col()
{
	return col;
}

Value* Value::zero() {
	M.assign(row, std::vector<double>(col, 0.0));
	return this;
}

