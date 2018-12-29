#include<iostream>
#include"Object.hpp"

using namespace std;
using namespace my;

class Tree : public Object
{
public:
	Tree(Object* parent = nullptr) : Object(parent){}
	~Tree()
	{
		cout << "~Tree destructor" << endl;
	}
};

class Apple : public Object
{
public:
	Apple(int id, Object* parent = nullptr) : Object(parent), id(id) {}
	~Apple()
	{
		cout << "~Apple number " << id <<  " destructor" << endl;
	}
private:
	int id{ 0 };
};

int main(int argc, char** argv)
{
	system("chcp 1251");
	system("cls");

	{
		Tree tree;
		Apple* app1 = new Apple(1, &tree);
		Apple* app2 = new Apple(2, &tree);
		Apple* app3 = new Apple(3, &tree);
	}

	system("pause");
	return 0;
}