#include<gtest.h>


#include <../Include/HierarchicalList.cpp>

TEST(List, can_create) {
	HierarchicalList tmp;
	ASSERT_NO_THROW(HierarchicalList tmp);
}
TEST(List, can_insert_as_child_and_find) {
	HierarchicalList tmp;
	tmp.first("Program");
	tmp.insertAsChild("My_program");
	tmp.find("My_program");
	EXPECT_EQ("My_program", tmp.get());
}
TEST(List, can_insert_and_find) {
	HierarchicalList tmp;
	tmp.first("Program");
	tmp.insert("My_program");
	tmp.find("My_program");
	EXPECT_EQ("My_program", tmp.get());
}
TEST(List, can_remove) {
	HierarchicalList tmp;
	tmp.first("Program");
	tmp.insertAsChild("My_program");
	tmp.remove("My_program");
	tmp.find("My_program");
	EXPECT_NE("My_program", tmp.get());
}