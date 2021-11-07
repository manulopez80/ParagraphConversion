#ifndef CParagraph_h
#define CParagraph_h

#include <string>
#include <map>
#include <vector>

using namespace std;
typedef map<string, size_t> MyMap;

class CParagraph 
{

public:	
	CParagraph();
	~CParagraph() = default;		

	//Traverse the paragraph and return it modified
	void TraverseParagraph(string &);

private:
	//Calculate the number in digits through the vector values 
	size_t GetNumberInDigits(const vector<size_t>);
	
	MyMap m_equivalenceMap;
	vector<size_t> m_vectorNumbers;
};

#endif
