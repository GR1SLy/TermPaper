/*
exception tests
*/
#include "List.cpp"
#include "MyString.cpp"
#include <iostream>
#include <fstream>
#include <chrono>
using namespace std::chrono;
using namespace std;

void start_test();
void pushing();
void poping();
void insert_erase();
void sorting();
void serialize_deserialize();
void MyString_test();
void fastarr_test();
void Check_BigData();

int main()
{
    start_test();
    return 0;
}

void start_test()
{
    system("clear");
    cout << "Welcome to test menu!" << endl;
    cout << ".....................Tests......................" << endl;
    cout << "1.\tPush elements\n2.\tPop elements\n3.\tInsert and erase elements\n4.\tSort\n5.\tSerialize and deserialize\n6.\tCheck List with custom MyString class\n7.\tCheck fast array with different methods\n8.\tCheck sort with big data\n9.\tExit\nInput a number: ";
    int n;
    cin >> n;
    switch (n)
    {
        case 1:
            pushing();
            break;
        case 2:
            poping();
            break;
        case 3:
            insert_erase();
            break;
        case 4:
            sorting();
            break;
        case 5:
            serialize_deserialize();
            break;
        case 6:
            MyString_test();
            break;
        case 7:
            fastarr_test();
            break;
        case 8:
            Check_BigData();
            break;
        case 9:
            return;
        default:
        {
            system( "read -n 1 -s -p \"Wrong number! Press any key to restart...\"" );
            start_test();
        }
    }
}

void pushing()
{
    system("clear");
    cout << "Testing push operations for List................" << endl;
    List<int> lst;
    int a = 756;
    int b = 99;
    int c = 20;
    int d = 83;
    int e = 72;
    lst.push_back(&a);
    lst.push_back(&b);
    lst.push_back(&c);
    cout << "Current list:" << endl;
    lst.print();
    cout << "Pushing " << d << " front by pointer (list.push_front(&" << d << ");)" << endl;
    lst.push_front(&d);
    lst.print();
    cout << "Pushing " << e << " back by pointer (list.push_back(&" << e << "):)" << endl;
    lst.push_back(&e);
    lst.print();
    system( "read -n 1 -s -p \"Press any key to continue...\"" );
    start_test();
}

void poping()
{
    system("clear");
    cout << "Testing pop operations for List................." << endl;
    List<int> lst;
    int a = 756;
    int b = 99;
    int c = 20;
    int d = 83;
    int e = 72;
    lst.push_back(&a);
    lst.push_back(&b);
    lst.push_back(&c);
    lst.push_back(&d);
    lst.push_back(&e);
    cout << "Current list:" << endl;
    lst.print();
    cout << "Poping back (list.pop_back();)" << endl;
    lst.pop_back();
    lst.print();
    cout << "Poping front (list.pop_front();)" << endl;
    lst.pop_front();
    lst.print();
    system( "read -n 1 -s -p \"Press any key to continue...\"" );
    start_test();
}

void insert_erase()
{
    system("clear");
    cout << "Testing insert and erase operations............." << endl;
    List<int> lst;
    int a = 756;
    int b = 99;
    int c = 20;
    int d = 83;
    int e = 72;
    lst.push_back(&a);
    lst.push_back(&b);
    lst.push_back(&c);
    cout << "Current list:" << endl;
    lst.print();
    List<int>::iterator it = lst.begin();
    advance(it, 2);
    cout << "Inserting " << d << " before third element (list.insert(it, &" << d << ");)" << endl;
    lst.insert(it, &d);
    lst.print();
    cout << "Erasing second element (list.erase(it);)" << endl;
    it = lst.begin();
    lst.erase(++it);
    lst.print();
    system( "read -n 1 -s -p \"Press any key to continue...\"" );
    start_test();
}

void sorting()
{
    system("clear");
    cout << "Testing sort for int List......................." << endl;
    List<int> lst;
    int a = 756;
    int b = 99;
    int c = 20;
    int d = 83;
    int e = 72;
    lst.push_back(&a);
    lst.push_back(&b);
    lst.push_back(&c);
    lst.push_back(&d);
    lst.push_back(&e);
    cout << "Current list:" << endl;
    lst.print();
    cout << "Sorted list (list.sort()):" << endl;
    lst.sort();
    lst.print();
    cout << "Testing sort for char* List....................." << endl;
    List<char*> lstc;
    char* ac = new char[5];
    ac = "ertf\0";
    char* bc = new char[5];
    bc = "asde\0";
    char* cc = new char[5];
    cc = "thg\0";
    char* dc = new char[5];
    dc = "zyrt\0";
    char* ec = new char[5];
    ec = "iuor\0";
    lstc.push_back(&ac);
    lstc.push_front(&bc);
    lstc.push_front(&cc);
    lstc.push_front(&dc);
    lstc.push_front(&ec);
    cout << "Current list:" << endl;
    lstc.print();
    cout << "Sorted list (list.sort()):" << endl;
    lstc.sort();
    lstc.print();
    system( "read -n 1 -s -p \"Press any key to continue...\"" );
    start_test();
}

