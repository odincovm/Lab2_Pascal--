#pragma once
#include <string>
using namespace std;
class HierarchicalList {
	struct Node {
		Node* parent = nullptr;
		Node* child = nullptr;
		Node* Next = nullptr;
		Node* Last = nullptr;
		string value;
		Node(string val) { value = val; }
	};
	class myIterator{
	protected:
		Node* itr;
	public:
		bool operator!=(Node* tmp);
		bool operator==(Node* tmp);
		void inc();
		void dec();
		Node* getitr() { return itr; }
		string getvalue() { return itr->value; }
	};
	myIterator iter;
	Node* HList;
public:
	void remove(string n);
	void insert(string n);
	void insertAsChild(string n);
	//find - устанавливает итератор на элемент с значением n  
	void find(string n);




};