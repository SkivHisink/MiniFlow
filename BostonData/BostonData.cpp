#include "BostonData.hpp"

namespace {
	void split(const std::string& str, std::vector<std::string>& cont, char delim = ' ')
	{
		std::stringstream ss(str);
		std::string token;
		cont.clear();
		while (std::getline(ss, token, delim)) {
			cont.push_back(token);
		}
	}
}

BostonData::BostonData(size_t target_pos) {

	int row = 0;
	std::vector<std::vector<double>> new_data(samples, std::vector<double>(features, 0.0));
	data = new_data;
	new_data.clear();
	std::vector<double> new_target(samples, 0.0);
	target = new_target;
	new_target.clear();
	for (std::string line : raw_lines) {
		std::vector<std::string> splited;
		split(line, splited, ',');
		for (int i = 0; i < features; i++) {
			data[row][i] = stod(splited[i]);
		}
		target[row] = stod(splited[target_pos]);
		row++;
	}
}