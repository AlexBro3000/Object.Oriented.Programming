#include <iostream>
#include "Container.h"
using namespace std;

int main()
{
    setlocale(LC_ALL, "ru");

    cout << "Создание контейнеров и их запонение.\n";
    Container<int> t = Container<int>();
    Container<int> p = Container<int>();
    
    t.push_front(30);
    t.push_front(20);
    t.push_front(10);
    t.push_back(40);
    t.push_back(50);

    for (auto i : t)
        cout << i << " ";
    cout << endl;
    for (auto i : p)
        cout << i << " ";
    cout << endl;

    cout << "Приравнивание одноко контейнера другому.\n";
    p = t;

    for (auto i : t)
        cout << i << " ";
    cout << endl;
    for (auto i : p)
        cout << i << " ";
    cout << endl;

    cout << "Удаление крайних элементов.\n";
    p.pop_front();
    p.pop_back();
    for (auto i : t)
        cout << i << " ";
    cout << endl;
    for (auto i : p)
        cout << i << " ";
    cout << endl;

    auto a = t.begin();
    auto b = t.cbegin();
    auto c = t.rbegin();
    auto d = t.crbegin();

    ++a; a++; --a; a--;
    ++b; b++; --b; b--;
    ++c; c++; --c; c--;
    ++d; d++; --d; d--;

    cout << "SWAP:\n";
    t.swap(t.begin(), --t.end());
    for (auto i : t)
        cout << i << " ";
    cout << endl;

    cout << "Начало и конец списка.\n";
    cout << t.front() << endl;
    cout << t.back() << endl;

    cout << "ASSING -> RESIZE -> INSERT:\n";
    Node<int>* ins = new Node<int>(100);
    t.assign(5, 6);
    t.resize(8, 2);
    t.insert(t.crbegin(), ins);
    for (auto i : t)
        cout << i << " ";
    cout << endl;

    cout << "ERASE:\n";
    t.erase(t.cbegin());
    for (auto i : t)
        cout << i << " ";
    cout << endl;

    cout << "SWAP:\n";
    t.swap(p);
    for (auto i : t)
        cout << i << " ";
    cout << endl;
    t.swap(p);
    for (auto i : t)
        cout << i << " ";
    cout << endl;

    cout << "SORT:\n";
    t.sort();
    for (auto i : t)
        cout << i << " ";
    cout << endl;

    cout << "REVERSE:\n";
    t.reverse();
    for (auto i : t)
        cout << i << " ";
    cout << endl;

    cout << "UNIQUE:\n";
    t.unique();
    for (auto i : t)
        cout << i << " ";
    cout << endl;

    cout << "REMOVE:\n";
    cout << t.remove(6) << endl;//_if([](int n) { return n > 10; }) << endl;
    for (auto i : t)
        cout << i << " ";
    cout << endl;

    cout << "Наличие элементов в контейнере.\n";
    cout << t.empty() << endl;
    t.clear();
    cout << t.empty() << endl;

    cout << "Максимальный размер.\n";
    cout << t.max_size() << endl;

    cout << "\n";
    cout << typeid(t).name() << endl;
    cout << typeid(a).name() << endl;
    cout << typeid(b).name() << endl;
    cout << typeid(c).name() << endl;
    cout << typeid(d).name() << endl;

    Container<int>::allocator_type alloc = t.get_allocator();

    cout << endl;
}
