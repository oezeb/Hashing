#ifndef C_HASH_TABLE
#define C_HASH_TABLE

#include <list>

#define HASH_DEFAULT_SIZE 10

//separate Chaining for collision handling
template <typename T>
class CHashTable {
public:
	CHashTable(size_t(*Hfunction)(T const& e), size_t size = HASH_DEFAULT_SIZE);

	bool insert(T e);

	void erase(T e);

	void Traverse(void visit(T& e));

private:
	size_t size;
	size_t(*Hfunction)(T const& e);
	std::list<T>* HTable;
};

template<typename T>
CHashTable<T>::CHashTable(size_t(*Hfunction)(T const& e), size_t size)
	: Hfunction(Hfunction), size(size) {
	HTable = new std::list<T>[size];
}


template<typename T>
bool CHashTable<T>::insert(T e) {
	size_t index = Hfunction(e);
	if (index >= size)
		return false;
	HTable[index].push_back(e);
	return true;
}

template<typename T>
void CHashTable<T>::erase(T e) {
	size_t index = Hfunction(e);
	for(size_t i = 0; i < HTable[i].size();i++)
		if (HTable[i] == e)
			HTable[i].erase(i);
}

template<typename T>
void CHashTable<T>::Traverse(void visit(T& e)) {
	for (size_t i = 0; i < size; i++)
		for (auto& j : HTable[i])
			visit(j);
}

#endif // !C_HASH_TABLE

