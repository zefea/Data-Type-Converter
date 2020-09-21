# Data-Type-Converter

In this project firstly it takes,  
- a file containing signed integers, unsigned integers and floating point numbers
- the byte ordering type (Little Endian or Big Endian),
- the size of the floating point data type (the size of both signed and unsigned integers are 2 bytes),
as input and converts the contents of the file to hexadecimal according to the predefined
format and gives the converted data as output.

The size of the data type can be 1, 2, 3 or 4 bytes.

- The signed integers are written as normal integers in the file. (e.g., 3, -5, etc.)
- The unsigned integers are written as integers followed by the letter u. (e.g., 3u, 5u,etc.)
- The floating point numbers are written with a decimal point. (e.g., 3.0, 5.987, etc.)
- If the read data type is signed integer, program will convert the numbers in the input file using 2’s complement representation.
- If the read data type is unsigned integer, numbers will be converted using unsigned integer representation.
- If the read type is floating point number, IEEE-like format is used. The number of exponent bits according to given data size will be like the following:

- if 1 byte (i.e., 8 bits), 4 bits will be used for exponent part
- if 2 bytes (i.e., 16 bits), 6 bits will be used for exponent part
- if 3 bytes (i.e., 24 bits), 8 bits will be used for exponent part
- if 4 bytes (i.e., 32 bits), 10 bits will be used for exponent part

While calculating the mantissa to get the floating point value, only use the first 13 bits of the fraction part (for 3-byte and 4-byte data sizes) is used. Program
uses “round to nearest even” method for rounding fraction bits to 13 bits.
