//CH 11 

//Base 8 and base 16 are commonly used to reffer to the content of the memory 

//The value of a byte is expressed as two hexadecimal decimal digits 

//TO say that a number is hexidecimal, prefix 0X
//123 = 0X7B
//0X123 = 291
// Lowercase x can be used to hexidecimal representation also 

//Lowercase a , b , c, d, e, f for hexidecimal digits also
//123 == 0x7b


Octal is base 8 , only 8 Octal digits are needed

0,1,2,3,4,5,6,7

base-8 numbers (octal) are represented starting with a 0 
// 0123 is not the decimal number 123. Instead it is 1*8^2+2*8+3
which is equal to 83 in decimal 


Binary is two digits only 0 and 1 
base 2 numbers (binary) cannot be directly represented as literals 

only base 8, 10, and 16 can be represented as literals
octal , decimal, and hexadecimal

//hexideximal is popular for outputing hardware information
because hexidecimal exactly reprents a 4 bit value 


//terms such as hex and octal that are used to change the behaviour 
of the stream are called manupulators

//std::showbase is a stream manipulator since it changes the behabiour or the stream 
//std::showbase shows the base of the number eg no representation for deximal 
// 0 prefix for octal 
// 0X or 0x for hexadecimal 

//std::noshowbase returns the output to normal 


//What does unsetf() do ? 

//the stream member function unsetf() clears the flag or flags 
//given as argument 

// permits cin to accept various formats without failing 
//dec, oct, hex

//default basic floating-point output formatting manipulators
What is the difference between general, fixed, and scientific 
manipulators? 

//output
general rounds the floating point value 
fixed displays the value as is 
scientific displays the value in scientific notation 

What does defaultfloat do ?
default float resets the stream to default float format 

what is the default precision for defaultfloat format? 
6 digits 

//The floating point rounding rule only applies to floating point values


//default float chooses between fixed and scientific formats 
//to present the user with the 
//most accurate representation of a floating-point 
//value within the precision of the general format
//defaults to 6 total digits

	std::cout << 1234567.89 << "\n"
		<< std::fixed << 1234567.89 << "\n"
		<< std::scientific << 1234567.89 << "\n";

	//SCIENTIFIC OUTPUT FORM WOULD BE THE BEST REPRESENTATION 
	//THE COMPILER CHOOSES THE BEST OUTPUT FORM ON DEFAULT FLOAT 
	//THE COMPILER CANNOT REPRESENT 1234567.89 AS DEFAULT SINCE IT IS MORE THAN 6 DIGITS 


//floating-point precision 
//std::setprecision()

defaultfloat precision is the total number of digits

scientific precision is the total number of digits after the decimal point 

fixed precision is the number of digits after the decimal point

//use default floating point format with precision 6 bt default 
//only use other formats when you need a greater accuracay of the output

//What do scientific and fixed formats allow a programmer to do? 

//scientific and fixed formats allow a program to control the amount of space 
//a value takes up on output

//useful for printing tables etc...


//what are fields 
// fields are the floating point mechanism for integer values 
//using setw()
//works for both ints and strings
//field sizes don't stick 
//fields can also be used for floating point numbers

//What is a file? 
//A file is a representation of what the operating system provides
//A file is a sequence of bytes starting from 0 upward

//What is the bitwise | operator used for in file declarations?
//The bitwise or operator is used to join the file stream open modes 

//Operating systems will typically create a 
//new file for output if the file does not exist
//with the specified file name 


//What is binary I/O ?
//Binary I/O is responsible for copying bytes to and from files from an istream or ostream
//binary I/O is requested by using the binary open mode ios_base::binary
//binary open mode tells the stream not to do anything clever with the bytes 


//Why do we use binary open mode?
//Binary open mode is used when we need something better than the default 
//Binary open mode is also used to tell the stream not to do anything 
//clever with the bytes

//What does the as_bytes function do ? 
//The as_bytes function gets the address of the first byte for an objests
//representation


//Whenever you can, just read and write files from beginning to end 
//That's the easiest and least error-prone way

//Many times, when you feel that you have to make a change to a file,
//the better solution is to produce a new file with the change


//what is positioning in regards to files 
//positioning is selecting a specific place in a file for reading or writing 


//Every file that is open for reading has a read/get position
//and every file that is open for writing has a write/put position

//Only use positioning when you must
//seekp //seekg

//seekp and seekg do not have any run-time checking. Be careful

//what is an istringstream
//an istring stream is an istream that reads from a string

//what is an ostringstream
//an ostringstream is an ostream that stores characters written to it in a string 

//What is an istringstream useful for 
// an istring stream is useful for extracting numeric characters from a string

//what is an ostringstream useful for 
//an ostringstream is usefuil for formatting output for a system
//that required a simple string argument, such as a GUI system

//what are stringstreams generally used for
//stringstreams are generally used when we want to seperate I/O 
//from processing

//what is an istringstream initialized with?
// a string then input operations are used to read the characters from that string 

//what is an ostringstream initialized with?
//an empty string, the empty string is filled using output operations

