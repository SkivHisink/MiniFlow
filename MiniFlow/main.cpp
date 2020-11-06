#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "NeuralNetwork.hpp"
#include "BostonData.hpp"
int main() 
{
	{
		BostonData data(13);
		NeuralNetwork Boston_network(14, data.samples, 10, 1000, 1, 0.01);
		Boston_network.topologic_sort();
		Boston_network.print_sorted_result();
		Boston_network.print_number_of_examples();
		Boston_network.training(data.data, data.target, true, true);
		Boston_network.print_result();
	}
	_CrtDumpMemoryLeaks();
	return 0;
 }