// zxbpp.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <windows.h>

#define TARGET "zxbpp.py"
#define PYTHON_DIR "python36"

using namespace std;

string getBaseDir() {
	wchar_t res[MAX_PATH];
	auto copied = GetModuleFileName(NULL, res, MAX_PATH);
	wstring path(res);
	string basename = std::string(path.begin(), path.end());
	string result = ".";

	for (int i = basename.length() - 1; i >= 0; --i) {
		if (basename[i] == '\\')
			return basename.substr(0, i);
	}
	return result;
}


int execLocal(string basedir, int argc, char *argv[]) {
	string python = "\"" + basedir + '\\' + PYTHON_DIR + "\\python.exe\"";
	string script = "\"" + basedir + '\\' + TARGET + "\"";
	auto cmd = python + " " + script;

	for (int i = 1; i < argc; ++i)
		cmd = cmd + " " + "\"" + argv[i] + "\"";
	cmd = "\"" + cmd + "\"";
	//cout << cmd << endl;
	return system(cmd.c_str());
}


int main(int argc, char *argv[])
{
	string basedir = getBaseDir();
	//cout << basedir << endl;
	return execLocal(basedir, argc, argv);
}

