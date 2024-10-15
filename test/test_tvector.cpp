#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
	ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
	ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
	ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector)
{
	TDynamicVector<int> v(10);

	ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
	TDynamicVector<int> v(10);
	TDynamicVector<int> v1(v);

	EXPECT_EQ(v1, v);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
	TDynamicVector<int> v(10);
	TDynamicVector<int> v1(v);

	v1[5] = 4;
	EXPECT_NE(v1[5], v[5]);
}

TEST(TDynamicVector, can_get_size)
{
	TDynamicVector<int> v(4);

	EXPECT_EQ(4, v.size());
}

TEST(TDynamicVector, can_set_and_get_element)
{
	TDynamicVector<int> v(4);
	v[0] = 4;

	EXPECT_EQ(4, v[0]);
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
	TDynamicVector<int> v(4);

	EXPECT_ANY_THROW(v.at(-1) = 243);
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
	TDynamicVector<int> v(4);
	EXPECT_ANY_THROW(v.at(4) = 243);
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
	TDynamicVector<int> v(4);
	v[0] = 534;
	v = v;
	EXPECT_EQ(v[0], 534);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
	int* s = new int[4] {123, 534, 756, 3};
	TDynamicVector<int> v1(4), v2(s , 4);
	v1 = v2;

	EXPECT_EQ(v1, v2);

}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
	TDynamicVector<int> v1(2), v2(4);
	v1 = v2;

	EXPECT_EQ(v1.size(), 4);
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
	int* s = new int[4] {123, 534, 756, 3};
	TDynamicVector<int> v1(2), v2(s, 4);
	v1 = v2;

	EXPECT_EQ(v1, v2);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
	int* s = new int[4] {123, 534, 756, 3};
	TDynamicVector<int> v1(4), v2(s, 4);
	for (int i = 0; i < 4; i++) v1[i] = s[i];

	EXPECT_EQ(v1, v2);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
	int* s = new int[4] {123, 534, 756, 3};
	TDynamicVector<int> v2(s, 4);

	EXPECT_EQ(v2, v2);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
	int* s = new int[4] {123, 534, 756, 3};
	TDynamicVector<int> v1(3), v2(s, 4);
	for (int i = 0; i < 3; i++) v1[i] = s[i];

	EXPECT_NE(v1, v2);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
	int* s = new int[4] {123, 534, 756, 3};
	TDynamicVector<int> v1(4), v2(s, 4);
	for (int i = 0; i < 4; i++) v1[i] = s[i] + 4;
	v2 = v2 + 4;

	EXPECT_EQ(v1, v2);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
	int* s = new int[4] {123, 534, 756, 3};
	TDynamicVector<int> v1(4), v2(s, 4);
	for (int i = 0; i < 4; i++) v1[i] = s[i] - 4;
	v2 = v2 - 4;

	EXPECT_EQ(v1, v2);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
	int* s = new int[4] {123, 534, 756, 3};
	TDynamicVector<int> v1(4), v2(s, 4);
	for (int i = 0; i < 4; i++) v1[i] = s[i] * 7;
	v2 = v2 * 7;

	EXPECT_EQ(v1, v2);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
	int* s = new int[4] {123, 534, 756, 3};
	TDynamicVector<int> v1(4), v2(s, 4);
	for (int i = 0; i < 4; i++) v1[i] = s[i] * 7;

	TDynamicVector<int> v3 = v1 + v2;
	TDynamicVector<int> v4(4);
	for (int i = 0; i < 4; i++) v4[i] = s[i] * 8;

	EXPECT_EQ(v3, v4);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
	int* s = new int[4] {123, 534, 756, 3};
	TDynamicVector<int> v1(3), v2(s, 4);
	for (int i = 0; i < 3; i++) v1[i] = s[i] * 7;

	EXPECT_ANY_THROW(v1 + v2);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
	int* s = new int[4] {123, 534, 756, 3};
	TDynamicVector<int> v1(4), v2(s, 4);
	for (int i = 0; i < 4; i++) v1[i] = s[i] * 7;

	TDynamicVector<int> v3 = v1 - v2;
	TDynamicVector<int> v4(4);
	for (int i = 0; i < 4; i++) v4[i] = s[i] * 6;

	EXPECT_EQ(v3, v4);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
	int* s = new int[4] {123, 534, 756, 3};
	TDynamicVector<int> v1(3), v2(s, 4);
	for (int i = 0; i < 3; i++) v1[i] = s[i] * 7;

	EXPECT_ANY_THROW(v1 - v2);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
	int* s = new int[4] {123, 534, 756, 3};
	TDynamicVector<int> v1(4), v2(s, 4);
	for (int i = 0; i < 4; i++) v1[i] = i + 1;

	int mult = v1 * v2;
	int check = 0;
	for (int i = 0; i < 4; i++) check += (i + 1) * s[i];

	EXPECT_EQ(check, mult);

}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
	int* s = new int[4] {123, 534, 756, 3};
	TDynamicVector<int> v1(3), v2(s, 4);
	for (int i = 0; i < 3; i++) v1[i] = i + 1;

	ASSERT_ANY_THROW(v1 * v2);
}

