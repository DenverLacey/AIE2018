#include <Windows.h>
#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;

void PrintDirectory(string directory, int depth)
{
	HANDLE hFind;
	WIN32_FIND_DATAA data;

	string padding(" ");
	padding.resize(depth + 1);

	string searchPath = directory + "\\*";

	hFind = FindFirstFileA(searchPath.c_str(), &data);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			//don't process the '.' or '..' entries
			if (strcmp(data.cFileName, ".") == 0 || strcmp(data.cFileName, "..") == 0) {
				continue;
			}

			cout << padding << data.cFileName << endl;

			if ((data.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY) {
				PrintDirectory(directory + "\\" + data.cFileName, depth + 1);
			}

		} while (FindNextFileA(hFind, &data));
		FindClose(hFind);
	}
}

int main()
{
	PrintDirectory("C:\\Users\\s181336\\Documents", 0);

	cout << endl << endl << "Press 'Enter' to exit the program.";
	cin.get();
	return 0;
}