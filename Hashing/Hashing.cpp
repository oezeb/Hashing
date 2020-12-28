#include <iostream>
#include <string>
#include <map>
#include "chashtable.h"
#include "ahashtable.h"

using namespace std;

//custom hashing function
size_t hash0(string const& str) {
	return  str.empty() ? 0 : str[0] % HASH_DEFAULT_SIZE;
}

void print(string name,int age) {
	cout << "name : " << name << ", age : " << age << endl;
}

int main() {
	int age[] = { 19, 34, 23, 20, 59, 5, 17 };
	string name[] = { "jake","alex","peter","paul","justin","jade","chris" };

	CHashTable<string,int> CH(hash0);
	for (int i = 0; i < 7; i++)
		CH.insert(name[i], age[i]);
	cout << "separate Chaining for collision handling\n";
	cout << "jake " << CH["jake"] << "\n";
	cout << "peter " << CH["peter"] << "\n";
	cout << "paul " << CH["paul"] << "\n\n";

	AHashTable<string, int> AH(hash0);
	for (int i = 0; i < 7; i++)
		AH.insert(name[i], age[i]);
	cout << "open Adressing for collision handling\n";
	cout << "alex " << CH["alex"] << "\n";
	cout << "justin " << CH["justin"] << "\n";
	cout << "jade " << CH["jade"] << "\n";
	cout << "chris " << CH["chris"] << "\n";
	return 0;
}
