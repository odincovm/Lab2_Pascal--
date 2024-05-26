#pragma once

#include "../Include/HierarchicalList.h"
#include <vector>
#include <String>
using namespace std;
class SyntacsisControler
{
	HierarchicalList program;
public:
	SyntacsisControler() {}
	SyntacsisControler(HierarchicalList pr) { program = pr; }

	void check() {
		NotFoundProgram();
		NotFoudKeyWord();
		NotFoundProgramName();
		checkdatatype();
		checkvariablenames();
		checkcantchangeconst();
		checkNoExtraneousOperations();
	}
private:
	// Программы нет
	void NotFoundProgram() {
		if (program.getsize() == 0)
			throw "Program not found";
	}
	// Нет названия программы
	void NotFoundProgramName() {
		program.find("Program");
		if (!program.havechild()) {
			throw "Not found name";
		}
		program.back();
	}
	// Нет ключевых слов
	void NotFoudKeyWord() {
		program.find("Program");
		if (program.get() != "Program")
			throw "Not found key word Program";
		program.find("var");
		if (program.get() != "var")
			throw "Not found key word var";
		program.find("begin");
		if (program.get() != "begin")
			throw "Not found key word begin";
		program.find("end.");
		if (program.get() != "end.")
			throw "Not found key word end";
		program.back();
	}
	// Корректность объявления ( наличие в команде поддерживаемого типа данных)
	void checkdatatype() {
		bool flag;
		program.find("const");
		if (program.get() == "const") {
			program.inc();
			while (program.get() != "var") {
				flag = true;
				vector<string> type{ "integer","double","string" };
				string tmp;
				for (int i = 0; i < type.size(); i++) {
					tmp = program.get();
					if (tmp.find(type[i]) != std::string::npos) {
						flag = false;
					}
				}
				if (flag)
					throw "Unknown data type";
				program.inc();
			}
		}
		program.find("var");
		program.inc();
		while (program.get() != "begin") {
			flag = true;
			vector<string> type{ "integer","double","string" };
			string tmp;
			for (int i = 0; i < type.size(); i++) {
				tmp = program.get();
				if (tmp.find(type[i]) != std::string::npos) {
					flag = false;
				}
			}
			if (flag)
				throw "Unknown data type";
			program.inc();
		}
	}
	// Нахождение имени констант
	vector<string> constname() {
		program.find("const");
		vector<string> names;
		string comand;
		string name;
		if (program.get() == "const") {
			program.inc();
			while (program.get() != "var") {
				comand = program.get();
				name = "";
				for (int i = 0; i < comand.size(); i++) {
					if (comand[i] == ',') {
						names.push_back(name);
						name = "";
					}
					if (comand[i] == ':') {
						names.push_back(name);
						break;
					}
					if (comand[i] != ' ') {
						name += comand[i];
					}
				}
				program.inc();
			}
		}
		return names;
	}
	// Нахождение имени переменных
	vector<string> varname() {
		program.find("const");
		vector<string> names;
		string comand;
		string name;
		program.find("var");
		program.inc();
		while (program.get() != "begin") {
			comand = program.get();
			name = "";
			for (int i = 0; i < comand.size(); i++) {
				if (comand[i] == ',') {
					names.push_back(name);
					name = "";
				}
				else
					if (comand[i] == ':') {
						names.push_back(name);
						break;
					}
					else
						if (comand[i] != ' ') {
							name += comand[i];
						}
			}
			program.inc();
		}
		return names;
	}
	// Проверка имени переменных (не начинается с цифры и не пустое)
	void checkvariablenames() {
		vector<string> constant = constname();
		vector<string> var = varname();
		char tmp;
		for (int i = 0; i < constant.size(); i++) {
			if (constant[i].size() == 0)
				throw "Const name empty";
			for (int j = 0; j < 10; j++) {
				tmp = (char)(((int)'0') + j);
				if (constant[i][0] == tmp)
					throw "The name of a constant cannot begin with a digit";
			}
		}
		for (int i = 0; i < var.size(); i++) {
			if (var[i].size() == 0)
				throw "Variable name empty";
			for (int j = 0; j < 10; j++) {
				tmp = (char)(((int)'0') + j);
				if (var[i][0] == tmp)
					throw "The name of a variable cannot begin with a digit";
			}
		}
	}
	// Проверка на то, что нельзя изменить константу
	void checkcantchangeconst() {
		vector<string> constant = constname();
		program.find("begin");
		program.inc();
		while (program.get() != "end.")
		{
			if (program.get().find(":=") != std::string::npos) {
				for (int i = 0; i < constant.size(); i++) {
					if (program.get().find(constant[i]) != std::string::npos)
						throw "Cant change const";
				}
			}
			program.inc();
		}
	}
	// Проверка на то, что в строке есть операция
	void checkNoExtraneousOperations() {
		vector<string> oper{ ":=","Write","Read","if","then","begin","end","else" };
		bool flag;
		program.find("begin");
		program.inc();
		while (program.get() != "end.") {
			flag = true;
			for (int i = 0; i < oper.size(); i++) {
				if (program.get().find(oper[i]) != std::string::npos)
					flag = false;
			}
			if (flag)
				throw "Operation not found";
		}
	}
};

