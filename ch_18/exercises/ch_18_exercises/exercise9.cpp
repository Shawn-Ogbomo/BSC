//Consider the memory layout in §17.4.Write a program that tells the order
//in which static storage, the stack, and the free store are laid out in memory.
//In which direction does the stack grow : upward toward higher addresses
//or downward toward lower addresses ? In an array on the free store, are
//elements with higher indices allocated at higher or lower addresses ?

//stack grows down towards lower addresses and heap grows upwards towards higher addresses

#include <array>
#include <vector>
#include <iostream>
#include <algorithm>

const auto g1 = 1;
const auto g2 = 2;
const auto g3 = 3;

static auto display_memory_layout(int v1, int v2, int v3, const std::array<int, 3>& vals_s, const std::vector<int>& vals_h)
{
	std::cout << "vals static\n"
		<< &v1 << " " << &v2 << " " << &v3 << "\n";

	std::cout << "\nvals stack\n\n";

	std::for_each(vals_s.begin(), vals_s.end(), [](const auto& target) {
		std::cout << &target << " ";
		});

	std::cout << "\n\nvals heap\n\n";
	std::for_each(vals_h.begin(), vals_h.end(), [](const auto& internal_target) {
		std::cout << &internal_target << " ";
		});
}

int main()
{
	auto vals_stack = std::array<int, 3> { 1, 2, 3 };

	auto vals_heap = std::vector<int>{ 1,2,3 };

	display_memory_layout(g1, g2, g3, vals_stack, vals_heap);

	std::cout << "\n";
}