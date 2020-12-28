#ifndef C_HASH_TABLE
#define C_HASH_TABLE

#include <map>

#define HASH_DEFAULT_SIZE 10

//separate Chaining for collision handling
template <typename K,typename D>
class CHashTable {
public:
	CHashTable(size_t(*Hfunction)(K const& key), size_t size = HASH_DEFAULT_SIZE);

	bool insert(K const& key, D data);

	bool full() const;

	void erase(K const& key);

	D get(K const& key) const;

	void Traverse(void visit(K key, D data));

private:
	size_t size;
	size_t curr_size;
	size_t(*Hfunction)(K const& e);
	std::map<K, D>* HTable;
};

template<typename K, typename D>
inline CHashTable<K, D>::CHashTable(size_t(*Hfunction)(K const& key), size_t size)
	: Hfunction(Hfunction), size(size), curr_size(0) {
		HTable = new std::map<K, D>[size];
}

template<typename K, typename D>
inline bool CHashTable<K, D>::insert(K const& key, D data) {
	size_t index = Hfunction(key);
	if (index >= size || full())
		return false;
	std::map<int, int> m;
	HTable[index].insert(std::pair<K, D>(key, data));
	curr_size++;
	return true;
}

template<typename K, typename D>
inline bool CHashTable<K, D>::full() const {
	return size == curr_size;
}

template<typename K, typename D>
inline void CHashTable<K, D>::erase(K const& key) {
	size_t index = Hfunction(key);
	HTable[index].erase(key);
	curr_size--;
}
template<typename K, typename D>
inline D CHashTable<K, D>::get(K const& key) const {
	size_t index = Hfunction(key);
	return HTable[index].find(key)->second;
}

template<typename K, typename D>
inline void CHashTable<K, D>::Traverse(void visit(K key, D data)) {
	for (size_t i = 0; i < size; i++)
		for (auto j : HTable[i])
			visit(j.first, j.second);
}

#endif // !C_HASH_TABLE
