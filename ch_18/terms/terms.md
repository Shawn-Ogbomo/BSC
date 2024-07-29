_Array_
Indefinite amount of homogenous objects allocated in contiguous memory

_Array Initialization_
Initializing an array with {} list initialization or ={} syntax.
List initialization sets all bytes to a safe state, and permits the array to be initialized with a set of values that are not defaults

_Copy Assignment_
Prevents memory leaks and double deletion. Permits copying of objects by assignment

_Copy Constructor_
constructor that copies.
Assigns all the values of the target const reference object to the current object.
Such a constructor is invoked when initializing an object with another of the same type

_Deep Copy_
Copies what the pointer points to so that the two pointers now refer to distinct objects.

_Default Constructor_
Permits construction of an object without specifying a value, and sets the object to its default state

_Essential Operations_{
Default Constructor
Constructor One or more parameters
Copy Constructor
Copy Assignment
Move Constructor
Move Assignment
Destructor
}

_Explicit Constructors_
Prevent implicit conversions
Primarily used with one argument constructor

_Move Assignment_
Memory efficient. Prevents paltry copying of objects with assignment

_Move Construction_
Prevents paltry copying of objects on construction. Invoked when an object is initialized with another of the same type using std::move

_Palindrome_
A value that reads the same way from the left and right

_Shallow Copy_
Copies only a pointer; both pointers refer to the same object
