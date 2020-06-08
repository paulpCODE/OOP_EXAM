#pragma once

#include <iostream>
#include <string>
#include "HashTable.h"

using namespace std;

const int FREE = 0; // свободная ячейка
const int BUSY = 1; // занятая ячейка
const int REMOVED = 2; // удалённая ячейка

template <typename KeyType, typename DataType>
class LinearProbingHashNode : public HashNode<KeyType, DataType> {
public:
	LinearProbingHashNode(KeyType key, DataType* data) :
		HashNode<KeyType, DataType>(key, data), state{ 0 } {};

	LinearProbingHashNode() {};

	int state{ 0 };
};

template <typename KeyType, typename DataType>
class LinearProbingTable : public HashTable<KeyType, DataType> {

	int size;
	int q; // шаг пробирования

	LinearProbingHashNode<KeyType, DataType>* cells; // массив ячеек

	int (*h)(KeyType); // указатель на хеш-функцию

public:
	LinearProbingTable(int tableSize, int (*h)(KeyType), int q = 1); // конструктор из размера, хеш-функции и шага пробирования
	LinearProbingTable(const LinearProbingTable<KeyType, DataType>& table); // конструктор копирования

	void insert(KeyType key, DataType* data); // добавление значения по ключу
	bool remove(KeyType key); // удаление по ключу
	bool find(const KeyType& key); // поиск по ключу
	bool set(KeyType key, DataType* data);

	void clear(); // очистка таблицы
	DataType* search(KeyType key); // получение значения по ключу

	void Print() const; // вывод таблицы

	int GetSize() const; // получение размера
	bool IsEmpty() const; // проверка на пустоту

	~LinearProbingTable(); // деструктор (освобождение памяти)
};

template <typename KeyType, typename DataType>
int LinearProbingTable<KeyType, DataType>::GetSize() const {
	return this->size; // возвращаем размер
}

template <typename KeyType, typename DataType>
bool LinearProbingTable<KeyType, DataType>::IsEmpty() const {
	return this->size == 0; // таблица пуста, если нет элементов
}
	
// конструктор из размера, хеш-функции и шага пробирования
template <typename KeyType, typename DataType>
LinearProbingTable<KeyType, DataType>::LinearProbingTable(int tableSize, int (*h)(KeyType), int q) : HashTable<KeyType, DataType>(tableSize){
	this->size = 0; // изначально нет элементов
	this->q = q;
	this->cells = new LinearProbingHashNode<KeyType, DataType>[tableSize]; // выделяем память под ячейки

	for (int i = 0; i < tableSize; i++)
		cells[i].state = FREE;

	this->h = h; // запоминаем указатель на функцию
}

// конструктор копирования
template <typename KeyType, typename DataType>
LinearProbingTable<KeyType, DataType>::LinearProbingTable(const LinearProbingTable<KeyType, DataType>& table) {
	this->capacity = table.capacity; // копируем ёмкость
	this->size = table.size; // копируем количество элементов
	q = table.q; // копируем шаг пробирования

	this->cells = new LinearProbingHashNode<KeyType, DataType>[this->capacity]; // выделяем память под массив

	h = table.h; // копируем указатель на функцию

	// проходимся по всем ячейкам таблицы и копируем их содержимое
	for (int i = 0; i < this->capacity; i++) {
		cells[i].data = table.cells[i].data;
		cells[i].key = table.cells[i].key;
		cells[i].state = table.cells[i].state;
	}
}

// добавление значения по ключу
template <typename KeyType, typename DataType>
void LinearProbingTable<KeyType, DataType>::insert(KeyType key, DataType* data) {
	int sequenceLength = 0; // начальная длина пробной последовательности равна нулю
	int hash = h(key); // получаем хеш от ключа
	if (data == nullptr) throw std::string("Unable to insert nullptr data");

	while (sequenceLength < this->capacity) {
		int index = (hash + sequenceLength * q) % this->capacity;

		if (cells[index].state != BUSY) { // если нашли незанятую ячейку
			cells[index].key = key; // сохраняем ключ
			cells[index].data = data; // сохраняем значение
			cells[index].state = BUSY; // ячейка становится занятой

			this->size++; // увеличиваем счётчик числа элементов
			return; // выходим
		}

		sequenceLength++; // увеличиваем длину пробной последовательности
	}

	// прошли всю таблицу
	//throw std::string("Unable to insert data with this key"); // бросаем исключение
}

