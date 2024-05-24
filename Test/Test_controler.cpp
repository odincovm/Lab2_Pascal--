

#include <../Include/HierarchicalList.h>
#include <gtest.h>
#include <SyntacsisControler.h>

TEST(Controler, AssertWhenEmpty) {
	HierarchicalList tmp;
	SyntacsisControler synt(tmp);
	ASSERT_ANY_THROW(synt.check());
}
TEST(Controler, AssertWhenNoKeyWord) {
	HierarchicalList tmp;
	tmp.first("Program");
	//tmp.insert("var");
	tmp.insert("begin");
	tmp.insert("end");
	SyntacsisControler synt(tmp);
	ASSERT_ANY_THROW(synt.check());
}

TEST(Controler, AssertWhenNoProgramName) {
	HierarchicalList tmp;
	tmp.first("Program");
	tmp.insert("var");
	tmp.insert("begin");
	tmp.insert("end.");
	SyntacsisControler synt(tmp);
	ASSERT_ANY_THROW(synt.check());
}
TEST(Controler, AssertWhenWrongDataType) {
	HierarchicalList tmp;
	tmp.first("Program");
	tmp.insertAsChild("My program;");
	tmp.dec();
	tmp.insert("var");
	tmp.find("var");
	tmp.insertAsChild("num1, num2: vector;");
	tmp.dec();
	tmp.insert("begin");
	tmp.find("begin");
	tmp.insert("end.");
	SyntacsisControler synt(tmp);
	ASSERT_ANY_THROW(synt.check());
}
TEST(Controler, AssertWhenWrongName) {
	HierarchicalList tmp;
	tmp.first("Program");
	tmp.insertAsChild("My program;");
	tmp.find("Program");
	tmp.insert("const");
	tmp.find("const");
	tmp.insertAsChild("tmp: integer;");
	tmp.find("const");
	tmp.insert("var");
	tmp.find("var");
	tmp.insert("begin");
	tmp.insertAsChild("tmp := 5;");
	tmp.dec();
	tmp.insert("end.");
	SyntacsisControler synt(tmp);
	ASSERT_ANY_THROW(synt.check());
}
TEST(Controler, AssertWhenWrongOperand) {
	HierarchicalList tmp;
	tmp.first("Program");
	tmp.insertAsChild("My program;");
	tmp.find("Program");
	tmp.insert("const");
	tmp.find("const");
	tmp.insertAsChild("tmp: integer;");
	tmp.find("const");
	tmp.insert("var");
	tmp.find("var");
	tmp.insert("begin");
	tmp.insertAsChild("printf();");
	tmp.dec();
	tmp.insert("end.");
	SyntacsisControler synt(tmp);
	ASSERT_ANY_THROW(synt.check());
}