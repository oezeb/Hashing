#include <iostream>
#include <string>
#include "chashtable.h"

using namespace std;

typedef struct myStruct {
	int key;
	string data;
	myStruct(int key, string data) : key(key), data(data) {};
}myStruct;

//custom hashing function
size_t hash0(myStruct const& t) {
	return t.key % HASH_DEFAULT_SIZE;
}

void print(myStruct& t) {
	cout << "key : " << t.key << ", data : " << t.data << endl;
}

int main() {
	CHashTable<myStruct> Tab(hash0);
	int arr[] = { 84, 34, 23, 999,59, 9,117 };
	string str[] = { "avs","kjh","weio","jskj","hjhv","qiuw","ouhe" };
	for (int i = 0; i < 7; i++)
		Tab.insert(myStruct(arr[i],str[i]));
	Tab.Traverse(print);
	//T.display();
	return 0;
}
