#include "gtest/gtest.h"
#include <iostream>

using namespace std;

int main(int argc, char **argv) 
{
    ::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	cout << endl << "Insert a key and Enter to finish..." << endl;
	
	char x{};
	cin >> x;
	return 0;
}