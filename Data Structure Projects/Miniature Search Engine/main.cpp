#include <iostream>
#include <list>
#include <chrono>
#include <fstream>
#include <string>
#include <string.h>
using namespace std;

struct TreeNode
{
	string keyword;
	list<string> URLs;
	TreeNode* lchild;
	TreeNode* rchild;
	TreeNode() 
	{
		lchild = nullptr;
		rchild = nullptr;

	}
};

class Engine {
private:
	TreeNode* root;
	void insert(string keyword, string url) 
	{
		if (root == nullptr) //very first insertion, it has to happen in any case
		{
			root = new TreeNode();
			root->keyword = keyword;
			root->URLs.push_back(url);
			return;
		}
		else 
		{
			TreeNode* ptr = this->root;  //normal insertion of a typical tree with respect to the string comparison
			bool breakloop = false; 
			while (!breakloop) 		
			{
				if (keyword < ptr->keyword)
				{
					if (ptr->lchild == nullptr)
					{
						ptr->lchild = new TreeNode();
						ptr->lchild->keyword = keyword;
						ptr->lchild->URLs.push_back(url);
						breakloop = true;
					}
					else
					{
						ptr = ptr->lchild;
					}
				}
				else if (keyword > ptr->keyword)
				{
					if (ptr->rchild == nullptr)
					{

						ptr->rchild = new TreeNode();
						ptr->rchild->keyword = keyword;
						ptr->rchild->URLs.push_back(url);
						breakloop = true;
					}
				else
				{
					ptr = ptr->rchild;
				}
				}
				else //could be the same keyword but different URL
				{
					ptr->URLs.push_back(url);
					ptr->URLs.unique(); //removes all redundacies
					return;
				}

				
			}
		}
	}
	void inorderPrintKeys(TreeNode* ptr) { //left, it, right
		if (ptr)
		{ //as long as it is not a nullNode
			inorderPrintKeys(ptr->lchild);
			cout << ptr->keyword << endl;
			inorderPrintKeys(ptr->rchild);

		}
	}
	void preOrderPrintKeys(TreeNode* ptr)
	{
		if (ptr)  //it, left, right
		{
			cout << ptr->keyword << endl;
			preOrderPrintKeys(ptr->lchild);
			preOrderPrintKeys(ptr->rchild);
		}
	}
	list<string>* search(string keyword, TreeNode* ptr) {
		if (ptr == nullptr)
		{
			return nullptr;
		}
		else if (keyword > ptr->keyword) //if the key is greater then that means the specified Value lies on the right side of the current Node
		{
			return this->search(keyword, ptr->rchild);
		}
		else if (keyword < ptr->keyword) //if the key is less then that means the specified value lies on the left side
		{
			return this->search(keyword, ptr->lchild);
		}
		else {
			return &ptr->URLs;
		}
	}
	void deleteAll(TreeNode* ptr)
	{
		if (ptr)
		{
			deleteAll(ptr->lchild);
			deleteAll(ptr->rchild);
			delete ptr;
		}
	
	}
	void delete_(string keyword, TreeNode*& ptr)
	{
		if (ptr == nullptr)  //base case set
		{
			return;
		}
		else if (ptr->keyword < keyword) //the node to be deleted, lies on the right side
		{
			return delete_(keyword, ptr->rchild);
		}
		else if (ptr->keyword > keyword)
		{
			return delete_(keyword, ptr->lchild);
		}
		else //4 cases will come out
		{
			if (!ptr->lchild && !ptr->rchild) //it has neither left or right child
			{
				delete ptr;
				ptr = nullptr;
			}
			else if (ptr->rchild && !ptr->lchild) //only rchild exists
			{
				TreeNode* delNode = ptr;
				ptr = ptr->rchild;
				delete delNode;				
			}
			else if (ptr->lchild && !ptr->rchild) // only lchild exists
			{
				TreeNode* delNode = ptr;
				ptr = ptr->lchild;
				delete delNode;
			}
			else //both children exist
			{
				TreeNode* successor = ptr->rchild;
				while (successor->lchild) {
					successor = successor->lchild;
				}
				ptr->keyword = successor->keyword;
				ptr->URLs = successor->URLs;
				delete_(successor->keyword, ptr->rchild);
			}
		}
	}
public:
	Engine() {
		this->root = nullptr;
	}
	void insert(string filename)
	{
		chrono::steady_clock::time_point begin = chrono::steady_clock::now();
		string url_temp;
		string word_temp;
		int num;
		ifstream file;
		string word;
		int length;
		file.open(filename);

		while (!file.eof())
		{
			file >> num;
			file >> url_temp;
			file.ignore(1); //because the file has extra spaces
			getline(file, word_temp);
			file.ignore(1);
			length = word_temp.length();
			for (int i = 0; i < word_temp.length(); i++) {
				if (word_temp.at(i) != ' ') //reading a character to make up a word till the next space is reached which indicates that keyword has ended
				{
					word.push_back(word_temp.at(i));
				}
				if (((i + 1) == word_temp.length()) || word_temp.at(i) == ' ')
				{
					insert(word, url_temp); //inserting the word
					word.clear();
				}
			}
		}

		
		chrono::steady_clock::time_point end = chrono::steady_clock::now();
		cout << "53 URLs Loaded in " << ((chrono::duration_cast<chrono::microseconds>(end - begin).count())/100000) << " second(s) and " << ((chrono::duration_cast<chrono::microseconds>(end - begin).count())%100000) << " microseconds." << endl;
		
		}
	void inorderPrintKeys()
	{
		inorderPrintKeys(this->root);
	}
	void preOrderPrintKeys()
	{
		this->preOrderPrintKeys(this->root);
	}
	list<string>* search(string keyword) 
	{
		return this->search(keyword, this->root);
	}
	void delete_(string keyword)
	{
		delete_(keyword, this->root);
	}
	~Engine()
	{
		this->deleteAll(this->root);
	}

};

int main() {
	list<string>* ptr;
	Engine Yahoo;
	string filename;
	string keyword;

	cout << "Please enter a filename: ";
	cin >> filename;
	Yahoo.insert(filename);
	cout << endl;
	cout << "Please enter a keyword, or enter - to exit: ";
	cin >> keyword;
	Yahoo.delete_("life");
	while (keyword.at(0) != '-') {
		chrono::steady_clock::time_point begin = chrono::steady_clock::now();
		ptr = Yahoo.search(keyword);
		chrono::steady_clock::time_point end = chrono::steady_clock::now();
		if (ptr) {
			cout << ptr->size() << " result(s) found in "  << ((chrono::duration_cast<chrono::microseconds>(end - begin).count()) / 100000) << " second(s) and " << ((chrono::duration_cast<chrono::microseconds>(end - begin).count()) % 100000) << " microseconds." << endl;
			for (int i = 0; !ptr->empty(); i++)
			{
				cout << i + 1 << ") " << ptr->front() << endl;
				ptr->pop_front();
			}
		}
		else {
			cout << "No result(s) found in " << ((chrono::duration_cast<chrono::microseconds>(end - begin).count()) / 100000) << " second(s) and " << ((chrono::duration_cast<chrono::microseconds>(end - begin).count()) % 100000) << " microseconds." << endl;
		}
		cout << endl << endl;
		cout << "Please enter a keyword, or enter - to exit: ";
		cin >> keyword;
	}
	
	system("pause");
	return 0;
}