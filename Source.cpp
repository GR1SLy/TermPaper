#include "List.cpp"
#include <iostream>
using namespace std;

int main()
{
    List<int> lst;
    for (int i = 0; i < 35; i++)
    {
        lst.push_back(i);
    }
    /* lst.print();
    cout << endl << endl;
    List<int>::iterator it = lst.begin();
    cout << "Fit: " << *++it << endl;
    lst.insert(it, 999);
    lst.print();
    advance(it, 2);
    cout << "Sit: " << *++it << endl;
    lst.erase(it);
    lst.print(); */
    cout << endl << endl;
    lst.print();
    cout << lst.GetSize() << endl;
    cout << endl << endl;
    lst.printarr();
    return 0;
}