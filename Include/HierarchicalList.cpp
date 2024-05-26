#pragma once
#include "HierarchicalList.h"

//Итератор
inline bool HierarchicalList::myIterator::operator!=(Node* tmp)
{
	if (itr = tmp)
		return true;
	return false;
}

inline bool HierarchicalList::myIterator::operator==(Node* tmp)
{
	if (itr!=tmp)
		return false;
	return true;
}

inline void HierarchicalList::myIterator::operator=(Node* tmp)
{
	itr = tmp;
}


inline void HierarchicalList::myIterator::inc()
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
inline void HierarchicalList::myIterator::next()
{
	if (itr->Next != nullptr) {
		itr = itr->Next;
		return;
	}
}

inline void HierarchicalList::myIterator::dec()
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
inline void HierarchicalList::remove(string n)
{
	find(n);

	if (iter.itr->value == n) {
		size--;
		if (iter.itr->parent == nullptr) {
			iter.dec();
			
			iter.itr->Next = nullptr;
		}
		else {
			if (iter.itr->Last != nullptr) {
				iter.dec();
			
				iter.itr->Next = nullptr;
			}
			else {
				iter.dec();
			
				iter.itr->child = nullptr;
			}
		}
	}
	
}

inline void HierarchicalList::insert(string n)
{
	Node* tmp = new Node(n);
	if (iter.itr->Next == nullptr) {
		size++;
		iter.itr->Next = tmp;
		tmp->Last = iter.itr;
		tmp->parent = iter.itr->parent;
		iter.inc();
	}

}



inline void HierarchicalList::find(string n)
{
	myIterator tmp;
	tmp.itr = HList;
	while ((tmp.itr->child != nullptr)||(tmp.itr->Next!=nullptr)||(tmp.itr->parent!=nullptr)) {
		if (tmp.getvalue() == n) {
			iter.itr = tmp.itr;
			return;
		}
		tmp.inc();
	}
	if (tmp.getvalue() == n) {
		iter.itr = tmp.itr;
		return;
	}
}