// удаление по ключу
template <typename KeyType, typename DataType>
bool LinearProbingTable<KeyType, DataType>::remove(KeyType key) {
	int sequenceLength = 0; // начальная длина пробной последовательности равна нулю
	int hash = h(key); // получаем хеш от ключа

	while (sequenceLength < this->capacity) {
		int index = (hash + sequenceLength * q) % this->capacity;

		// если нашли занятую нужным ключом ячейку
		if (cells[index].state == BUSY && cells[index].key == key) {
			cells[index].state = REMOVED; // помечаем её как удалённую
			this->size--; // уменьшаем счётчик числа элементов

			return true;
		}

		if (cells[index].state == FREE)
			return false;

		sequenceLength++; // увеличиваем длину пробной последовательности
	}
	return false;
}

// поиск по ключу
template <typename KeyType, typename DataType>
bool LinearProbingTable<KeyType, DataType>::find(const KeyType& key) {
	int sequenceLength = 0; // начальная длина пробной последовательности равна нулю
	int hash = h(key); // получаем хеш от ключа

	while (sequenceLength < this->capacity) {
		int index = (hash + sequenceLength * q) % this->capacity; // ищем индекс элемента

		// если нашли занятую клетку с нужным ключом
		if (cells[index].state == BUSY && cells[index].key == key)
			return true; // значит нашли

		// если нашли свободную ячейку
		if (cells[index].state == FREE)
			return false; // значит нет элемента

		sequenceLength++; // увеличиваем длину пробной последовательности
	}

	return false; // не нашли во всей таблице
}

template<typename KeyType, typename DataType>
inline bool LinearProbingTable<KeyType, DataType>::set(KeyType key, DataType* data)
{
	int sequenceLength = 0; // начальная длина пробной последовательности равна нулю
	int hash = h(key); // получаем хеш от ключа

	while (sequenceLength < this->capacity) {
		int index = (hash + sequenceLength * q) % this->capacity; // ищем индекс элемента

		// если нашли занятую клетку с нужным ключом
		if (cells[index].state == BUSY && cells[index].key == key)
			cells[index].data = data;
			return true; // значит нашли

		// если нашли свободную ячейку
		if (cells[index].state == FREE)
			return false; // значит нет элемента

		sequenceLength++; // увеличиваем длину пробной последовательности
	}

	return false; // не нашли во всей таблице
}

template <typename KeyType, typename DataType>
void LinearProbingTable<KeyType, DataType>::clear() {
	for (int i = 0; i < this->capacity; i++)
		cells[i].state = FREE;

	this->size = 0; // обнуляем счётчик числа элементов
}

// получение значения по ключу
template <typename KeyType, typename DataType>
DataType* LinearProbingTable<KeyType, DataType>::search(KeyType key) {
	int sequenceLength = 0;
	int hash = h(key); // получаем хеш от ключа

	while (sequenceLength < this->capacity) {
		int index = (hash + sequenceLength * q) % this->capacity; // ищем индекс элемента

		// если нашли занятую клетку с нужным ключом
		if (cells[index].state == BUSY && cells[index].key == key)
			return cells[index].data; // значит нашли

		// если нашли свободную ячейку, значит нет такого элемента
		if (cells[index].state == FREE)
			return nullptr;
			//throw string("No data with this key"); // бросаем исключение

		sequenceLength++; // увеличиваем длину пробной последовательности
	}

	// обошли всю таблицу
	return nullptr;
	//throw string("No data with this key"); // бросаем исключение
}

// деструктор (освобождения памяти)
template <typename KeyType, typename DataType>
LinearProbingTable<KeyType, DataType>::~LinearProbingTable() {
	delete[] cells; // удаляем массив ячеек
}

// оператор вывода в поток
template <typename KeyType, typename DataType>
void LinearProbingTable<KeyType, DataType>::Print() const {
	for (int i = 0; i < this->capacity; i++) {
		if (cells[i].state != BUSY)
			continue; // если ячейка не занята, то переходим к следующему элементу

		cout << "[" << i << "]: "; // выводим номер ячейки
		cout << cells[i].data << "(" << cells[i].key << ") "; // выводим содержимое ячейки
		cout << endl; // переходим на новую строку
	}
}
