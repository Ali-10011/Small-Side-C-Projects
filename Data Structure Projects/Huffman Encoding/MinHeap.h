#pragma once
#include<iostream>
#include<assert.h>
using namespace std;

template <typename K, typename V>
struct HeapItem
{
	K Key;
	V Value;
};
template <typename K, typename V>
class MinHeap
{
	HeapItem<K, V>* Arr;
	int Capacity;
	int TotalElements;
	void DoubleCapacity()
	{
		HeapItem<K, V>* newArr = new HeapItem<K, V>[this->Capacity * 2];
		this->Capacity *= 2;
		for (int i = 0; i < this->TotalElements; i++)
		{
			newArr[i] = this->Arr[i];
		}
		delete[]this->Arr;
		this->Arr = newArr;
	}
	void ShiftUp(int Index)
	{
		int parent = (Index - 1) / 2;

		if (this->Arr[Index].Key < this->Arr[parent].Key)
			swap(this->Arr[Index], this->Arr[parent]);
		else return;

		if (parent > 0)
			ShiftUp(parent);
	}
	void ShiftDown(int Index)
	{
		int lChild = (Index * 2) + 1;
		int rChild = (Index * 2) + 2;
		int Min = Index;
		if (lChild<this->TotalElements && this->Arr[Min].Key>this->Arr[lChild].Key)
		{
			Min = lChild;
		}
		if (rChild<this->TotalElements && this->Arr[Min].Key>this->Arr[rChild].Key)
		{
			Min = rChild;
		}
		if (Min == Index)
			return;

		swap(this->Arr[Min], this->Arr[Index]);
		ShiftDown(Min);

	}
	void HeapifyRec(K* Arr, int Size, int Index)
	{
		int lChild = (Index * 2) + 1;
		int rChild = (Index * 2) + 2;
		int Min = Index;
		if (lChild<Size && Arr[Min].Key>Arr[lChild].Key)
		{
			Min = lChild;
		}
		if (rChild<Size && Arr[Min].Key>Arr[rChild].Key)
		{
			Min = rChild;
		}
		if (Min == Index)
			return;

		swap(Arr[Min], Arr[Index]);
		HeapifyRec(Arr, Size, Min);
	}
public:
	MinHeap()
	{
		this->Arr = new HeapItem<K, V>[1];
		this->TotalElements = 0;
		this->Capacity = 1;
	}
	MinHeap(int _capacity)
	{
		assert(_capacity > 0);
		this->Arr = new HeapItem<K, V>[_capacity];
		this->TotalElements = 0;
		this->Capacity = _capacity;
	}
	void Insert(K Key, V Value)
	{
		if (this->TotalElements == this->Capacity)
		{
			this->DoubleCapacity();
		}
		this->Arr[this->TotalElements].Key = Key;
		this->Arr[this->TotalElements].Value = Value;

		this->ShiftUp(this->TotalElements);
		this->TotalElements++;
	}
	void DeleteMin()
	{
		assert(this->TotalElements > 0);
		swap(this->Arr[0], this->Arr[this->TotalElements - 1]);
		this->TotalElements--;
		this->ShiftDown(0);
	}
	void Heapify(K* Arr, int Size)
	{
		this->HeapifyRec(Arr, Size, 0);
	}
	void GetMin(V& v)
	{
		v = this->Arr[0].Value;
	}
	void GetMax(V& v, K& k)
	{
		K Key = this->Arr[0].Key;
		v = this->Arr[0].Value;
		k = this->Arr[0].Key;
		for (int i = 0; i < this->TotalElements; i++)
		{
			if (Key < this->Arr[i].Key)
			{
				Key = this->Arr[i].Key;
				v = this->Arr[i].Value;
				k = this->Arr[i].Key;
			}
		}
	}
	bool IsEmpty()
	{
		return (this->TotalElements == 0);
	}
	HeapItem<K, V>* GetArr()
	{
		return this->Arr;
	}
	int GetTotalELements()
	{
		return this->TotalElements;
	}
	void print()
	{
		for (int i = 0; i <this->TotalElements; i++)
		{

			cout << "Key : " << Arr[i].Key << " ";
			cout << " Value : " << Arr[i].Value << endl;
		}
	}
	~MinHeap()
	{
		if (Arr) {
			delete[]this->Arr;
			this->Arr = NULL;
			this->TotalElements = this->Capacity = 0;
		}
	}
};

