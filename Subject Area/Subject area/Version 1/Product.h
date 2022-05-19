#pragma once
#include "Date.h"
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

struct Address
{
	// Страна
	string country = "Россия";
	// Регион
	string region = "Приморский край";
	// Город
	string city = "Русский остров";
	// Улица
	string street = "Аякс";
	// Индекс
	size_t index = 690922;

};

// Классы товара
class Product
{
	friend class IProduct;
	friend class Aplle;
	friend class Pipes;
protected:
	const string name;          // Название товара
	const string manufacturer;  // Производитель товара
	string date;                // Дата производства / доставки
	double_t price;             // Цена партии / упаковки
	size_t quantity;            // Количество товара в партии / упаковке
	double_t mass;              // Вес партии / упаковки

public:
	Product() {}
	Product(string name, string manufacturer) :
		name(name), manufacturer(manufacturer)
	{ }
	Product(Product* prd) :
		name(prd->name), manufacturer(prd->manufacturer)
	{
		date = prd->date;
		price = prd->price;
		quantity = prd->quantity;
		mass = prd->mass;
	}
	~Product() {}

private:

};
class IProduct// : public Product
{
public:
	virtual void setDate(string date) = 0;
	virtual void setPrice(double_t price) = 0;
	virtual void setQuantity(size_t quantity) = 0;
	virtual void setMass(double_t mass) = 0;
	virtual void setBox(size_t box) = 0;
	virtual void setDiameter(double_t d) = 0;
	virtual void setLength(double_t l) = 0;

	virtual string getName() = 0;
	virtual string getManufacturer() = 0;
	virtual string getBox() = 0;
	virtual string getPrice() = 0;
	virtual string getQuantity() = 0;
	virtual string getMass() = 0;

};

// Яблоки
class Aplle : public IProduct
{
protected:
	Product* prd; // Продукт
	size_t box;   // Количество

public:
	Aplle() {}
	Aplle(string name, string manufacturer, string date)
	{
		prd = new Product(name, manufacturer);
		prd->date = date;
	}
	Aplle(Aplle* aplle)
	{
		prd = new Product(aplle->prd);
		box = aplle->box;
	}
	~Aplle()
	{
		delete prd;
	}

	void setDate(string date) override
	{
		prd->date = date;
	}
	void setPrice(double_t price) override
	{
		prd->price = price;
	}
	void setQuantity(size_t quantity) override
	{
		prd->quantity = quantity;
	}
	void setMass(double_t mass) override
	{
		prd->mass = mass;
	}
	void setBox(size_t box) override
	{
		this->box = box;
	}

	string getName() override
	{
		return prd->name;
	}
	string getManufacturer() override
	{
		return prd->manufacturer;
	}
	string getBox() override
	{
		return to_string(box);
	}
	string getPrice() override
	{
		return to_string(prd->price);
	}
	string getQuantity()
	{
		return to_string(prd->quantity);
	}
	string getMass()
	{
		return to_string(prd->mass);
	}

private:
	void setDiameter(double_t d) override {}
	void setLength(double_t l) override {}

};

// Трубы
class Pipes : public IProduct
{
protected:
	Product* prd; // Продукт
	size_t box;   // Количество
	double_t d;   // Диаметр
	double_t l;   // Длина

public:
	Pipes() {}
	Pipes(string name, string manufacturer, string date)
	{
		prd = new Product(name, manufacturer);
		prd->date = date;
	}
	Pipes(Pipes* pipe)
	{
		prd = new Product(pipe->prd);
		box = pipe->box;
		d = pipe->d;
		l = pipe->l;
	}
	~Pipes()
	{
		delete prd;
	}

	void setDate(string date) override
	{
		prd->date = date;
	}
	void setPrice(double_t price) override
	{
		prd->price = price;
	}
	void setQuantity(size_t quantity) override
	{
		prd->quantity = quantity;
	}
	void setMass(double_t mass) override
	{
		prd->mass = mass;
	}
	void setBox(size_t box) override
	{
		this->box = box;
	}
	void setDiameter(double_t d) override
	{
		this->d = d;
	}
	void setLength(double_t l) override
	{
		this->l = l;
	}

	string getName() override
	{
		return prd->name + " " + to_string(d) + "*1*" + to_string(l);
	}
	string getManufacturer() override
	{
		return prd->manufacturer;
	}
	string getBox() override
	{
		return to_string(box);
	}
	string getPrice() override
	{
		return to_string(prd->price);
	}
	string getQuantity()
	{
		return to_string(prd->quantity);
	}
	string getMass()
	{
		return to_string(prd->mass);
	}

private:

};

