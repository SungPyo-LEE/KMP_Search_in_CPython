#include <Python.h>
#include <numpy/arrayobject.h>
#include <math.h>
#include <string.h>
#include <stdio.h>

void Preprocess(char* Pattern, int PatternSize);
double KMP(char* Text, int TextSize, int Start, char* Pattern, int PatternSize);
