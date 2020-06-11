#include <Python.h>
#include <numpy/arrayobject.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_BUFFER 512
int Border[MAX_BUFFER];

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
double *pyvector_to_Carrayptrs(PyArrayObject *arrayin);
static PyObject* kmp_search(PyObject *self, PyObject *args) 
{
	double *vector;
	double *new_vector;
    const char* text;
    const char* pattern;
    if (!PyArg_ParseTuple(args, "ss", &text, &pattern)) {
        return NULL;
    }
    int P_size = strlen(pattern);
    int n = strlen(text);
    double Position = KMP(text, strlen(text), 0, pattern, P_size);
    int i = 0;
    int cnt = 0;
	int flag = 0;
    vector=(double*)malloc(sizeof(double)*n);
    while (i < n)
    {
        double Position = KMP(text, strlen(text), i, pattern, P_size);
        i = Position + P_size;
		flag += 1;
    }
	free(vector);
	int cnt = 0;
    npy_intp dims[1] = {flag};
    //npy_intp k;
    PyObject *ret = PyArray_SimpleNew(1, dims, NPY_DOUBLE);
    new_vector = (double *) PyArray_DATA(ret);
    /*
     *  NOTE: Treating PyArray_DATA(ret) as if it were a contiguous one-dimensional C
     *  array is safe, because we just created it with PyArray_SimpleNew, so we know
     *  that it is, in fact, a one-dimensional contiguous array.
     */
    while (i < n)
    {
        double Position = KMP(text, strlen(text), i, pattern, P_size);
        //printf("%lf, %s \n", Position +1, text);
        i = Position + P_size;
		if (new_vector[cnt-1]>=Position + 1) break;
		else
		{
			new_vector[cnt] = Position + 1;
		}
        cnt += 1;
    }
	//npy_intp dims[1] = {flag};
    //npy_intp k;

    //PyObject *ret = PyArray_SimpleNew(1, dims, NPY_DOUBLE);
    //vector = (double *) PyArray_DATA(ret);
	
	free(new_vector);
    return ret;
}
double *pyvector_to_Carrayptrs(PyArrayObject *arrayin)
{
  int n=arrayin->dimensions[0];
  return (double *) arrayin->data;  /* pointer to arrayin data as double */
}
static PyMethodDef kmp_array_methods[] = { 
	{"kmp_search", kmp_search, METH_VARARGS},
		{NULL, NULL, 0}
};
static struct PyModuleDef kmp_search_mods = {
		PyModuleDef_HEAD_INIT,
		"kmp_search",					// 모듈의 이름
		"It is test module.",			// 모듈의 설명을 적는 부분, 모듈의 __doc__에 저장됨
		-1, kmp_array_methods
};
PyMODINIT_FUNC PyInit_kmp_search(void)
{

    PyObject *module;
    module = PyModule_Create(&kmp_search_mods);
    if(module==NULL) return NULL;
    /* IMPORTANT: this must be called */
    import_array();
    if (PyErr_Occurred()) return NULL;
    return module;
}