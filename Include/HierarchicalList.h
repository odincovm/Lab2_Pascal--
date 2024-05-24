#pragma once
#include <string>
using namespace std;
class HierarchicalList {
	struct Node {
		Node* parent;
		Node* child;
		Node* Next;
		Node* Last;
		string value=" ";
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
		string getvalue() { 
			return itr->value; 
		}
	};
	//
	Node* HList;
	myIterator iter;
	int size = 0;
	
public:
	HierarchicalList() {
		HList = nullptr;
	}
	Node* getiter() { return iter.getitr(); }
	void first(string n) {
		size++;
		Node* tmp = new Node(n);
		HList = tmp;
		iter.itr = HList;
	}
	void back() {
		iter.itr = HList;
	}
	int getsize() { return size; }
	void inc() { iter.inc(); }
	void dec() { iter.dec(); }
	bool havechild() { return iter.itr->child != nullptr; }
	void remove(string n);
	void insert(string n);
	void insertAsChild(string n) {
		Node* tmp = new Node(n);
		if (iter.itr->child == nullptr) {
			size++;
			iter.itr->child = tmp;
			tmp->parent = iter.itr;
			inc();
		}
	}
	//find - устанавливает итератор на элемент с значением n  
	void find(string n);
	string get() { return iter.getvalue(); }



};