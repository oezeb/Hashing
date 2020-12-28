#ifndef A_HASH_TABLE
#define A_HASH_TABLE

#define HASH_DEFAULT_SIZE 10

//open Adressing for collision handling
template <typename K, typename D>
class AHashTable {
public:
	AHashTable(size_t(*hash1)(K const&), size_t size = HASH_DEFAULT_SIZE, size_t(*hash2)(K const&) = nullptr);

	~AHashTable();

	bool insert(K key,D data);

	bool full() const;

	void erase(K key);

	D& operator[](K const& key);

private:
	size_t size;
	size_t curr_size;
	size_t(*hash1)(K const& key);
	size_t(*hash2)(K const& key);
	K** key_arr;
	D* data_arr;
};


template<typename K, typename D>
inline AHashTable<K, D>::AHashTable(size_t(*hash1)(K const&), size_t size, size_t(*hash2)(K const&))
	: size(size), curr_size(0), hash1(hash1), hash2(hash2) {
	key_arr = new K * [size];
	data_arr = new D[size];
	for (size_t i = 0; i < size; i++)
		key_arr[i] = nullptr;
}

template<typename K, typename D>
inline AHashTable<K, D>::~AHashTable() {
	for (size_t i = 0; i < size; i++)
		delete key_arr[i];
	delete key_arr;
	delete data_arr;
}

template<typename K, typename D>
inline bool AHashTable<K, D>::insert(K key, D data) {
	if (full())
		return false;
	size_t index1 = hash1(key);
	size_t index2 = index1;
	for (size_t i = 1; key_arr[index2] != nullptr; i++) {
		if (hash2)
			index2 = (index1 + i * hash2(key)) % size;
		else
			index2 = (i + 1) % size;
	}
	key_arr[index2] = new K;
	*key_arr[index2] = key;
	data_arr[index2] = data;
	curr_size++;
	return true;
}

template<typename K, typename D>
inline bool AHashTable<K, D>::full() const {
	return curr_size == size;
}

template<typename K, typename D>
inline void AHashTable<K, D>::erase(K key) {
	size_t index1 = hash1(key);
	size_t index2 = index1;
	for (size_t i = 1; *key_arr[index2] != key; i++) {
		if (hash2)
			index2 = (index1 + i * hash2(key)) % size;
		else
			index2 = (i + 1) % size;
	}
	delete key_arr[index2];
	key_arr[index2] = nullptr;
	curr_size--;
}

template<typename K, typename D>
inline D& AHashTable<K, D>::operator[](K const& key) {
	size_t index1 = hash1(key);
	size_t index2 = index1;
	for (size_t i = 1; *key_arr[index2] != key; i++) {
		if (hash2)
			index2 = (index1 + i * hash2(key)) % size;
		else
			index2 = (i + 1) % size;
	}
	return data_arr[index2];
}

#endif // !A_HASH_TABLE


