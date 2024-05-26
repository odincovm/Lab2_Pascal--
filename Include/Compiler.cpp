#include "Compiler.h"
#include "HierarchicalList.h"
#include "ArrayTable.h"
#include "ArrayTable.cpp"
#include "SyntacsisControler.h"
#include <vector>
#include <map>
#include "HierarchicalList.cpp"

Compiler::Compiler(const string& inputFile) :
	inputFile(inputFile)
{}

void Compiler::compile() {
	parse();
	generateMachineCode();
}

vector<string> parseString(string code) {
	// Разделение строки на лексические единицы
	vector<string> tokens;
	string token;
	for (int i = 0; i < code.length(); i++) {
		if (code[i] == ':' && code[i + 1] == '=') {
			tokens.push_back(":=");
			i++; i++;
		}
		if (code[i] == '(') {
			if (!token.empty()) {
				tokens.push_back(token);
				token.clear();
			}
			tokens.push_back("(");
			i++;
		}
		if (code[i] == ')') {
			if (!token.empty()) {
				tokens.push_back(token);
				token.clear();
			}
		}
		if (code[i] == ' ' || code[i] == '\t' || code[i] == ',') {
			if (!token.empty()) {
				tokens.push_back(token);
				token.clear();
			}
		}
		else if (code[i] == '/' && code[i+1] == '/') {
			return tokens;
		}
		else if (code[i] == ';') {
			if (!token.empty()) {
				tokens.push_back(token);
				token.clear();
				tokens.push_back(";");
				i++;
			}
		}
		else if (code[i] == '"')
		{
			i++;
			while (code[i] != '"') {
				token += code[i];
				i++;
			}
		}
		else {
			token += code[i];
		}
	}
	if (!token.empty()) {
		tokens.push_back(token);
	}
	return tokens;
}

void Compiler::parse() {
	// Чтение кода из файла и создание иерархического списка
	string code;
	vector<string> Parents;
	string lastParent;
	while (getline(inputFile, code)) {
		vector<string> tokens;
		tokens = parseString(code);
		// Добавление лексических единиц в иерархический список
		int i = 0;
		if (!tokens.empty()) {
			while (i < tokens.size()) {
				if (tokens[i] == "Program") {
					program.first(tokens[i]);
					i++;
					Parents.push_back("Program");
					program.insertAsChild(tokens[i]);
					lastParent = "Program";
					i++;
					while (tokens[i] != ";" && i < tokens.size()) {
						program.insert(tokens[i]);
						i++;
					}
				}
				else if (tokens[i] == "const") {
					program.find(Parents.back());
					program.insert(tokens[i]);
					i++;
					Parents.push_back("const");
					lastParent = "const";
					if (i < tokens.size()) {
						program.insertAsChild(tokens[i]);
						i++;

						while (tokens[i] != ";" && i < tokens.size()) {
							program.insert(tokens[i]);
							i++;
						}
					}
				}
				else if (tokens[i] == "var") {
					program.find(Parents.back());
					program.insert(tokens[i]);
					Parents.push_back("var");
					lastParent = "var";
					i++;
					if (i < tokens.size()) {
						program.insertAsChild(tokens[i]);
						i++;

						while (tokens[i] != ";" && i < tokens.size()) {
							program.insert(tokens[i]);
							i++;
						}
					}
				}
				else if (tokens[i] == "begin") {
					program.find(Parents.back());
					program.insert(tokens[i]);
					if (program.havechild()) {
						while (program.get() != lastParent) {
							program.next();
						}
						if(program.havechild())
							program.inc();
						while (program.haveNext()) {
							program.next();
						}
					}
					Parents.push_back("begin");
					lastParent = "begin";
					tokens = parseString(code);
				}
				else if (tokens[i] == "Write" || tokens[i] == "Read") {
					program.find(Parents.back());
					if (program.havechild()) {
						program.inc();
						while (program.haveNext()) {
							program.next();
						}
					}
					program.insert(tokens[i]);
					program.find(tokens[i]);
					while (program.haveNext()) {
						program.next();
					}
					i++;
					if (lastParent == "begin") {
						program.insertAsChild(tokens[i]);
						i++;
					}
					while (tokens[i] != ";" && i < tokens.size()) {
						program.insert(tokens[i]);
						i++;
					}
				}
				else if (tokens[i] == "end" || tokens[i] == "end.") {
					Parents.pop_back();
				}
				else if (tokens[i] == "if") {
					program.find(Parents.back());
					Parents.push_back("if");
					lastParent = "if";
					if (program.havechild()) {
						program.inc();
						while (program.haveNext()) {
							program.next();
						}
					}
					program.insert(tokens[i]);
					program.find(lastParent);
				}
				else if (tokens[i] == "(") {
					program.find(lastParent);
					program.insertAsChild(tokens[i++]);
					program.insertAsChild(tokens[i++]);
					while (tokens[i] != ")") {
						program.insert(tokens[i++]);
					}
					program.insert(tokens[i++]);
					program.find(lastParent);
					program.inc();
					while (program.haveNext()) {
						program.next();
					}
					program.insert(tokens[i]);
				}
				else if (tokens[i] == "else") {
					program.find(Parents.back());
					Parents.pop_back();
					program.insert(tokens[i]);
					Parents.push_back("else");
				}
				else {
					program.find(Parents.back());
					if (program.havechild()) {
						program.inc();
						while (program.haveNext()) {
							program.next();
						}
						while (tokens[i] != ";" && i < tokens.size()) {
							program.insert(tokens[i]);
							i++;
						}
					}
					else {
						lastParent = Parents.back();
						while (program.haveNext()) {
							program.inc();
						}
						program.insertAsChild(tokens[i]);
						i++;
						if (lastParent == "begin") {
							program.insertAsChild(tokens[i]);
							i++;
						}
						while (tokens[i] != ";" && i < tokens.size()) {
							program.insert(tokens[i]);
							i++;
						}
					}
				}
				i++;
			}
		}
	}

	// Проверка синтаксиса
	SyntacsisControler syntacsis(program);
	syntacsis.check();

	ctrl = program;
}

