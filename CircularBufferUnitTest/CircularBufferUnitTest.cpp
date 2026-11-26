#include "gtest/gtest.h"
#include "../CircularBufferLib/CircularBuffer.h"

TEST(CircularBuffer, ConstructorSizeOne)
{
	CircularBuffer<int, 1> buf;
	ASSERT_EQ(size_t{ 0 }, buf.size());
}
TEST(CircularBuffer, ConstructorSize10)
{
	CircularBuffer<int, 10> buf;
	ASSERT_EQ(size_t{ 0 }, buf.size());
}
TEST(CircularBuffer, pushAndPopSize1NotExceedSize)
{
	CircularBuffer<int, 1> buf;

	ASSERT_TRUE(buf.push(43));
	ASSERT_EQ(size_t{ 1 }, buf.size());
	int v;
	ASSERT_TRUE(buf.pop(v));
	ASSERT_EQ(43, v);
	ASSERT_EQ(size_t{ 0 }, buf.size());
}
TEST(CircularBuffer, pushAndPopSize5NotExceedSize)
{
	CircularBuffer<int, 5> buf;

	ASSERT_TRUE(buf.push(23));
	ASSERT_TRUE(buf.push(4));
	ASSERT_TRUE(buf.push(6));
	ASSERT_TRUE(buf.push(12));
	ASSERT_TRUE(buf.push(91));
	ASSERT_EQ(size_t{ 5 }, buf.size());
	int v;
	ASSERT_TRUE(buf.pop(v));
	ASSERT_EQ(23, v);
	ASSERT_TRUE(buf.pop(v));
	ASSERT_EQ(4, v);
	ASSERT_TRUE(buf.pop(v));
	ASSERT_EQ(6, v);
	ASSERT_TRUE(buf.pop(v));
	ASSERT_EQ(12, v);
	ASSERT_TRUE(buf.pop(v));
	ASSERT_EQ(91, v);
}
TEST(CircularBuffer, pushAndPopSize1ExceedSize)
{
	CircularBuffer<int, 1> buf;

	ASSERT_TRUE(buf.push(2));
	ASSERT_FALSE(buf.push(7));
	ASSERT_EQ(size_t{ 1 }, buf.size());
	int v;
	ASSERT_TRUE(buf.pop(v));
	ASSERT_EQ(2, v);
	ASSERT_EQ(size_t{ 0 }, buf.size());
}
TEST(CircularBuffer, pushAndPopSize3ExceedSize)
{
	CircularBuffer<int, 3> buf;

	ASSERT_TRUE(buf.push(2));
	ASSERT_TRUE(buf.push(7));
	ASSERT_TRUE(buf.push(15));
	ASSERT_FALSE(buf.push(34));
	ASSERT_EQ(size_t{ 3 }, buf.size());
	int v;
	ASSERT_TRUE(buf.pop(v));
	ASSERT_EQ(2, v);
	ASSERT_TRUE(buf.pop(v));
	ASSERT_EQ(7, v);
	ASSERT_TRUE(buf.pop(v));
	ASSERT_EQ(15, v);
	ASSERT_EQ(size_t{ 0 }, buf.size());
}
TEST(CircularBuffer, popFromSize1EmptyBuffer)
{
	CircularBuffer<int, 1> buf;
	int v;
	ASSERT_FALSE(buf.pop(v));
}
TEST(CircularBuffer, popFromSize3EmptyBuffer)
{
	CircularBuffer<int, 3> buf;
	int v;
	ASSERT_FALSE(buf.pop(v));
}
TEST(CircularBuffer, pushPopIntoEmpty)
{
	CircularBuffer<int, 5> buf;
	ASSERT_TRUE(buf.push(5));
	ASSERT_EQ(size_t{ 1 }, buf.size());
	int v;
	ASSERT_TRUE(buf.pop(v));
	ASSERT_EQ(5, v);
	ASSERT_EQ(size_t{ 0 }, buf.size());
}
TEST(CircularBuffer, pushPopArroundIntoEmpty)
{
	int v;
	CircularBuffer<int, 5> buf;
	ASSERT_TRUE(buf.push(4));
	ASSERT_TRUE(buf.push(3));
	ASSERT_TRUE(buf.pop(v));
	ASSERT_TRUE(buf.pop(v));

	ASSERT_TRUE(buf.push(5));
	ASSERT_EQ(size_t{ 1 }, buf.size());

	ASSERT_TRUE(buf.pop(v));
	ASSERT_EQ(5, v);
	ASSERT_EQ(size_t{ 0 }, buf.size());
}
TEST(CircularBuffer, pushPopIntoNotEmpty)
{
	CircularBuffer<int, 5> buf;
	ASSERT_TRUE(buf.push(5));
	ASSERT_TRUE(buf.push(3));
	ASSERT_TRUE(buf.push(7));
	int v;
	ASSERT_EQ(size_t{ 3 }, buf.size());
	ASSERT_TRUE(buf.pop(v));
	ASSERT_EQ(5, v);
	ASSERT_EQ(size_t{ 2 }, buf.size());
	ASSERT_TRUE(buf.pop(v));
	ASSERT_EQ(3, v);
	ASSERT_EQ(size_t{ 1 }, buf.size());
	ASSERT_TRUE(buf.pop(v));
	ASSERT_EQ(7, v);
	ASSERT_EQ(size_t{ 0 }, buf.size());
}
TEST(CircularBuffer, pushPopArroundIntoNotEmpty)
{
	int v;
	CircularBuffer<int, 5> buf;
	ASSERT_TRUE(buf.push(9));
	ASSERT_TRUE(buf.push(5));
	ASSERT_TRUE(buf.pop(v));
	ASSERT_TRUE(buf.push(3));
	ASSERT_TRUE(buf.push(7));
			
	ASSERT_EQ(size_t{ 3 }, buf.size());
	ASSERT_TRUE(buf.pop(v));
	ASSERT_EQ(5, v);
	ASSERT_EQ(size_t{ 2 }, buf.size());
	ASSERT_TRUE(buf.pop(v));
	ASSERT_EQ(3, v);
	ASSERT_EQ(size_t{ 1 }, buf.size());
	ASSERT_TRUE(buf.pop(v));
	ASSERT_EQ(7, v);
	ASSERT_EQ(size_t{ 0 }, buf.size());
}
TEST(CircularBuffer, pushPopWillBecomeFull)
{
	CircularBuffer<int, 4> buf;
	ASSERT_TRUE(buf.push(5));
	ASSERT_TRUE(buf.push(3));
	ASSERT_TRUE(buf.push(7));
	ASSERT_TRUE(buf.push(4));
	int v;
	ASSERT_EQ(size_t{ 4 }, buf.size());
	ASSERT_TRUE(buf.pop(v));
	ASSERT_EQ(5, v);
	ASSERT_EQ(size_t{ 3 }, buf.size());
	ASSERT_TRUE(buf.pop(v));
	ASSERT_EQ(3, v);
	ASSERT_EQ(size_t{ 2 }, buf.size());
	ASSERT_TRUE(buf.pop(v));
	ASSERT_EQ(7, v);
	ASSERT_EQ(size_t{ 1 }, buf.size());
	ASSERT_TRUE(buf.pop(v));
	ASSERT_EQ(4, v);
	ASSERT_EQ(size_t{ 0 }, buf.size());
}
TEST(CircularBuffer, pushPopArroundWillBecomeFull)
{
	int v;
	CircularBuffer<int, 4> buf;
	ASSERT_TRUE(buf.push(5));
	ASSERT_TRUE(buf.push(3));
	ASSERT_TRUE(buf.push(5));
	ASSERT_TRUE(buf.pop(v));
	ASSERT_TRUE(buf.pop(v));
	ASSERT_TRUE(buf.push(3));
	ASSERT_TRUE(buf.push(7));
	ASSERT_TRUE(buf.push(4));

	ASSERT_EQ(size_t{ 4 }, buf.size());
	ASSERT_TRUE(buf.pop(v));
	ASSERT_EQ(5, v);
	ASSERT_EQ(size_t{ 3 }, buf.size());
	ASSERT_TRUE(buf.pop(v));
	ASSERT_EQ(3, v);
	ASSERT_EQ(size_t{ 2 }, buf.size());
	ASSERT_TRUE(buf.pop(v));
	ASSERT_EQ(7, v);
	ASSERT_EQ(size_t{ 1 }, buf.size());
	ASSERT_TRUE(buf.pop(v));
	ASSERT_EQ(4, v);
	ASSERT_EQ(size_t{ 0 }, buf.size());
}
TEST(CircularBuffer, pushIntoFull)
{
	CircularBuffer<int, 4> buf;
	ASSERT_TRUE(buf.push(5));
	ASSERT_TRUE(buf.push(2));
	ASSERT_TRUE(buf.push(8));
	ASSERT_TRUE(buf.push(4));
	ASSERT_EQ(size_t{ 4 }, buf.size());

	ASSERT_FALSE(buf.push(7));
}
TEST(CircularBuffer, pushArroundIntoFull)
{
	int v;
	CircularBuffer<int, 4> buf;
	ASSERT_TRUE(buf.push(5));
	ASSERT_TRUE(buf.push(2));
	ASSERT_TRUE(buf.push(8));
	ASSERT_TRUE(buf.pop(v));
	ASSERT_TRUE(buf.push(4));
	ASSERT_TRUE(buf.push(5));
	ASSERT_EQ(size_t{ 4 }, buf.size());

	ASSERT_FALSE(buf.push(7));
}
TEST(CircularBuffer, popFromEmpty)
{
	int v;
	CircularBuffer<int, 4> buf;
	ASSERT_FALSE(buf.pop(v));
}
TEST(CircularBuffer, popArroundFromEmpty)
{
	int v;
	CircularBuffer<int, 4> buf;
	ASSERT_TRUE(buf.push(5));
	ASSERT_TRUE(buf.push(2));
	ASSERT_TRUE(buf.push(8));
	ASSERT_TRUE(buf.pop(v));
	ASSERT_TRUE(buf.pop(v));
	ASSERT_TRUE(buf.pop(v));
	ASSERT_EQ(size_t{ 0 }, buf.size());

	ASSERT_FALSE(buf.pop(v));
}
