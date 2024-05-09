#include <gtest.h>

#include<ArrayTable.cpp>

TEST(Table, can_create) {
	ASSERT_NO_THROW(ArrayTable<int> tmp);
}
TEST(Table, can_insert) {
	ArrayTable<int> tmp;
	tmp.insert("a", true, 12);
	EXPECT_EQ(1, tmp.getsize());
}
TEST(Table, cant_be_dublicate) {
	ArrayTable<int> tmp;
	tmp.insert("a", true, 12);
	tmp.insert("a", true, 12);
	EXPECT_EQ(1, tmp.getsize());
}
TEST(Table, can_find) {
	ArrayTable<int> tmp;
	tmp.insert("a", true, 12);
	EXPECT_NE(nullptr,tmp.find("a"));
}
TEST(Table, can_change) {
	ArrayTable<int> tmp;
	int ans;
	tmp.insert("a", false, 12);
	tmp.change("a", 40);
	ans = (int)*tmp.find("a");
	EXPECT_EQ(40, ans);
}
TEST(Table, cant_change_const) {
	ArrayTable<int> tmp;
	int ans;
	tmp.insert("a", true, 12);
	ASSERT_ANY_THROW(tmp.change("a", 40));
}

TEST(Table, can_remove) {
	ArrayTable<int> tmp;
	tmp.insert("a", true, 12);
	tmp.remove("a");
	EXPECT_EQ(0, tmp.getsize());
}