#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string.h>
#include <string>
#include <iterator>
#include "MinHeap.h"
using namespace std;
struct HNode
{
	int freq;
	char character;
	HNode *left, *right;
	HNode()
	{
		character = NULL;
		left = nullptr;
		right = nullptr;
	}
	HNode(int freq, char character)
	{
		this->freq = freq;
		this->character = character;
		left = nullptr;
		right = nullptr;
	}
};
class HuffMan {
	HNode* root;
	void print(HNode* ptr, string code)
	{
		if (ptr)
		{
			if (!ptr->left && !ptr->right) { //only printing those nodes which have actual data in them
				if (int(ptr->character) == 9) {
					
					cout << "Character: TAB"  << " Frequency: " << ptr->freq << " Code: " << code << endl;
					code.clear();
				}
				else if (int(ptr->character) == 10)
				{
					cout << "Character: ENTER" << " Frequency: " << ptr->freq << " Code: " << code << endl;
					code.clear();
				}
				else if (int(ptr->character) == 32)
				{
					cout << "Character: SPACE" << " Frequency: " << ptr->freq << " Code: " << code << endl;
					code.clear();
				}
				else
				{
					cout << "Character: " << ptr->character << " Frequency: " << ptr->freq << " Code: ";
					cout << code << endl;
					code.clear();
				}
			}
			print(ptr->left, code + "0");
			print(ptr->right, code + "1");
		}
	}
	void deleteAll(HNode* ptr)
	{
		if (ptr)
		{
			deleteAll(ptr->left);
			deleteAll(ptr->right);
			delete ptr;
		}
	}
public:
	HuffMan() {
		root = nullptr;
	}
	void createHuffman(string filename)
	{
		unordered_map<char, int> map;
		unordered_map<char, int>::iterator Itr; //Declaring the iterator for hashmap
		char data;
		MinHeap<int, HNode*> heap; //MinHeap will have key and a HNode which has the data
		ifstream file;
		file.open(filename);
		while (!file.eof())
		{
			file.get(data);
			for (Itr = map.begin(); Itr != map.end(); Itr++) //initialzing, conditioning and moving the iterator to the next index
			{
				if (map.find(data) == Itr)  // returns the pointer //this type of key already exists in the HashMap
				{
					if (file.eof()) {
						break;
					}
					map[data]++; //increments the frequency/value of this key
					continue; //no need to go further
				}
			}
			map.insert(make_pair(data, 1)); //data/value pair //frequncy = 1 if a new type of key is found/inserted
			
		}
		file.close(); //we do not need the file anymore

		for (Itr = map.begin(); Itr != map.end(); Itr++) 
		{
			HNode* temp = new HNode(Itr->second, Itr->first); //freq, char. Making a HNode type variable, initialzing it then inserting it into the heap
			heap.Insert(Itr->second, temp);
		}
		while(heap.GetTotalELements() != 1) //Since we need to make the last element the root
		{
			HNode* parent = new HNode();
			HNode* lnode;
			HNode* rnode;
			heap.GetMin(lnode);			//making a new HNode, assigning it children and then moving on
			heap.DeleteMin();
			heap.GetMin(rnode);
			heap.DeleteMin();
			parent->freq = lnode->freq + rnode->freq;
			parent->left = lnode;
			parent->right = rnode;
			heap.Insert(parent->freq, parent);
		}
		heap.GetMin(root); //it will point the root to the last remaining element of heap
		heap.DeleteMin();//we do not need the last element of heap


	}

	void printHuffMan() 
	{
		string code;
		print(this->root, code);
	}
	~HuffMan()
	{
			this->deleteAll(this->root);
	}
};

int main()
{
	HuffMan code;
	code.createHuffman("file.txt");
	code.printHuffMan();


	system("pause");
	return 0;
}