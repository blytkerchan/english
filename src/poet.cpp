#include <algorithm>
#include <iostream>
#include <random>
#include <vector>
#include "poem.hpp"

using namespace std;
using namespace Vlinder::English;

int main()
{
	random_device r;

	vector< unsigned char > data(32);
	generate(data.begin(), data.end(), [&](){ return r(); });
	cout << createPoem(data);
}

