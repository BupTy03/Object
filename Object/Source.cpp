#include<iostream>
#include"Object.hpp"

using namespace std;
using namespace my;

class Tree : public Object
{
public:
	Tree(Object* parent = nullptr) : Object(parent){}
	void printTree() const { cout << "Hello, I'm Tree!" << endl; }
	virtual Tree* clone() override { return new Tree(this->parent_); }
	~Tree() { cout << "~Tree destructor" << endl; }
};

class Apple : public Object
{
public:
	Apple(int id, Object* parent = nullptr) : Object(parent), id(id) {}
	void printApple() const { cout << "Hello, I'm Apple " << id << endl; }
	virtual Apple* clone() override { return new Apple(id, this->parent_); }
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
		Object parent;
		Tree* tree = new Tree(&parent);
		Apple* app1 = new Apple(1, tree);
		Apple* app2 = new Apple(2, tree);
		Apple* app3 = new Apple(3, tree);
		Apple* apple = app3->clone();
		apple->printApple();
		Tree* tree2 = tree->clone();
	}

	system("pause");
	return 0;
}