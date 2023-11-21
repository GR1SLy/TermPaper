/*
Задачи:
Поставить УКАЗАТЕЛИ на объекты
Сериализация
*/


#include "List.cpp"
#include <iostream>
using namespace std;

int main()
{
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
    // lst.push_front(32);
    //List<int>::iterator it = lst.begin();
    //lst.insert(it, 7632);
    //lst.erase(it);
    // lst.push_front(1111);

    List<int> lst;
    for (int i = 20; i > 0; i--)
    {
        lst.push_back(i);
    }
    
    lst.push_front(928);
    lst.push_front(8832);

    //lst.sort();
    cout << "Current List:" << endl;
    lst.print();
    cout << "Size of list: " << lst.GetSize() << endl;
    cout << endl << endl;
    lst.printarr();

    auto it = lst.begin();
    cout << "it1: " << it.get_count() << endl;
    ++it;
    cout << "it2: " << it.get_count() << endl;
    advance(it, 5, lst);
    cout << "it3: " << it.get_count() << endl;
    lst.insert(it, 9874);
    lst.erase(++it);
    // it = lst.end();
    lst.print();
    lst.printarr();
    cout << endl;
    lst.erase(it);
    cout << "it4: " << it.get_count() << endl;
    cout << endl << endl;
    lst.pop_back();
    lst.print();
    cout << endl;
    lst.printarr();
    // lst.push_front(8832);
    // lst.push_front(735);
    // lst.push_front(888);
    // lst.push_front(823);
    // lst.push_back(2);
    // lst.push_front(5);
    // lst.push_front(20);
    // lst.push_front(18);
    // lst.push_front(17);
    // lst.push_front(1);
    // lst.push_back(1);
    // lst.push_back(0);
    // lst.push_back(10);
    // lst.push_back(9);
    // lst.push_back(8);
    // lst.push_front(3);
    // lst.push_back(3);
    // lst.print();
    // cout << endl << endl;
    // lst.sort();
    // lst.print();
    return 0;
}