#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>
#include <numeric>
#include <fstream>
using namespace std;

class car
{
	string name;
	int year;
	int engine;
	int price;
public:
	car(string mark, int year , int engine , int price)
	{
		this->name = mark;
		this->year = year;
		this->engine = engine;
		this->price = price;
	}
	car()
	{
		name = "";
		year = 0;
		price = 0;
		engine = 0;
	}
	int get_year() const { return year; };
	int get_engine() const { return engine; };
	int get_price() const { return price; };
	string get_name() const { return name; };
	void set_year(int year) { this->year = year; };
	void set_engine(int engine) { this->engine = engine; };
	void set_price(int price) { this->price = price; };
	void set_name(string mark) { this->name = mark; };
	void print()
	{
		cout << "Mark : " << name << endl;
		cout << "Year : " << year << endl;
		cout << "Engine : " << engine << " litres" << endl;
		cout << "Price : " << price << '$'<<endl;
	}
	friend istream& operator>>(istream& is , car& c);
	friend ostream& operator<<(ostream& os, const car& c);
};
istream& operator>>(istream& is, car& c)
{
	string mark;
	int y, e, p;
	is >> mark >> y >> e >> p;
	c.set_name(mark);
	c.set_year(y);
	c.set_engine(e);
	c.set_price(p);
	return is;
}
ostream& operator<<(ostream& os, const car& c)
{
	os << c.get_name() << " " << c.get_year() << " " << c.get_engine() << " " << c.get_price() << endl;
	return os;
}
class functor_name
{
	string name;
public:
	functor_name(string name)
	{
		this->name = name;
	}
	functor_name()
	{
		this->name = "";
	}
	bool operator()(const car& c)
	{
		if (c.get_name() == name)
			return true;
		return false;
	}
	void set_name(string value)
	{
		this->name = value;
	}
};
class functor_year
{
	int year;
public:
	functor_year(int year)
	{
		this->year = year;
	}
	functor_year()
	{
		this->year = 0;
	}
	bool operator()(const car& c)
	{
		if (c.get_year() == year)
			return true;
		return false;
	}
	void set_year(int year)
	{
		this->year = year;
	}
};
class functor_price
{
	int value;
public:
	functor_price(int value)
	{
		this->value = value;
	}
	functor_price()
	{
		this->value = 0;
	}
	bool operator()(const car& c)
	{
		if (c.get_price() == value)
			return true;
		return false;
	}
	void set_price(int value)
	{
		this->value = value;
	}
};
class functor_engine
{
	int value;
public:
	functor_engine(int value)
	{
		this->value = value;
	}
	functor_engine()
	{
		this->value = 0;
	}
	bool operator()(const car& c)
	{
		if (c.get_engine() == value)
			return true;
		return false;
	}
	void set_engine(int value)
	{
		this->value = value;
	}
};
bool predicat1(const car& c1, const car& c2)
{
	return c1.get_name() < c2.get_name();
}
bool predicat2(const car& c1 , const car& c2)
{
	return c1.get_price() < c2.get_price();
}
bool predicat3(const car& c1, const car& c2)
{
	return c1.get_year() < c2.get_year();
}
bool predicat4(const car& c1, const car& c2)
{
	return c1.get_engine() < c2.get_engine();
}
int main()
{
	fstream f;
	f.open("file.txt");
	if (!f.is_open())
	{
		cerr << "File wasn't found :( " << endl;
		throw(4);
	}
	car tmp;
	vector <car> garage;
	while (f >> tmp)
	{
		garage.push_back(tmp);
	}
	f.close();
	int choice = 1;
	int sub_menu_choice = 1;
	string name;
    int engine, year, price;
	functor_name f1;
	functor_price f2;
	functor_year f3;
	functor_engine f4;
	do
	{
		cout << "0 - Exit\n1 - Show data\n2 - Add car\n3 - Delete car\n4 - Sort\n5 - Search\nEnter your choice : ";
		cin >> choice;
		system("cls");
		switch (choice)
		{
		case 0:
		{
			cout << "Exiting..." << endl;
			system("pause");
			break;
		}
		case 1:
		{
			for (size_t i = 0; i < garage.size(); i++)
			{
				garage[i].print();
				cout << endl;
			}
			system("pause");
			break;
		}
		case 2:
		{
			cout << "Input car's name : ";
			cin >> name;
			cout << "Input car's development year : ";
			cin >> year;
			cout << "Input engine's volume : ";
			cin >> engine;
			cout << "Input car's price : ";
			cin >> price;
			garage.push_back(car(name, year, engine, price));
			system("pause");
			break;
		}
		case 3:
		{
			cout << "Input car's name : ";
			cin >> name;
			f1.set_name(name);
			auto it = remove_if(garage.begin(), garage.end(), f1);
			garage.erase(it , garage.end());
			system("pause");
			break;
		}
		case 4:
		{
			system("cls");
			do {
				cout << "0 - Back\n1 - Sort by names\n2 - Sort by price\n3 - Sort by year\n4 - Sort by engine volume\nEnter your choice : ";
				cin >> sub_menu_choice;
				switch (sub_menu_choice)
				{
				case 0:
				{
					system("cls");
					cout << "Going back to menu..." << endl;
					break;
				}
				case 1:
				{
					system("cls");
					sort(garage.begin(), garage.end(), predicat1);
					cout << "Sorting Done!" << endl;
					break;
				}
				case 2:
				{
					system("cls");
					sort(garage.begin(), garage.end(), predicat2);
					cout << "Sorting Done!" << endl;
					break;
				}
				case 3:
				{
					system("cls");
					sort(garage.begin(), garage.end(), predicat3);
					cout << "Sorting Done!" << endl;
					break;
				}
				case 4:
				{
					system("cls");
					sort(garage.begin(), garage.end(), predicat4);
					cout << "Sorting Done!" << endl;
					break;
				}
				}
				system("pause");
				system("cls");
			} while (sub_menu_choice != 0);
			break;
		}
		//
		
		case 5:
		{
			system("cls");
			do {
				cout << "0 - Back\n1 - Find by name\n2 - Find by price\n3 - Find by year\n4 - Find by engine volume\nEnter your choice : ";
				cin >> sub_menu_choice;
				switch (sub_menu_choice)
				{
				case 0:
				{
					system("cls");
					cout << "Going back to menu..." << endl;
					break;
				}
				case 1:
				{
					cout << "Input name to search : ";
					cin >> name;
					f1.set_name(name);
					auto it = find_if(garage.begin(), garage.end(), f1);
					system("cls");
					it->print();
					break;
				}
				case 2:
				{
					cout << "Input price to search : ";
					cin >> price;
					f2.set_price(price);
					system("cls");
					auto it = find_if(garage.begin(), garage.end(), f2);
					it->print();
					break;
				}
				case 3:
				{
					cout << "Input year to search : ";
					cin >> year;
					f3.set_year(year);
					system("cls");
					auto it = find_if(garage.begin(), garage.end(), f3);
					it->print();
					break;
				}
				case 4:
				{
					cout << "Input engine's vloume to search : ";
					cin >> engine;
					f4.set_engine(engine);
					system("cls");
					auto it = find_if(garage.begin(), garage.end(), f4);
					it->print();
					break;
				}
				}
				system("pause");
				system("cls");
			} while (sub_menu_choice != 0);
			break;
		}
		}
		
		system("cls");
	} while (choice != 0);
	f.open("file.txt");
	if (!f.is_open())
	{
		cerr << "File wasn't found :( " << endl;
		throw(4);
	}
	for (size_t i = 0; i < garage.size(); i++)
	{
		f << garage[i];
	}
}

