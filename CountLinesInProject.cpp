#include <Windows.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <iterator>
using namespace std;

vector<string> get_all_files_names_within_folder(string &folder)
{
	vector<string> names;
	string search_path = folder + "/*.*";
	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				names.push_back(fd.cFileName);
			}
		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
	return names;
}

string splitToken(string &stringInput, const string &delim)
{
	size_t pos = 0;
	string token = "";
	if ((pos = stringInput.find(delim)) != string::npos)
	{
		token = stringInput.substr(0, pos);
		stringInput.erase(0, pos + delim.length());
	}
	return token;
}

int countLineNumbersInProject(vector<string> listFiles, const string &folder)
{
	cout << "Lines: ";
	string temp, extension;
	unsigned countLines = 0;
	for (auto i : listFiles)
	{
		temp = " ";
		extension = i;
		while (temp != "")
			temp = splitToken(extension, ".");
		if (extension != "cpp" && extension != "h") continue;
		ifstream fileInput(folder + "/" + i);
		while (!fileInput.eof())
		{
			getline(fileInput, temp);
			++countLines;
		}
		fileInput.close();
	}
	return countLines;
}

int main()
{
	string folder;
	cout << "Enter your folder's name: ";
	getline(cin, folder);
	vector<string> ls = get_all_files_names_within_folder(folder);
	cout << countLineNumbersInProject(ls, folder) << endl;
	system("pause");
}