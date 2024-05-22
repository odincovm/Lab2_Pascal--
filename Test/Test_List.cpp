#include<gtest.h>


#include <../Include/HierarchicalList.cpp>

TEST(List, can_create) {
	HierarchicalList tmp;
	ASSERT_NO_THROW(HierarchicalList tmp);
}
TEST(List, can_insert) {
	HierarchicalList tmp;
	tmp.first("Program");
	tmp.insertAsChild("My_program");
}