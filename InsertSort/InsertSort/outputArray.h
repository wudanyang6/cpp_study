#include <iostream>

class outputArray
{
public:
	outputArray(){};
	~outputArray(){};
	void outArray(int arr[], long arrlength);
};

void outputArray::outArray(int arr[], long arrlength)
{
	for (long i = 0; i < arrlength; i++)
	{
		std::cout << arr[i] << "\t";
	}
	std::cout << std::endl;
};