class Command
{
protected:
	Command() = default;

public:
	string name;     // Название товара
	double_t price;  // Цена партии / упаковки
	size_t quantity; // Количество товара в партии / упаковоке
	double_t mass;   // Вес партии / упаковки
	double_t diam;   // Диаметр
	double_t len;    // Длина

public:
	virtual ~Command() {}
	virtual void execute(IProduct* prd) = 0;

};
class CreateProduct : public Command
{
public:
	CreateProduct(string n) /*, IProduct* p) : Command(p)*/
	{
		name = n;
	}
	void execute(IProduct* prd)
	{
		prd->setDate(getDate());
	}

};
class SetPrice : public Command
{
public:
	SetPrice(double_t p)/*, IProduct* _p) : Command(_p)*/
	{
		price = p;
	}
	void execute(IProduct* prd)
	{
		prd->setPrice(price);
	}

};
class SetQuantity : public Command
{
public:
	SetQuantity(size_t q)/*, IProduct* p) :	Command(p)*/
	{
		quantity = q;
	}
	void execute(IProduct* prd)
	{
		prd->setQuantity(quantity);
	}

};
class SetMass : public Command
{
public:
	SetMass(double_t m)/*, IProduct* p) : Command(p)*/
	{
		mass = m;
	}
	void execute(IProduct* prd)
	{
		prd->setMass(mass);
	}

};
class SetDiameter : public Command
{
public:
	SetDiameter(double_t d)/*, IProduct* p) : Command(p)*/
	{
		diam = d;
	}
	void execute(IProduct* prd)
	{
		prd->setDiameter(diam);
	}

};
class SetLength : public Command
{
public:
	SetLength(double_t l)/*, IProduct* p) : Command(p)*/
	{
		len = l;
	}
	void execute(IProduct* prd)
	{
		prd->setLength(len);
	}

};

// Яблоневый сад
class AplleOrchard
{
protected:
	const string name;
	vector<vector<Command*>> cont;

public:
	AplleOrchard(string name) :
		name(name)
	{
		vector<Command*> prd_1;
		prd_1.push_back(new CreateProduct("Зеленое яблоко"));
		prd_1.push_back(new SetPrice(2800.00));
		prd_1.push_back(new SetQuantity(30));
		prd_1.push_back(new SetMass(13));
		cont.push_back(prd_1);

		vector<Command*> prd_2;
		prd_2.push_back(new CreateProduct("Желтое яблоко"));
		prd_2.push_back(new SetPrice(2960.00));
		prd_2.push_back(new SetQuantity(32));
		prd_2.push_back(new SetMass(11));
		cont.push_back(prd_2);

		vector<Command*> prd_3;
		prd_3.push_back(new CreateProduct("Красное яблоко"));
		prd_3.push_back(new SetPrice(3420.00));
		prd_3.push_back(new SetQuantity(38));
		prd_3.push_back(new SetMass(16));
		cont.push_back(prd_3);
	}

	IProduct* order(string name, size_t box = 1)
	{
		size_t i = 0;
		while (i < cont.size() && cont[i][0]->name != name)
			i++;

		if (i < cont.size() && cont[i][0]->name == name)
		{
			IProduct* prd = new Aplle(name, this->name, "");
			for (auto j : cont[i])
				j->execute(prd);
			prd->setBox(box);

			return prd;
		}
		return nullptr;
	}
	string getName()
	{
		return name;
	}

};

// Сталелитейный завод
class SteelPlant
{
protected:
	const string name;
	vector<vector<Command*>> cont;

public:
	SteelPlant(string name) :
		name(name)
	{
		vector<Command*> prd_1;
		prd_1.push_back(new CreateProduct("Медная труба"));
		prd_1.push_back(new SetDiameter(10));
		prd_1.push_back(new SetLength(600));
		prd_1.push_back(new SetPrice(20224.00));
		prd_1.push_back(new SetQuantity(32));
		prd_1.push_back(new SetMass(14.656));
		cont.push_back(prd_1);

		vector<Command*> prd_2;
		prd_2.push_back(new CreateProduct("Медная труба"));
		prd_2.push_back(new SetDiameter(100));
		prd_2.push_back(new SetLength(1000));
		prd_2.push_back(new SetPrice(107504.00));
		prd_2.push_back(new SetQuantity(16));
		prd_2.push_back(new SetMass(117.984));
		cont.push_back(prd_2);

		vector<Command*> prd_3;
		prd_3.push_back(new CreateProduct("Стальная труба"));
		prd_3.push_back(new SetDiameter(10));
		prd_3.push_back(new SetLength(2000));
		prd_3.push_back(new SetPrice(8832.00));
		prd_3.push_back(new SetQuantity(32));
		prd_3.push_back(new SetMass(13.152));
		cont.push_back(prd_3);

		vector<Command*> prd_4;
		prd_4.push_back(new CreateProduct("Стальная труба"));
		prd_4.push_back(new SetDiameter(100));
		prd_4.push_back(new SetLength(4000));
		prd_4.push_back(new SetPrice(65856.00));
		prd_4.push_back(new SetQuantity(16));
		prd_4.push_back(new SetMass(48.6));
		cont.push_back(prd_4);
	}

	IProduct* order(string name, double_t diameter, double_t length, size_t box = 1)
	{
		size_t i = 0;

		while (i < cont.size() && (cont[i][0]->name != name || cont[i][1]->diam != diameter || cont[i][2]->len != length))
			i++;

		if (i < cont.size() && cont[i][0]->name == name)
		{
			IProduct* prd = new Pipes(name, this->name, "");
			for (auto j : cont[i])
				j->execute(prd);
			prd->setBox(box);

			return prd;
		}
		return nullptr;
	}
	string getName()
	{
		return name;
	}

};
