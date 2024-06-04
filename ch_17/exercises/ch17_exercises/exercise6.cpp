//This chapter does not say what happens when you run out of memory
//using new.That’s called memory exhaustion.Find out what happens.You have
//two obvious alternatives : look for documentation, or write a program with
//an infinite loop that allocates but never deallocates.Try both.Approximately
//how much memory did you manage to allocate before failing ?

//results in bad_alloc exception
//bad alloc is a type of exception thrown by allocation functions to report failure to allocate storage.
// 113.7gb allocated before bad_alloc
#include <iostream>

int main() {
	while (true)
	{
		new int[100000000];
	}
}