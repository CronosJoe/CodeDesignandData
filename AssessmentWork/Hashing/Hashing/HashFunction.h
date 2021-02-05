#pragma once
#include <functional>
#include <cstdint>

template<typename T>
uint32_t hash(const T& val);

template<>
uint32_t hash<uint32_t>(const uint32_t &val) //function from the sharepoint, that number below looks super random
{
	return val * 2654435761;//unsigned int hashing
}
template<>
uint32_t hash<int>(const int &val)//int hashing
{
	return hash((uint32_t)val);
}
template<>
uint32_t hash<char>(const char &val)//char hashing
{
	return hash((uint32_t)val);
}
template<>
uint32_t hash<bool>(const bool &val)//bool hashing
{
	return hash((uint32_t)val);
}
template<>
uint32_t hash<short>(const short& val)//short hashing
{
	return hash((uint32_t)val);
}
template<>
uint32_t hash<long>(const long& val)//long hashing
{
	return hash((uint32_t)val);
}
template<size_t N>
uint32_t hash(char const (&string)[N])
{
	uint32_t returnVal = 0; //this will be used to add it all together
	for(int x = 0; x<N;++x) //iterate through the string
	{
		toReturn ^= hash((char)string[x]);
	}
	return returnVal;
}
