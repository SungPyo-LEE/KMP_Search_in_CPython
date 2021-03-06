#include <Python.h>
#include <numpy/arrayobject.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_BUFFER 512

int Border[MAX_BUFFER];
void Preprocess(char* Pattern, int PatternSize);
double KMP(char* Text, int TextSize, int Start, char* Pattern, int PatternSize);

static PyObject* kmp_search(PyObject *self, PyObject *args) 
{
    char *text;
    char *pattern;
    if (!PyArg_ParseTuple(args, "ss", &text, &pattern)) {
        return NULL;
    }
    double *vector;
    int P_size = strlen(pattern);
    int n = strlen(text);
    double Position = KMP(text, strlen(text), 0, pattern, P_size);
    int i = 0;
	int cnt = 0;
    while (i < n)
    {
        double Position = KMP(text, strlen(text), i, pattern, P_size);
        //printf("%lf, %s \n", Position, Text);
		if (Position + P_size > i || i == 0)
		{
			i = Position + P_size;
			cnt += 1;
		}
		else
			break;
    }
	i = 0;
    npy_intp dims[1] = {cnt};
	npy_intp k;
	k = 0;
	PyObject *ret = PyArray_SimpleNew(1, dims, NPY_DOUBLE);
    vector = (double *) PyArray_DATA(ret);
	while (i < n)
    {
        double Position = KMP(text, strlen(text), i, pattern, P_size);
        //printf("%lf, %s \n", Position, Text);
		if (Position + P_size > i || i == 0)
		{
			i = Position + P_size;
			vector[k]=Position;
			k+=1;
		}
		else
			break;
    }

    return ret;
}

static PyMethodDef kmp_array_methods[] = { 
	{"kmp_search", kmp_search, METH_VARARGS},
		{NULL, NULL, 0}
};

static struct PyModuleDef kmp_search_mods = {

		PyModuleDef_HEAD_INIT,

		"nlp_c",					// 모듈의 이름

		"It is test module.",			// 모듈의 설명을 적는 부분, 모듈의 __doc__에 저장됨

		-1, kmp_array_methods

};

PyMODINIT_FUNC PyInit_nlp_c(void)
{
    PyObject *module;
    module = PyModule_Create(&kmp_search_mods);
    if(module==NULL) return NULL;
    /* IMPORTANT: this must be called */
    import_array();
    if (PyErr_Occurred()) return NULL;
    return module;
}

/* KMP Algo header */

void Preprocess(char* Pattern, int PatternSize)
{
	int i = 0;
	int j = -1;
	
	Border[0] = -1;
	while (i < PatternSize)
	{
		while(j>-1 && Pattern[i] != Pattern[j])
            j = Border[j];
        i++;
        j++;

        Border[i] = j;
    }
}

double KMP(char* Text, int TextSize, int Start, char* Pattern, int PatternSize)
{
    int i = Start;
    int j = 0;
    double Position = -1;
    Preprocess(Pattern, PatternSize);

    while(i < TextSize)
    {
        while(j>=0 && Text[i] != Pattern[j])
            j = Border[j];
        i++;
        j++;
        if (j == PatternSize)
        {
            Position = (double)i - (double)j;
            break;
        }
    }
    return Position;
}