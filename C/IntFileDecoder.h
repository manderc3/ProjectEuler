/**
 * Integer File Decoder Module
 *
 * Written by Christopher Mander (http://github.com/manderc3)
 **/

#pragma once	

struct DecodedFile {
	int length;
	int height;
	int** arr;
};

/**
 * Get the length and height of rows and columns in a file (file must have uniform row lengths
 * and column heights.)
 *
 * getHeight depends on getLength's return value as a tradeoff for efficiency.
 **/
int getLength(FILE* f);
int getHeight(FILE* f, const int height);

/**
 * For decoding provided file into multidimensional array. Returns array upon success, NULL otherwise.
 **/
int** decodeFile(FILE* f, const int length, const int height);

/**
 * Interface for above functions. It is the reponsibility of the caller to deallocate the returned
 * struct from the heap. Returns NULL pointer upon allocation failure.
 **/
struct DecodedFile* dStructInit(char* path);