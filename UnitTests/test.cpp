#include "pch.h"
#include "../Array.h"

TEST(ArrayTests, DefaultConstructor_CapacityEqualsDefaultCapacity) 
{
	Array<int> arr = Array<int>();
	ASSERT_EQ(arr.capacity(), STARTING_CAPACITY);
}

TEST(ArrayTests, CapacityConstructor_IncorectCapacity_CapacityEqualsDefaultCapacity) 
{
	Array<int> arr = Array<int>(-1);
	ASSERT_EQ(arr.capacity(), STARTING_CAPACITY);
}

TEST(ArrayTests, CapacityConstructor_CorectCapacity_CapacityEqualsSpecifiedCapacity) 
{
	Array<int> arr = Array<int>(1);
	ASSERT_EQ(arr.capacity(), 1);
}

TEST(ArrayTests, CopyConstructor_ArrayGetsCopied) 
{
	Array<int> arr = Array<int>();
	arr.insert(1);
	Array<int> copy(arr);
	copy.insert(2);
	ASSERT_EQ(arr[0], copy[0]);
	ASSERT_NE(arr.size(), copy.size());
}

TEST(ArrayTests, CopyAssignment_ArrayGetsCopied) 
{
	Array<int> arr = Array<int>();
	arr.insert(1);
	Array<int> copy;
	copy = arr;
	copy.insert(2);
	ASSERT_EQ(arr[0], copy[0]);
	ASSERT_NE(arr.size(), copy.size());
}

TEST(ArrayTests, Insert_CapacityIncreaseNotNeeded) 
{
	Array<int> arr = Array<int>();
	arr.insert(1);
	arr.insert(2);
	ASSERT_EQ(arr[0], 1);
	ASSERT_EQ(arr[1], 2);
}

TEST(ArrayTests, Insert_CapacityIncreaseNeeded) 
{
	Array<int> arr = Array<int>(2);
	arr.insert(1);
	arr.insert(2);
	ASSERT_EQ(arr.capacity(), 2);
	arr.insert(3);
	ASSERT_EQ(arr.capacity(), (int)(2 * CAPACITY_INCREASE_COEF));
	ASSERT_EQ(arr[0], 1);
	ASSERT_EQ(arr[1], 2);
	ASSERT_EQ(arr[2], 3);
}

TEST(ArrayTests, InsertAt_CapacityIncreaseNotNeeded) 
{
	Array<int> arr = Array<int>();
	arr.insert(0, 1);
	arr.insert(0, 2);
	ASSERT_EQ(arr[0], 2);
	ASSERT_EQ(arr[1], 1);
}

TEST(ArrayTests, InsertAt_ComplexObject_CapacityIncreaseNotNeeded)
{
	Array<std::string> arr = Array<std::string>();
	arr.insert(0, "1");
	arr.insert(0, "2");
	ASSERT_EQ(arr[0], "2");
	ASSERT_EQ(arr[1], "1");
}

TEST(ArrayTests, InsertAt_CapacityIncreaseNeeded) 
{
	Array<int> arr = Array<int>(2);
	arr.insert(0, 1);
	arr.insert(0, 2);
	ASSERT_EQ(arr.capacity(), 2);
	arr.insert(1, 3);
	ASSERT_EQ(arr.capacity(), (int)(2 * CAPACITY_INCREASE_COEF));
	ASSERT_EQ(arr[0], 2);
	ASSERT_EQ(arr[1], 3);
	ASSERT_EQ(arr[2], 1);
}

TEST(ArrayTests, InsertAt_IncorrectIndex) 
{
	Array<int> arr = Array<int>();
	arr.insert(0, 1);
	arr.insert(-1, 2);
	ASSERT_EQ(arr[0], 1);
	ASSERT_EQ(arr[1], 2);
}

TEST(ArrayTests, Remove_ShiftingNotNeeded) 
{
	Array<int> arr = Array<int>();
	arr.insert(1);
	arr.insert(2);
	arr.insert(3);
	arr.remove(2);
	ASSERT_EQ(arr.size(), 2);
}

TEST(ArrayTests, Remove_ShiftingNeeded) 
{
	Array<int> arr = Array<int>();
	arr.insert(1);
	arr.insert(2);
	arr.insert(3);
	arr.remove(1);
	ASSERT_EQ(arr.size(), 2);
	ASSERT_EQ(arr[1], 3);
}

TEST(ArrayTests, Iterator_ForwardIterationCorrect) 
{
	Array<int> arr = Array<int>();
	arr.insert(1);
	arr.insert(2);
	arr.insert(3);
	arr.insert(4);
	int i = 1;
	for (auto iter = arr.iterator(); iter.hasNext(); iter.next(), i++)
		ASSERT_EQ(iter.get(), i);
}

TEST(ArrayTests, ReverseIterator_ReverseIterationCorrect) 
{
	Array<int> arr = Array<int>();
	arr.insert(1);
	arr.insert(2);
	arr.insert(3);
	arr.insert(4);
	int i = 4;
	for (auto iter = arr.reverseIterator(); iter.hasNext(); iter.next(), i--)
		ASSERT_EQ(iter.get(), i);
}

TEST(ArrayTests, CopyConstructor_ComplexObjectsGetsCopied) 
{
	Array<std::string> arr = Array<std::string>();
	arr.insert(std::to_string(1));

	Array<std::string> copy(arr);

	ASSERT_NE(arr[0].c_str(), copy[0].c_str());
}

TEST(ArrayTests, CopyAssignment_ComplexObjectsGetsCopied) 
{
	Array<std::string> arr = Array<std::string>();
	arr.insert(std::to_string(1));

	Array<std::string> copy;
	copy = arr;

	ASSERT_NE(arr[0].c_str(), copy[0].c_str());
}