void Compiler::generateMachineCode() {
	// Обход иерархического списка и генерация машинного кода
	program.first("Program");
	program.inc();
	ArrayTable<int> ints;
	ArrayTable<double> doubles;

	while (program.get() != "end.") {
		// Обработка различных конструкций языка
		if (program.get() == "const") {
			// Обработка констант
			program.inc();
			while (program.get() != "var") {
				string name = program.get();
				string type = program.get();
				double value = stod(program.get());

				if (type == "integer") {
					ints.insert(name, true, static_cast<const int>(value));
				}
				else if (type == "double") {
					doubles.insert(name, true, value);
				}

				program.inc();
			}
		}
		else if (program.get() == "var") {
			// Обработка переменных
			program.inc();
			while (program.get() != "begin") {
				string name = program.get();
				string type = program.get();
				if (type == "integer") {
					ints.insert(name, false, NULL);
				}
				else if (type == "double") {
					doubles.insert(name, false, NULL);
				}
			}
		}
		else if (program.get() == "begin") {
			// Обработка операторов
			program.inc();
			while (program.get() != "end.") {
				if (program.get().find(":=") != string::npos) {
					// Обработка присваивания
					string name = program.get().substr(0, program.get().find(":="));
					string expression = program.get().substr(program.get().find(":=") + 2);
					//
					//Код сюда
					//
				}
				else if (program.get() == "Write") {
					// Обработка вывода
					program.inc();
					string output = program.get();
					cout << output << endl;
					a:
					if (program.haveNext()) {
						program.inc();
						if (ints.find(program.get())){
							cout << ints.find(program.get());
						}
						else if(doubles.find(program.get())) {
							cout << doubles.find(program.get());
						}
					}   
					goto a;
				}
				else if (program.get() == "Read") {
					// Обработка ввода
					program.inc();
					string name = program.get();
					if (ints.find(name)) {
						int tmp;
						cin >> tmp;
						ints.change(name, tmp);
					}
					else if (doubles.find(name)) {
						double tmp;
						cin >> tmp;
						doubles.change(name, tmp);
					}

				}

				else if (program.get() == "if") {
					// Обработка условных операторов
					program.inc();
					string condition = program.get();
					// Генерация машинного кода для условных операторов
					// Например:
					// LOAD condition
					// JUMP_IF_FALSE label
					// ...
					// label:
				}
				program.inc();
			}
		}
		program.inc();
	}
}


//Program (Parent)
//	Example (child)
//const (Next parent)
//	Pi (child)
//	double	(child)
//	3.1415926		(child)
//var	(Next parent)
//	num1		(child)
//	integer	(child)
//	num2		(child)
//	integer	(child)
//	Res		(child)
//	double	(child)
//	d			(child)
//	double	(child)
//begin			(Next parent)
//	num1		(child)
//	: =		(child)
//	5			(child)
//	Write		(child of begin new Parent)
//			"Введите четное целое число: "	(child)
//	Read		(child of begin new Parent)
//			num2	(child)
//	Write		(child of begin new Parent)
//			"Введите вещественное число: " (child)
//	Read		(child of begin new Parent)
//			d	(child)
//	if		(child of begin new Parent)
//			(	(child of if new Parent)
//				b	(child of '(' )
//				mod	(child of '(' )
//				2	(child of '(' )
//				=	(child of '(' )
//				0	(child of '(' )
//				)	(child of '(' )
//			then	(child of if new parent )
//				begin	(child of then new parent )
//					Res	(child of begin )
//					: =	(child of begin )
//					(	(child of begin new parent )
//						num1	(child of '(' )
//						-		(child of '(' )
//						num2	(child of '(' )
//						*		(child of '(' )
//						5		(child of '(' )
//						div		(child of '(' )
//						2		(child of '(' )
//						)		(child of '(' )
//					/	(child of begin )
//					(	(child of begin new parent)
//						d	(child of '(' )
//						*	(child of '(' )
//						2	(child of '(' )
//						)	(child of '(' )
//			Write	(child of if new Parent)
//				"Результат = "	(child)
//				Res				(child)
//			end					(child of if)
//	else				(child of begin new parent)
//			Write				(child of if)
//	      "Неверный ввод"		(child of if)
//	end.	(child of begin, end of the list)