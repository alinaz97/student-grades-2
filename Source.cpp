#include"Header.h"

using namespace std;


int main()
{
	string command;
	
	do
	{
		cin >> command;
		if(command == "create")
			create();
		else if(command == "sequentialSearch")
			sequentialSearch();

		else if(command == "update") 
			update();

		else if(command == "delete")
			deleteStudent();

	} while (command != "exit");

	system("pause");
	return 0;
}