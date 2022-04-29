#include <iostream>
#include "Container.h"
using namespace std;

int main()
{
    Container<int> t = Container<int>();

    t.push_front(30);
    t.push_front(20);
    t.push_front(10);
    t.push_back(40);
    t.push_back(50);

    auto a = t.begin();
    auto b = t.cbegin();
    auto c = t.rbegin();
    auto d = t.crbegin();

    ++a;
    ++b;
    ++c;
    ++d;
    a++;
    b++;
    c++;
    d++;
    --a;
    --b;
    --c;
    --d;
    a--;
    b--;
    c--;
    d--;

    cout << (*c) << endl;

    cout << typeid(t).name() << endl;
    cout << typeid(a).name() << endl;
    cout << typeid(b).name() << endl;

    t.pop_front();
    t.pop_back();

    t.clear();
    cout << endl;
}
