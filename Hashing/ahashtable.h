#ifndef A_HASH_TABLE
#define A_HASH_TABLE

//open Adressing for collision handling\

#define HASH_DEFAULT_SIZE 10


template <typename T>
class AHashTable {
public:
	AHashTable(size_t(*hash1)(T const&), size_t size = HASH_DEFAULT_SIZE, size_t(*hash2)(T const&) = nullptr);

	~AHashTable();

	bool insert(T key);

	bool full() const;

	void erase(T key);

private:
	size_t size;
	size_t curr_size;
	size_t(*hash1)(T const& e);
	size_t(*hash2)(T const& e);
	T** HTable;
};

template<typename T>
inline AHashTable<T>::AHashTable(size_t(*hash1)(T const& e), size_t size, size_t(*hash2)(T const& e)) {
	: size(size), curr_size(0), hash1(hash1), hash2(hash2) {
	HTable = new T*[size];
	for (size_t i = 0; i < size; i++)
		HTable[i] = nullptr;
}

template<typename T>
inline AHashTable<T>::~AHashTable() {
	for (size_t i = 0; i < size; i++)
		delete HTable[i];
	delete HTable;
}

template<typename T>
inline bool AHashTable<T>::insert(T key) {
	if (full()) 
		return false;
	size_t index1 = hash1(key);
	size_t index2 = index1;
	for (size_t i = 1; HTable[index2] != nullptr; i++) {
		if (hash2)
			index2 = (index1 + i * hash2(key)) % size;
		else
			index2 = (i + 1) % size;
	}
	HTable[index2] = new T;
	HTable[index2] = key;
	curr_size++;
	return true;
}

template<typename T>
inline bool AHashTable<T>::full() const {
	return curr_size == size;
}

template<typename T>
inline void AHashTable<T>::erase(T key) {
	size_t index1 = hash1(key);
	size_t index2 = index1;
	for (size_t i = 1; HTable[index2] != key; i++) {
		if (hash2)
			index2 = (index1 + i * hash2(key)) % size;
		else
			index2 = (i + 1) % size;
	}
	delete HTable[index2];
	HTable[index2] = nullptr;
	curr_size--;

}

#endif // !A_HASH_TABLE


