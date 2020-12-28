#include <iostream>
#include <string>
#include <map>
#include "chashtable.h"

using namespace std;

//custom hashing function
size_t hash0(string const& str) {
	return  str.empty() ? 0 : str[0] % HASH_DEFAULT_SIZE;
}

void print(string name,int age) {
	cout << "name : " << name << ", age : " << age << endl;
}

int main() {

	CHashTable<string,int> Tab(hash0);
	int age[] = { 84, 34, 23, 999,59, 9,117 };
	string name[] = { "avs","kjh","weio","jskj","hjhv","qiuw","ouhe" };
	for (int i = 0; i < 7; i++)
		Tab.insert(name[i], age[i]);
	Tab.Traverse(print);
	cout << "avs-->" << Tab.get("avs");
	//T.display();*/
	return 0;
}
