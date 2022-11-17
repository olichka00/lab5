#include <iostream>
#include <string>
#include "Dialog.h"

void Save(CWorkspace &ws) {
	std::string path;
	std::cout << "Enter the path to the file(without extension):";
	std::cin >> path;
	path += ".txt";
	if (ws.Save(path))
		std::cout << "Successfuly\n";
	else
		std::cout << "Error\n";
}

void Load(CWorkspace &ws) {
	std::string path;
	std::cout << "Enter the path to the file(without extension):";
	std::cin >> path;
	path += ".txt";
	if (ws.Load(path))
		std::cout << "Successfuly.\n";
	else {
		std::cout << "Error. ";
		std::cout << "No such file\n";
	}
}

void Init(CWorkspace &ws) {
	int nDepth = 0, nLength = 0;
	std::cout << "Depth: ";
	std::cin >> nDepth;

	std::cout << "Length: ";
	std::cin >> nLength;
	
	ws.Init(nDepth, nLength);
}

void ShowFullSequence(CWorkspace &ws) {
	std::cout << ws.GetChainString() << std::endl;
}

void Find(CWorkspace &ws) {
	std::string str;
	int pos;
	std::cout << "Enter the line, you want to find: ";
	std::cin >> str;
	std::cout << "Enter the position: ";
	std::cin >> pos;

	if (ws.Find(str.c_str(), pos) == -1)
		std::cout << "The line not found\n";
	else
		std::cout << "Id from the first occurrence " << ws.Find(str.c_str(), pos) << std::endl;
}

void ShowAllLinks(CWorkspace &ws) {
	ws.ShowAll();
}

void RemoveLink(CWorkspace &ws) {
	int n = 0;
	std::cout << "Enter the position, you want delete: ";
	std::cin >> n;
	if (ws.RemoveLink(n))
		std::cout << "Successfuly\n";
	else {
		std::cout << "Error, element with id not exist";
	}
}

void AddPerson(CWorkspace &ws) {
	std::string str;
	std::cout << "Enter the line: ";
	std::cin >> str;

	int n;
	std::cout << "Enter the num of group: ";
	std::cin >> n;

	std::string name;
	std::cout << "Enter the name: ";
	std::cin >> name;

	ws.AddPerson(str.c_str(), n, name.c_str());
}

void AddLink(CWorkspace &ws) {
	std::string str;
	std::cout << "Enter the line: ";
	std::cin >> str;

	std::string url;
	std::cout << "Enter the url: ";
	std::cin >> url;

	ws.AddURL(str.c_str(), url.c_str());
}

void TestPosition(CWorkspace &ws) {
	std::cout << "Enter the position, you want to test: ";
	int pos;
	std::cin >> pos;
	LinksArray links;
	if (ws.TestPosition(pos, links)) {
		std::cout << "Finded " << links.size() << " links\n";
	} else {
		std::cout << "Not such elements with position " << pos << std::endl;
	}

}

void TestInterval(CWorkspace &ws) {
	std::cout << "Enter the start position: ";
	int start;
	std::cin >> start;

	std::cout << "Enter the end position: ";
	int end;
	std::cin >> end;

	LinksArray links;
	if (ws.TestInterval(start, end, links)) {
		std::cout << "Finded " << links.size() << " links\n";
	} else {
		std::cout << "Not such links with numbers whoose place in range [" << start << " " << end << "]\n";
	}
}

void InitPi(CWorkspace &ws) {
	std::cout << "Enter the length: ";
	int length;
	std::cin >> length;

	ws.Init(-1, length);
}



int main() {
	std::cout << "123";
	CDataSimple ds;
	CWorkspace ws(ds);
	CDialogManager mgr(ws);
	mgr.RegisterCommand("Init sequence", Init);
	mgr.RegisterCommand("Init sequence Pi", InitPi);
	mgr.RegisterCommand("Show sequence", ShowFullSequence);
	mgr.RegisterCommand("Find substring", Find);
	mgr.RegisterCommand("Add link", AddLink);
	mgr.RegisterCommand("Show All Links", ShowAllLinks);
	mgr.RegisterCommand("Remove Link", RemoveLink);
	mgr.RegisterCommand("Add Person", AddPerson);
	mgr.RegisterCommand("Test Position", TestPosition);
	mgr.RegisterCommand("Test Interval", TestInterval);
	mgr.RegisterCommand("Save", Save);
	mgr.RegisterCommand("Load", Load);

	mgr.Run();
	return 0;
}