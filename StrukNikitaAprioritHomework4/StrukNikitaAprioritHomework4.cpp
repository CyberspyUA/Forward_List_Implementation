/**
 * OS: Windows 10
 * IDE: MS Visual Studio 2022
 * C++ Standard: ISO 2017
 * Compiler: MSVC C++
 */
#include <iostream>
#include "LinkedList.h"

template <typename T>
void PrintList(LinkedList<T> list);

int main()
{
	LinkedList list {1, 2, 3, 5, 12, 42, 142, 542};
	list.push_front(5.5);
	std::cout << " Original list size: " << list.getSize() <<"\n";

	std::cout << "Original list: ";
    for (auto iter = list.begin(); iter != list.end(); ++iter)
    {
	    std::cout << *iter << " ";
    }
    std::cout << "\n";

	auto list2 = list.split_when([](int value){return value == 42;});

	std::cout << "Splitted list 1: ";
    PrintList(list);

    std::cout << "Splitted list 2: ";
    PrintList(list2);

    list.swap(list2);

    std::cout << "Swapped list 1: ";
    PrintList(list);

    std::cout << "Swapped list 2: ";
    PrintList(list2);

    return 0;
}

/**
 * \brief 
 * \tparam T - тип даних, що зберігає список (data type that stores the list).
 * \param list - список, що зберігає дані (list that stores data).
 */
template <typename T>
void PrintList(LinkedList<T> list)
{
	for (auto iter = list.begin(); iter != list.end(); ++iter)
    {
	    std::cout << *iter << " ";
    }
    std::cout << "\n";
}