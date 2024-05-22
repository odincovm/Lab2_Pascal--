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

void HierarchicalList::myIterator::operator=(Node* tmp)
{
	itr = tmp;
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
	if (iter.itr->value == n) {
		
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

void HierarchicalList::insert(string n)
{

	Node* tmp = new Node(n);

	// Если это 1 элемент
	
	if (iter.itr->Next == nullptr) {
		iter.itr->Next = tmp;
		tmp->Last = iter.itr;
		tmp->parent = iter.itr->parent;
	}

}



void HierarchicalList::find(string n)
{
	myIterator tmp;
	tmp.itr = HList;
	while ((tmp.itr->child != nullptr)||(tmp.itr->Next!=nullptr)) {
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
