1.  What does Caveat emptor! mean?
    let the buyer beware.
2.  What is the default meaning of copying for class objects?
    copy all members
3.  When is the default meaning of copying of class objects appropriate? When is it inappropriate?”
    appropriate for object
    unsuitable for pointer-members since resources are shared. Results in double free
4.  What is a copy constructor?
    constructor that copies an object. Invoked when initializing an object with another.

5.  What is a copy assignment?
    copies all the values from the target object to the source using = operator

6.  What is the difference between copy assignment and copy initialization?
    copy assignment is invoked when operator = is used
    copy initialization is invoked when {} is used

7.  What is shallow copy? What is deep copy?
    Shallow copy- used by pointer and references; the objects are shared
    Deep copy- all resources are copied from the target object to the source object.
    both objects are managing resources in distinct memory locations

8.  How does the copy of a vector compare to its source?
    its resources are distinct in memory

9.  What are the five “essential operations” for a class?
    .construction
    .default constructor
    .copy constructor
    .copy assignment
    .destructor

10. What is an explicit constructor? Where would you prefer one over the (default) alternative?
    a constructor marked explicit. safeguards against implicit conversions.

11. What operations may be invoked implicitly for a class object?
    Constructor
    conversion operators
    destructor

12. What is an array?
    a series objects allocated in contiguous memory

13. How do you copy an array?
    operator =
    deep copy the members into the source
14. How do you initialize an array?
    with {} syntax (uniform initialization)

15. When should you prefer a pointer argument over a reference argument? Why?
    When referring to multiple nullable objects
    references only refer to one object

16. What is a C-style string?
    zero-terminated string
    array of characters

17. What is a palindrome?
    a value reading the same from left and right
