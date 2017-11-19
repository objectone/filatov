#pragma once

#include "xqueue.h"

#include <stdlib.h>
#include <Windows.h>

// структура для хранения измеренных результатов сортировки
struct Counts    
{
	int shiftCnt;      // число перемещений элементов сортируемого массива при сортировке
	int compareCnt;    //  число сравнений элементов сортируемого массива при сортировке
	int duration;      // время (в тиках), затраченное на сортировку 
};

//Сортировка бинарными вставками
// (in) T* mas - массив
// (in) int count - размер массива
// return - структура с результатами сортировки
template< typename T>
Counts sort_bin_insert(T* mas, int count)
{
	Counts counts = { 0, 0, 0};
	ULONGLONG startTime = GetTickCount64();  // метка начала процесса сортировки
	for (int i = 1; i < count; i++)  // сортируем массив на месте
	{
		counts.compareCnt++;         // счетчик сравнения элементов массива  
		if (mas[i - 1] > mas[i])
		{
			T x = mas[i];      // x – включаемый элемент
			int left = 0;       // левая граница отсортированной части массива
			int right = i - 1;    // правая граница отсортированной части массива 
			do            // поиск места переноса методом половинного деления
			{
				int sred = (left + right) / 2;      // sred – новая "середина" последовательности
				counts.compareCnt++;   // счетчик сравнения элементов массива
				if (mas[sred] < x)
				{
					left = sred + 1;
				}
				else
				{
					right = sred - 1;
				}
			} while (left <= right);     // поиск ведется до тех пор, пока левая граница не окажется правее правой границы

			for (int j = i - 1; j >= left; j--)  // сдвигаем массив 
			{
				counts.shiftCnt++;  // счетчик сдвига элементов массива
				mas[j + 1] = mas[j];
			}
			counts.shiftCnt++;  // счетчик сдвига элементов массива
			mas[left] = x; // вставляем перемещаемый элемент
		}
	}
	counts.duration = GetTickCount64() - startTime;  // сохраняем время выполнения сортировки
	return counts;
}

// Функция переноса очереди в массив
// (in) xQueue<T>& q - очередь
// (in/out) T** mas - указатель на переменную-массив
// return - размер созданного массива
template<typename T>
size_t queueToArray( xQueue<T>& q, T** mas )
{
	if (q.empty())
	{
		return 0;
	}

	size_t count = q.size();
	T* pMas = new T[count];  // временный массив для сортировки
	int i = 0;
	while (!q.empty()) // переносим очередь в массив
	{
		pMas[i++] = q.front();
		q.pop();
	}
	*mas = pMas;
	return count;
}

// Функция копирования массива в очередь
// (in) xQueue<T>& q - очередь
// (in) T* mas - массив
// (in) size_t masSize - размер массива
template<typename T>
void arrayToQueue(xQueue<T>& q, T* mas, size_t masSize)
{
	for (int i = 0; i < masSize; i++)  // возвращаем отсортированный массив в очередь
	{
		q.push(mas[i]);
	}
}

// Функция создания массива определенного размера с инициализацией случайными значениями
// (in) size_t masSize - размер массива
// return - массив
template<typename T>
T* createArray(size_t arraySize)
{
	T* arr = new T[arraySize];
	for (int i = 0; i < arraySize; ++i )
	{
		arr[i] = (T)(rand());
	}
	
	return arr;
}