#include "ArrayTable.h"

template<typename T>
inline void ArrayTable<T>::insert(string n, bool c, T v)
{
	record tmp(n, c, v);
	if (find(n) == nullptr) {
		table.push_back(tmp);
		size++;
	}
}

template<typename T>
void ArrayTable<T>::change(string n, T value)
{
	for (int i = 0; i < table.size(); i++) {
		if (table[i].name == n) {
			if (table[i].is_const) {
				throw "Can't change const";
			}
		}
	}
	remove(n);
	insert(n, false, value);
}

template<typename T>
void ArrayTable<T>::remove(string n)
{
	vector<record> tmp;
	for (int i = 0; i < table.size(); i++) {
		if (table[i].name != n) {
			tmp.push_back(table[i]);
		}
		else {
			size--;
		}
	}
	table = tmp;
}

template<typename T>
T* ArrayTable<T>::find(string n)
{
	for (int i = 0; i < table.size(); i++) {
		if (table[i].name == n) {
			return &table[i].value;
		}
	}
	return nullptr;
}
