#PASCALTR: Pascal's Triangle generator
My first C project! This is a simple program that prints a Pascal's Triangle with a given number of lines to the terminal. Developing this made me learn the ins-and-outs of C string handling, as well as a bit about data types. The code is pure C89 with no dependencies beyond the standard library so it should work on anything, but I did all the development work on a DOS system with MS C 6.0.

##Known issues
* Only works up to n = 12; beyond that the factorial function overflows the unsigned long int. Would probably have to use floats to go beyond that.
* Needs to check maximum n for a given terminal width. Currently just segfaults if it goes over the hardcoded 80-col limit.
* Cell size is hardcoded to 3, which is fine for the current n = 12 limit but would need to be dynamic to maintain formatting beyond that.
* Might be fun to give it a curses UI or GUI