//what does the isalnum() function do?
// isalnum() determines if the target is a letter or a digit
//use this instead of isdigit amd isalpha

//what is the ss.str() do?
// returns a copy of ss's string

//what does ss.str(s) do?
//sets ss's string to a copy of s

//what is the character \t?
// \t is the tabulation character

//File stream open modes 
ios_base::app append(i.e., add to the end of the file)
ios_base::ate "at end" (open and seek to end)
ios_base::binary binary mode -- beware of system -specific behaviour 
ios_base::in for reading 
ios_base::out for writing 
ios_base::trunc truncate file to 0 length 

//stringstreams can be seen as a mechanism for tailoring I/O to special needs and tastes

//don't use getline if your reason for using it is because we want to do what operator >> cant do. 
//when using getline, we usually need to parse the string after
//if his is the case stick to operator >>


//REVIEW
1. Why is I/O tricky for a programmer
	//I/O is tricky for a programmer since it needs to be parsed

2. What does the notation << hex do?
	//The << hex notation sets the stream state flags to display a character or character sequence as hexidecimal

3. What are hexadecimal numbers used for in computer science why? (come back here)
	//Hexidecimal numbers are used for hardware GUI applications 
	//used to output hardware information
	//Hexidecimal exactly represents a 4 bit value

4. Name some of the options you may want to implement for formatting integer output
	//std::hex
	//std::oct
	//std::dec

5. What is a manupulator? 
	//A manipulator changes the behavioir of the stream
	// eg general, fixed ,scientigic , show_basae, no_show_base

6. What is the prefix for decimal, octal, and hexadecimal
	//deciaml nothing 
	//octal 8
	//hex 0x

7. What is the default output format for floating-point values?
	//the defauly format for floating-point values is default-float
	//6 digits

8. What is a field? 
	// A field is the floating-point mechanisms for integer values
	// fields work with fractional values and strings
	//eg setw function in iomanip header file 

9. Explain what setprecision and setw do 
	//set precision acceots an integer argument which sets the stream out or in to exactyly the integer
	// eg const auto val = 7.1234
	//setpreciasion(4) = 7.123
	// setw sets the stream precision to the provided integreal  value 
	// eg setw(8)
	//sets the max width to 8. If the string has a length of 4, 4 spaes wiill preceed the string. 
	//If the sting has a greater length than the specified width, then the stream formatting will be ignored.

10. What is the purpose of file open modes? 
	// The purpose of file open modes is, to provide additional functionality for orking with files 
	//eg , trunc , binary, ate , in , out , app 

11. Which of the following manupulator does not stick: hex, scientific, setprecision(), showbase, setw?
	//the setw manipulator does not stick 

12. What is the difference between character I/O and binary I/operator
	// the difference between character I/O and binary I/O is 
	//binary I/O tells the stream not to do anything clever with the bytes 
	// binary I/O copies the bytes to and from files from an istream or an ostream
	//binary I/O seperates each sting into a character sequence 
	// eg "shawn" becomes s,h,a,w,n

	//character I/O 
	//permits use of operators 
	//eg >> and  << 
	//default I/O

13. Give an example of when it would probably be beneficial to use a binary file instead of a text file
	// Binary mode could be ideal for when we want to encode the data in the file.  

14. Give two examples where stringstream can be useful
	//string stream can be useful to treat a character as another character 
	// eg treat !@#$% as white space 
	// read a numeric value from a string into a double / int 

15. What is file pocition? 
	// file position lets you choose a specific place in the file for reading and writing

16. What happens if you position a file beyond the end of file? 
	//If you position a file beyond the end if file, you will get undefined behaviour.
	//This undefined behaviour depends on the machines operating system.

17. When would you prefer line-oriented input to type-specific input?
	//line-oriented input is prefered to type specific input when you you want additional seperation characters 
	// eg shawn, smith , lewis , jenny all on seperate lines 
	// if you were to use type specific input using string type, strings operator >> would read the whole line


18. What does isalnum(c) do?
	//isalnum checks if the argument is an alpha numeric. 

TERMS

Binary: file open mode. Binary is also a stream manipulator std::binary. 

character classification: classifying individual characters when reading 
isalnum(), isdigit(), isspace(), ispunct(),isupper(),islower(),etc...

decimal: stream manipulator sets the output mode and input mode to decimal (integeral value)

default float:  stream manipulator. fractional values will only have a maximum of 6 digits

file positioning: moves the file pointer to the specified position for reading or writing

fixed: manipulator displays floating-point values as is

hexadecimal : manipulator takes input as hex, outputs hex value

irregularity: tailering input and output to our needs 
//not treating the input sources the same

line-oriented input: getline 

manipulator: changes behaviour of the stream

nonstandard seperator: treating other characters as a standard seperator 

noshowbase: resets the floating-point format to defualt

octal: numbering system base 8 

output formatting: setw, set precision 

regularity: treating all objects in memory the same, and treating all input sources equivilently
results in maintainable and efficient code

scientific: floating point format. Scientific notation.

setprecision: floating point formater, sets the input and output maxdigits to the provided argument

showbase: floating point formater. Shows the base of the value, decimal , oct , hex 