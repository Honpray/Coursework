#include <stdio.h>
#include <Python.h>

int main(int argc, char **argv) {
	char *key = "18oxkrFKQqETnOmNAx0y2SrPGH0LMOrvVZQsFpxPvKO8";
	
	PyObject *pModuleString, *pModule, *pGc, *pA1, *pCellArg, *pCellFunc, *pWks, *pSh, *pKeyArg, *pOpenkeyFunc, *pEmptyArg, *pAuthFunc;

	Py_Initialize();
	
	pModuleString = PyString_FromString((char *)"pygsheets");
	if (!pModuleString) {
		PyErr_Print();
		puts("Error formating python script");
	}
	pModule = PyImport_Import(pModuleString);
	if (!pModule) {
		PyErr_Print();
		puts("Error importing");
	}

	pAuthFunc = PyObject_GetAttrString(pModule, (char *)"authorize");
	if (!pAuthFunc) {
		PyErr_Print();
		puts("Error authorizing");
	}
	pEmptyArg  = Py_BuildValue("()");
	if (!pEmptyArg) {
		PyErr_Print();
		puts("Error pEmptyArg");
	}
	
	pGc = PyEval_CallObject(pAuthFunc, pEmptyArg);
	if (!pGc) {
		PyErr_Print();
		puts("Error pGc");
	}
	pOpenkeyFunc = PyObject_GetAttrString(pGc, (char *)"open_by_key");
	if (!pOpenkeyFunc) {
		PyErr_Print();
		puts("Error authorizing");
	}

	pKeyArg = Py_BuildValue("(s)", key);
	if (!pKeyArg) {
		PyErr_Print();
		puts("Error pKeyArg");
	}
	
	pSh = PyEval_CallObject(pOpenkeyFunc, pKeyArg);
	if (!pSh) {
		PyErr_Print();
		puts("Error pSh");
	}
	pWks = PyObject_GetAttrString(pSh, (char *)"sheet1");
	if (!pWks) { 
		PyErr_Print();
		puts("Error pWks");
	}
	pCellArg = Py_BuildValue("(s)", "A1");
	if (!pCellArg) {
		PyErr_Print();
		puts("Error pCellArg");
	}
	pCellFunc = PyObject_GetAttrString(pWks, (char *)"get_value");
	if (!pCellFunc) {
		PyErr_Print();
		puts("Error pCellFunc");
	}
	pA1 = PyEval_CallObject(pCellFunc, pCellArg);
	if (!pA1) {
		PyErr_Print();
		puts("Error pA1");
	}
	
	char *output;
	PyArg_Parse(pA1, "s", &output);

	puts(output);
	Py_Finalize();
	return 0;
}