void serialize_deserialize()
{
    system("clear");
    cout << "Testing serialization and deserialization List..." << endl;
    List<char*> lst;
    char* a = new char[5];
    a = "ertf\0";
    char* b = new char[5];
    b = "asde\0";
    char* c = new char[5];
    c = "thg\0";
    char* d = new char[5];
    d = "zyrt\0";
    char* e = new char[5];
    e = "iuor\0";
    lst.push_back(&a);
    lst.push_front(&b);
    lst.push_front(&c);
    lst.push_front(&d);
    lst.push_front(&e);
    cout << "Current list:" << endl;
    lst.print();
    int n;
    cout << "Choose method:\n1.\tSerialize\n2.\tDeserialize\n3.\tReturn to menu\nInput a number: ";
    cin >> n;
    if (n == 1) { cout << "Starting serialization. Check test.bin!" << endl; lst.serialize("test.bin"); system( "read -n 1 -s -p \"Press any key to continue...\"" ); serialize_deserialize(); }
    else if (n == 2) { List<char*> lst; cout << "Starting deserialization from test.bin" << endl; lst.deserialize("test.bin"); lst.print(); system( "read -n 1 -s -p \"Press any key to continue...\"" ); serialize_deserialize(); }
    else if (n == 3) { start_test(); }
    else { system( "read -n 1 -s -p \"Wrong number! Press any key to restart...\"" ); serialize_deserialize(); }
}

void MyString_test()
{
    system("clear");
    cout << "Testing List with custom class MyString.........." << endl;
    List<MyString> lst;
    MyString s1 = "Hello";
    MyString s2 = "World";
    MyString s3 = "!";
    lst.push_back(&s1);
    lst.push_back(&s2);
    lst.push_back(&s3);
    cout << "Current list:" << endl;
    lst.print();
    cout << "Sorted list:" << endl;
    lst.sort();
    lst.print();
    system( "read -n 1 -s -p \"Press any key to continue...\"" );
    start_test();
}

void fastarr_test()
{
    system("clear");
    cout << "Testing List's fastarray........................" << endl;
    List<int> lst;
    int *a;
    for (int i = 0; i < 35; i++)
    {
        a = new int(i);
        lst.push_front(a);
    }
    cout << "Current list:" << endl;
    lst.print();
    lst.printarr();
    cout << endl;
    List<int>::iterator it;
    cout << "Choose tests: \n1.\tPush and pop\n2.\tInsert\n3.\tErase\nInput a number: ";
    int n;
    cin >> n;
    switch (n)
    {
        case 1:
        {
            system("clear");
            cout << "Pushing front" << endl;
            int b = 999;
            lst.push_front(&b);
            lst.print();
            lst.printarr();
            cout << "Poping front" << endl;
            lst.pop_front();
            lst.pop_front();
            lst.print();
            lst.printarr();
            break;
        }
        case 2:
        {
            it = lst.begin();
            advance(it, 25, lst);
            int c = 47543;
            cout << "Insert " << c << " before 15th element" << endl;
            lst.insert(it, &c);
            lst.print();
            lst.printarr();
            break;
        }
        case 3:
        {
            it = lst.begin();
            advance(it, 15, lst);
            cout << "Erase 15 element" << endl;
            lst.erase(it);
            lst.print();
            lst.printarr();
            break;
        }
    }
    system( "read -n 1 -s -p \"Press any key to continue...\"" );
    start_test();
}

void Check_BigData()
{
    system("clear");
    List<int> lst;
    cout << "Enter count of elements to check: ";
    long int n;
    cin >> n;
    int **arr = new int*[n];
    for (int i = 0; i < n; i++)
    {
        arr[i] = new int(i);
        lst.push_front(arr[i]);
    }
    auto start = steady_clock::now();
    lst.sort();
    auto finish = steady_clock::now();
    cout << "Duration of sort with " << n << " elements: " << duration_cast<milliseconds>(finish - start).count() << " milliseconds" << endl;
    for (int i = 0; i < n; i++)
    {
        delete arr[i];
    }
    delete[] arr;
    system( "read -n 1 -s -p \"Press any key to continue...\"" );
    start_test();
}
