#include"HashTable.h"

int main()
{
	HashTable ht;

	ht.reg((char*)"login1", (char*)"password1", 10);
	ht.reg((char*)"login2", (char*)"password2", 10);
	ht.reg((char*)"login3", (char*)"password3", 10);	

	std::cout << ht.login((char*)"login1", (char*)"password1", 10) << std::endl;
	std::cout << ht.login((char*)"login4", (char*)"password1", 10) << std::endl;
	std::cout << ht.login((char*)"login1", (char*)"password2", 10) << std::endl;

	ht.show();

	return 0;
}