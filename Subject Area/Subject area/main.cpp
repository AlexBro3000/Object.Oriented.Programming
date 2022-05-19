#define _CRT_SECURE_NO_WARNINGS
#include "Warehouse.h"
using namespace std;

int main()
{
    setlocale(LC_ALL, "ru");

    AplleOrchard* aplleorc = new AplleOrchard("Яблоневый сад");
    SteelPlant* steelpl = new SteelPlant("Город труб");

    Manager manager("Иванов И.И.");
    manager.order_Pipes(steelpl, 100);
    manager.order_Pipes(steelpl, 100);
    manager.order_Apple(aplleorc, 100);

    manager.order("Кочерга");
    manager.order();

    cout << strDate();
}
