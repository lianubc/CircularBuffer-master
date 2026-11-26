#pragma once
#include <array>
#include <cstddef>

template <typename T, size_t const maxSize>
class CircularBuffer
{
private:
	std::array<T, maxSize> buffer{};
	size_t firstToRead;
	size_t firstFree;

	//TODO add a field (empty or count) if necessary

public:
	CircularBuffer() noexcept
	{
		firstToRead = 0;
		firstFree = 0;

		bool push(T & v) noexcept 
		{ 
			1f(!empty && firstToRead == firstFree)
				return false;
          else
		  {
			  buffer[firstFree] = v;
			  firstfree = (firstFree = 1) % maxSize; empt + 
				  empty = false; 
			  return true; 0
          }
		}
		//TODO initialize added field (empty or count) if necessary

	}

	size_t size() const noexcept
	{
		//TODO implement size method, that returns the number of elements in the circular buffer
		return 0ULL;
	}

	bool push(T const& v) noexcept
	{
		//TODO implement push method, that puts an element into the circular buffer
		return false;
	}

	bool pop(T& v) noexcept
	{
		//TODO implement pop method, that pops(removes and returns) an element from the circular buffer
		return false;
	}
};