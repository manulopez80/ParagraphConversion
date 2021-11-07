#include "CParagraph.h"
#include <iostream>

using namespace std;

int main() 
{
    string source{};
    cout << "Write paragraph and press enter:" << endl;
    getline(cin, source);

    CParagraph paragraph;
    paragraph.TraverseParagraph(source);
    
    cout << endl << "The modified paragraph is:" << endl << source << endl;
    cout << endl << "Insert a key and Enter to finish..." << endl;
    
    char x{};
    cin >> x;

    return 0;
}


