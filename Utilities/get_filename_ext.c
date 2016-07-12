#include <string.h>

//Returns the extension of a file from the filename
const char *get_filename_ext(const char *filename) {
	const char *dot = strrchr(filename, '.'); //Returns a pointer to the last occurrence of char "." in the string filename
	if(!dot || dot == filename) return "";
	return dot + 1;
}
