#include "pch.h"
#include "Dungeon.h"

TEST(TestCaseName, TestName) {
	Dungeon D(3);
	D.read_levels();
	//D.save_levels();
	D.read_saved_levels();
	ASSERT_EQ(D.get_levels()[1].get_enemies().size(), 0);
}