// generic.cpp: define el punto de entrada de la aplicación de consola.

#include <string>
#include <iostream>
#include <windows.h>

#define PYTHON_DIR "python"

using namespace std;

string getBaseDir() {
	wchar_t res[MAX_PATH];
	auto copied = GetModuleFileName(NULL, res, MAX_PATH);
	wstring path(res);
	string basename = std::string(path.begin(), path.end());
	string result = ".";

	for (int i = (int)basename.length() - 1; i >= 0; --i) {
		if (basename[i] == '\\')
			return basename.substr(0, i);
	}
	return result;
}


string getBaseName(string fname) {
	for (int i = (int)fname.length() - 1; i >= 0; --i) {
		if (fname[i] == '\\')
			return fname.substr(i + 1);
	}
	return fname;
}


string getTargetName(string fname) {
	string basename = getBaseName(fname);
	auto pos = basename.find(".exe");
	if (pos < basename.length())
		basename.resize(pos);
	return basename += ".py";
}


int execLocal(string basedir, int argc, char* argv[]) {
	string target = getTargetName(argv[0]);
	string python = "\"" + basedir + '\\' + PYTHON_DIR + "\\python.exe\"";
	string script = "\"" + basedir + '\\' + target + "\"";
	auto cmd = python + " " + script;

	for (int i = 1; i < argc; ++i)
		cmd = cmd + " " + "\"" + argv[i] + "\"";
	cmd = "\"" + cmd + "\"";
	//cout << cmd << endl;
	return system(cmd.c_str());
}

int main(int argc, char* argv[])
{
	string basedir = getBaseDir();
	//cout << basedir << endl;
	return execLocal(basedir, argc, argv);
}

