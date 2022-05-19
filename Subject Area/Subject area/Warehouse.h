#pragma once
#include "Container.h"
#include "Product.h"
#include <fstream>
using namespace std;

size_t number_id = 1;

// Класс 
class Warehouse
{
	friend class IWarehouse;
	friend class BuilderWarehouse;
protected:
	const size_t number;        // Номер склада
	const size_t subnumber;     // Подномер склада
	const Address adress;       // Адрес склада
	Container<IProduct*> product; // Товар на складе

public:
	// Конструкторы / Создание склада
	Warehouse() :
		number(number_id), subnumber(1)
	{
		number_id++;
	}
	Warehouse(Address adress) :
		number(number_id), subnumber(1), adress(adress)
	{
		number_id++;
	}
	// Конструкторы / Копирования
	Warehouse(const Warehouse* other) :
		number(other->number), subnumber(other->subnumber + 1), adress(other->adress)
	{ }
	// Деструктор
	~Warehouse()
	{
		product.~Container();
	}

private:

};
// Интерфейс склад
class IWarehouse
{
public:
	virtual void setProduct(IProduct* prd) = 0;

	virtual string getNumber() const = 0;
	virtual string getAddress() const = 0;
	virtual Warehouse* getWarehouse() = 0;
};

// Строитель склада
class BuilderWarehouse : public IWarehouse
{
protected:
	Warehouse* warehouse;

public:
	BuilderWarehouse()
	{
		warehouse = new Warehouse();
	}
	BuilderWarehouse(Address adress)
	{
		warehouse = new Warehouse(adress);
	}
	~BuilderWarehouse()
	{
		delete warehouse;
	}

	void setProduct(IProduct* prd) override
	{
		warehouse->product.push_back(prd);
	}

	string getNumber() const override
	{
		string str = to_string(warehouse->number) + "." + to_string(warehouse->subnumber);
		return str;
	}
	string getAddress() const override
	{
		Address adr = warehouse->adress;
		string str = to_string(adr.index) + ", " + adr.country + ", " + adr.region + ", " + adr.city + ", " + adr.street;
		return str;
	}
	Warehouse* getWarehouse() override
	{
		return warehouse;
	}
};

// Менджер склада
class Manager
{
protected:
	const string name;
	IWarehouse* warehouse;

	Container<string> contr;   // Поставщики
	Container<IProduct*> prod; // Заказы

public:
	Manager(string name, IWarehouse* wrhs = new BuilderWarehouse()) :
		name(name), warehouse(wrhs)
	{
		prod = Container<IProduct*>();
	}

	void order_Apple(AplleOrchard* aplleorc, string name, size_t box = 1)
	{
		AddContractor(aplleorc);
		prod.push_back(aplleorc->order(name, box));
	}
	void order_Apple(AplleOrchard* aplleorc, size_t box = 1)
	{
		AddContractor(aplleorc);
		prod.push_back(aplleorc->order("Зеленое яблоко", box));
		prod.push_back(aplleorc->order("Желтое яблоко", box));
		prod.push_back(aplleorc->order("Красное яблоко", box));
	}
	void order_Pipes(SteelPlant* steelpl, string name, double_t diameter, double_t length, size_t box = 1)
	{
		AddContractor(steelpl);
		prod.push_back(steelpl->order(name, diameter, length, box));
	}
	void order_Pipes(SteelPlant* steelpl, double_t diameter, double_t length, size_t box = 1)
	{
		AddContractor(steelpl);
		prod.push_back(steelpl->order("Медная труба", diameter, length, box));
		prod.push_back(steelpl->order("Стальная труба", diameter, length, box));
	}
	void order_Pipes(SteelPlant* steelpl, size_t box = 1)
	{
		AddContractor(steelpl);
		prod.push_back(steelpl->order("Медная труба", 10, 600, box));
		prod.push_back(steelpl->order("Медная труба", 100, 1000, box));
		prod.push_back(steelpl->order("Стальная труба", 10, 2000, box));
		prod.push_back(steelpl->order("Стальная труба", 100, 4000, box));
	}
	
	void order()
	{
		while (!prod.empty())
		{
			string iter_manuf = (*prod.begin())->getManufacturer();

			Сonsignment(iter_manuf);
			for (Container<IProduct*>::iterator j = prod.begin(); j != prod.end(); j++)
			{
				if ((*j)->getManufacturer() == iter_manuf)
				{
					(*j)->setDate(getDate());
					warehouse->setProduct(*j);

					prod.erase(j++);
					j--;
				}
			}
		}
	}
	void order(string manufacturer)
	{
		string iter_manuf = manufacturer;

		Сonsignment(iter_manuf);
		for (Container<IProduct*>::iterator j = prod.begin(); j != prod.end(); j++)
		{
			if ((*j)->getManufacturer() == iter_manuf)
			{
				(*j)->setDate(getDate());
				warehouse->setProduct(*j);

				prod.erase(j++);
				j--;
			}
		}
	}
private:
	void Сonsignment(string contr_name)
	{
		ofstream f("Сonsignment/Накладная_" + contr_name + "   " + strDate() + ".txt", ios::out);

		f << "ТОВАРНО ТРАНСПОРТНАЯ НАКЛАДНАЯ:" << endl;
		f << "Грузоотправитель: " << contr_name << endl;
		f << "Грузополучатель:  Склад " << warehouse->getNumber() << ", " << warehouse->getAddress()
			<< endl;

		f << endl << "ТОВАРНЫЙ РАЗДЕЛ" << endl;
		size_t i = 0;
		double_t price = 0;
		double_t mass = 0;

		for (Container<IProduct*>::iterator j = prod.begin(); j != prod.end(); j++)
		{
			if ((*j)->getManufacturer() == contr_name)
			{
				f << ++i << ":" << endl;
				f << "  Название:                   " << (*j)->getName() << endl;
				f << "  Количество партий:          " << (*j)->getBox() << endl;
				f << "  Цена партии:                " << (*j)->getPrice() << endl;
				f << "  Количество товара в партии: " << (*j)->getQuantity() << endl;
				f << "  Вес одной партии:           " << (*j)->getMass() << endl;
				price += stod((*j)->getPrice()) * stod((*j)->getBox());
				mass += stod((*j)->getMass()) * stod((*j)->getBox());
			}
		}
		if (!i)
			f << "  Нет товара." << endl;

		f << endl << "Цена груза:  " << to_string(price) << endl;
		f << "Масса груза: " << to_string(mass) << endl;
		f << "Груз принял: " << name << endl;
		f << "Дата:        " << getDate() << endl;

		f.close();
	}

	template<typename T>
	void AddContractor(T obj)
	{
		string str = obj->getName();
		for (auto i : contr)
			if (i == str)
				return;
		contr.push_back(str);
	}

};
