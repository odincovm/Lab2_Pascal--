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
		Node(string val) { value = val; parent = nullptr, child = nullptr, Next = nullptr, Last = nullptr;}
		Node() { parent = nullptr; child = nullptr; Next = nullptr; Last = nullptr; }
	};
	class myIterator{
	friend class HierarchicalList;
	protected:
		Node* itr;
	public:
		bool operator!=(Node* tmp);
		bool operator==(Node* tmp);
		void operator=(Node* tmp);
		void inc();
		void dec();
		Node* getitr() { return itr; }
		string getvalue() { return itr->value; }
	};
	//
	Node* HList;
	myIterator iter;
	
public:
	HierarchicalList() {
		Node tmp("Program");
		HList = &tmp;
		iter = HList;
	}
	Node* getiter() { return iter.getitr(); }
	void first(string n) {
		Node tmp(n);
		iter.itr = &tmp;
	}
	void remove(string n);
	void insert(string n);
	void insertAsChild(string n) {
		Node t(n);
		Node* tmp = &t;
		if (iter.itr->child == nullptr) {
			iter.itr->child = tmp;
			tmp->parent = iter.itr;
		}
	}
	//find - устанавливает итератор на элемент с значением n  
	void find(string n);
	string get() { return iter.getvalue(); }



};