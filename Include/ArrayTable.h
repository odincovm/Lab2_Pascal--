#pragma once
#include <vector>
#include <string>
using namespace std;
template <typename T>
class ArrayTable
{
	struct record {
		string name;
		bool is_const;
		T value;
		record(string n, bool c, T v) { name = n; is_const = c, value = v; }
	};
	vector<record> table;
	size_t size = 0;
public:
	void insert(string n, bool c, T v);
	void change(string n, T value);
	void remove(string n);
	size_t getsize() { return size; }
	T* find(string n);
};


