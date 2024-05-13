#include "HierarchicalList.h"

//Итератор
bool HierarchicalList::myIterator::operator!=(Node* tmp)
{
	if (itr = tmp)
		return true;
	return false;
}

bool HierarchicalList::myIterator::operator==(Node* tmp)
{
	if (itr!=tmp)
		return false;
	return true;
}


void HierarchicalList::myIterator::inc()
{
	// Когда пустой
	if (itr == nullptr) 
		return;
	//Когда есть дети спуск вниз     
	if (itr->child != nullptr) {
		itr = itr->child;
		return;
		//Шаг впередна этом уровне
	}else if(itr->Next !=nullptr){
		itr = itr->Next;
		return;
	}
	else {
		//Поднимаемся науровень и шаг вперед
		itr = itr->parent;
		itr = itr->Next;
	}
}

void HierarchicalList::myIterator::dec()
{
	//Шаг назад
	if (itr->Last != nullptr) {
		itr = itr->Last;
		// Если пришаге назад у элемента оказались дети,то идем к последнему ребенку
		if (itr->child != nullptr) {
			while (itr->Next != nullptr) {
				itr = itr->Next;
			}
		}
		return;
	}
	else {
		//Поднимаемся на вверх
		if (itr->parent != nullptr) {
			itr = itr->parent;
		}
	}
}
//Список
void HierarchicalList::remove(string n)
{
	find(n);
	Node* tmp = iter.getitr();
	if (tmp->parent == nullptr) {
		iter.dec();
		tmp = iter.getitr();
		tmp->Next = nullptr;
	}
	else {
		if (tmp->Last != nullptr) {
			iter.dec();
			tmp = iter.getitr();
			tmp->Next = nullptr;
		}
		else {
			iter.dec();
			tmp = iter.getitr();
			tmp->child = nullptr;
		}	
	}
}

void HierarchicalList::insert(string n)
{
	Node* tmp;
	tmp->value = n;
	Node* tmp1 = iter.getitr();
	if (tmp1->Next == nullptr) {
		tmp1->Next = tmp;
		tmp->Last = tmp1;
		tmp->parent = tmp1->parent;
	}
}

void HierarchicalList::insertAsChild(string n)
{
	Node* tmp;
	tmp->value = n;
	Node* tmp1 = iter.getitr();
	if (tmp1->child == nullptr) {
		tmp1->child = tmp;
		tmp->parent = tmp1;
	}
}

void HierarchicalList::find(string n)
{
	myIterator tmp = iter;
	while (iter != nullptr) {
		if (iter.getvalue() == n) {
			return;
		}
		iter.inc();
	}
	if (iter == nullptr)
		iter = tmp;
}
