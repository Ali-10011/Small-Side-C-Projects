#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;
template <typename K, typename V>
struct TreeNode {
	K key;
	V value;
	TreeNode* lChild;
	TreeNode* rChild;
	TreeNode() {
		lChild = nullptr;
		rChild = nullptr;
	}
	TreeNode(K _key, V _value) {
		this->key = _key;
		this->value = _value;
		lChild = nullptr;
		rChild = nullptr;
	}
	bool isLeaf() {
		return (!this->lChild && !this->rChild);
	}
};
template <typename K, typename V>
class SpecialBST {
private:
	TreeNode<K, V>* root;
	void insert(K _key, V _value, TreeNode<K, V>*&ptr) {
			if (ptr == nullptr)
			{
				ptr = new TreeNode<K, V>(_key, _value);
				makeroot(this->root, ptr);
			}
			else if (_key < ptr->key)
			{
				insert(_key, _value, ptr->lChild);
			}
			else if (_key > ptr->key)
			{
				insert(_key, _value, ptr->rChild);
			}
	}
	bool IsDuplicate(K key, TreeNode<K, V>* ptr) //checks for duplications in BST
	{
		if (ptr == nullptr)
			return false;
		else if (key < ptr->key)
			return this->IsDuplicate(key, ptr->lChild);
		else if (key > ptr->key)
			return this->IsDuplicate(key, ptr->rChild);
		else
			return true;

	}
	V* search(K key, TreeNode<K, V>* ptr) //searching function
	{
		TreeNode<K, V>* temp;
		if (ptr == nullptr) {
			return nullptr;
		}
		else if (key < ptr->key) {
			if ((searchtree(key, ptr->lChild)) == nullptr)
			{
				if (ptr != this->root) {
					makeroot(this->root, ptr);
					return nullptr;
				}
			}
			else {
				return this->search(key, ptr->lChild);
			}
		}
		else if (key > ptr->key) {
			if ((searchtree(key, ptr->rChild)) == nullptr)
			{
				if (ptr != this->root) {
					makeroot(this->root, ptr);
					return nullptr;
				}			
			}
			else
			{
				return this->search(key, ptr->rChild);
			}
		}			
		else {
			temp = ptr;
			makeroot(this->root, ptr);			
			return &temp->value;
		}
	}
	void leftRotate(TreeNode<K, V>*& ptr)
	{
		TreeNode<K, V>* y = ptr;
		TreeNode<K, V>* x = y->rChild;
		TreeNode<K, V>* T2 = x->lChild;
		ptr = x;
		x->lChild = y;
		y->rChild = T2;
	}
	void rightRotate(TreeNode<K, V>*& ptr)
	{
		TreeNode<K, V>* y = ptr;
		TreeNode<K, V>* x = y->lChild;
		TreeNode<K, V>* T2 = x->rChild;
		ptr = x;
		x->rChild = y;
		y->lChild = T2;
	}
	void delete_(K key, TreeNode<K, V>* &ptr)
	{
		if (ptr == nullptr)
			return;
		else if (key < ptr->key)
		{
			delete_(key, ptr->lChild);
		}
		else if (key > ptr->key)
		{
			delete_(key, ptr->rChild);
		}
		else
		{
			//case 0: leaf node
			if (ptr->isLeaf())
			{
				delete ptr;
				ptr = nullptr;
			}
			//case 1.1: only left child exists
			else if (ptr->lChild && !ptr->rChild)
			{
				TreeNode<K, V>* delNode = ptr;
				ptr = ptr->lChild;
				delete delNode;
			}
			//case 1.2: only right child exists
			else if (!ptr->lChild && ptr->rChild)
			{
				TreeNode<K, V>* delNode = ptr;
				ptr = ptr->rChild;
				delete delNode;
			}
			//case 2: both children exits
			else
			{
				TreeNode<K, V>* successor = ptr->rChild;
				while (successor->lChild)
					successor = successor->lChild;

				ptr->key = successor->key;
				ptr->value = successor->value;
				delete_(successor->key, ptr->rChild);

			}
		}
	}//end of delete

	V* searchtree(K key, TreeNode<K, V>* ptr) //normally searches the tree, used when searched is needed to in search function
	{
		if (ptr == nullptr)
			return nullptr;
		else if (key < ptr->key)
			return this->searchtree(key, ptr->lChild);
		else if (key > ptr->key)
			return this->searchtree(key, ptr->rChild);
		else return &ptr->value;
	}
	void deleteAll(TreeNode<K, V>* ptr)
	{
		if (ptr)
		{
			deleteAll(ptr->lChild);
			deleteAll(ptr->rChild);
			delete ptr;
		}
	}
	void inorderPrint(TreeNode<K, V>* ptr, vector<V>*vec)
	{
		if (ptr)
		{

			inorderPrint(ptr->lChild, vec);
			vec->push_back(ptr->value);
			inorderPrint(ptr->rChild, vec);
		}
	}
public:
	SpecialBST() {
		this->root = nullptr;
	}

/*	void makeroot(TreeNode<K,V>*& ptr) {
		TreeNode<K, V>* temp;
		K key = ptr->key;
		while (this->root->key != key) {
			temp = FindParent(key);
			if (temp->rChild == ptr) { // if the child is on right side of parent
				cout << "rotation left" << endl;
				leftRotate(temp);
			}
			else if(temp->lChild == ptr){
				cout << "rotation right" << endl;
				//cout << key << " " << this->root->key << endl;
				cout << temp->key << endl;
				cout << this->root->key << endl;
				rightRotate(temp);		
				cout << temp->key << endl;
				cout << this->root->key << endl;
			//	cout << key << " " << this->root->key << endl;
			}
		}
	} */
	void makeroot(TreeNode<K, V>*&ptr, TreeNode<K, V>*ptr2) { //This function makes ptr2 the new root of BST
		if (ptr == ptr2) {
			return;
		}
		else if(ptr->key > ptr2->key)
		{
			makeroot(ptr->lChild, ptr2);
		}
		else if(ptr->key < ptr2->key)
		{
			makeroot(ptr->rChild, ptr2);
		}
		if (ptr->key < ptr2->key)
		{
			if (ptr->rChild) {
				leftRotate(ptr);
			}
		}
		else
		{
			if (ptr->lChild) {
				rightRotate(ptr);
			}
		}
	}

	TreeNode<K, V>* FindParent(K key, TreeNode<K, V>*&ptr) { //This function is to find the parent of the pointer passed and return its pointer
		if (ptr->rChild || ptr->lChild) {
			//cout << "Inside" << endl;
			if (ptr->rChild) {
				if (ptr->rChild->key == key) {
				//	cout << "Right" << endl;
					return ptr;
				}
			}
			 if (ptr->lChild) {
				if (ptr->lChild->key == key) {
					//cout << "Left" << endl;
					return ptr;
				}
			}
		}
		if (key < ptr->key) {
			//cout << "Left" << endl;
			return this->FindParent(key, ptr->lChild);
		}
		if (key > ptr->key)
		{
		//	cout << "Right" << endl;
			return this->FindParent(key, ptr->rChild);
		}
		if (this->root->key == key) {
			return nullptr;
		}
	}
	TreeNode<K, V>* FindParent(K key) {
		return this->FindParent(key, this->root);
	}
	bool delete_(K key)
	{
		TreeNode<K, V>* temp;
		if (searchtree(key)) {
				temp = FindParent(key); //meaning that the deleted node is root node
				if (temp != nullptr) {
					//cout << temp->key << endl;
					delete_(key, this->root);
					//cout << this->root->key << endl;
					makeroot(this->root, temp);
					//cout << this->root->key << endl;
					return true;
				}
				else
				{
					delete_(key, this->root);
					return true;
				}			
		}
		else
		{
			search(key, this->root);
			return false;
		}
	}
	bool insert(K _key, V _value) {
		TreeNode<K, V>* temp;
		if (IsDuplicate(_key, this->root)) {
			return false;
		}
		this->insert(_key, _value, this->root);
		return true;
	}
	V* searchtree(K key)
	{
		return this->searchtree(key, this->root);
	}

	V* search(K key)
	{
		return this->search(key, this->root);
	}
	~SpecialBST()
	{
		this->deleteAll(this->root);
	}
	vector<V>* getValuesLevelWise() { //level wise printing
		if (this->root == nullptr) {
			cout << "The tree is empty !" << endl;
			return nullptr;
		}

		queue<TreeNode<K,V>*> q;
		q.push(this->root);

		vector<V>* vec = new vector<V>;

		while (!q.empty())
		{
			TreeNode<K, V>* ptr = q.front();
			q.pop();
			vec->push_back(ptr->value);

			if (ptr->lChild)
				q.push(ptr->lChild);
			if (ptr->rChild)
				q.push(ptr->rChild);
		}
		return vec;
	}
	vector<V>* inorderPrintKeys()
	{
		vector<V>*vec = new vector<V>;
		inorderPrint(this->root, vec);
		return vec;
	}
};
struct StudentData {
public:
	int RollNo;
	string FirstName;
	string LastName;
	string department;
	int batch;
	float cgpa;
	StudentData(int _RollNo, string _FirstName, string _LastName, string _department, int _batch, float _cgpa) { 
		this->RollNo = _RollNo;
		this->FirstName = _FirstName;
		this->LastName = _LastName;
		this->department = _department;
		this->batch = _batch;
		this->cgpa = _cgpa;
	}
/*	StudentData(StudentData& data) {
		this->RollNo = data.RollNo;
		this->FirstName = data.FirstName;
		this->LastName = data.LastName;
		this->department = data.department;
		this->batch = data.batch;
		this->cgpa = data.cgpa;
	}*/
	StudentData() {

	}
};
class StudentList {
	SpecialBST<int, StudentData> BST;
public: 
	bool InsertNewStudent(int rollNumber, string firstName, string lastName, int batch, string department, float cgpa) //passes and calls original BST function
	{
		StudentData data(rollNumber, firstName, lastName,  department, batch, cgpa);
		return BST.insert(rollNumber, data);
		
	}
	bool deleteStudent(int rollNumber) //Calls the delete function from original BST
	{
	return BST.delete_(rollNumber);
	}
	bool updateStudent(int oldRollNumber, int newRollNumber, string newFirstName, string newLastName, int newBatch, string newDepartment, float newCgpa)
	{		//The update function with its conditions 
		StudentData* data;
		if (oldRollNumber == newRollNumber)
		{
			if (!(BST.search(oldRollNumber)))
			{
				cout << "The Roll_No to be changed does not exist in the tree" << endl;
				return false;
			}
			else
			{
				data = BST.search(oldRollNumber);
				data->FirstName = newFirstName;
				data->LastName = newLastName;
				data->department = newDepartment;
				data->cgpa = newCgpa;
				data->batch = newBatch;
				return true;
			}
		}
		else
		{
			if (!(BST.search(oldRollNumber)))
			{
				cout << "The Roll No to be changed does not exist in the tree" << endl;
				return false;
			}
			else if (BST.search(newRollNumber))
			{
				cout << "The new Roll No to be changed already exists in the tree" << endl;
				return false;
			}
			data = BST.search(oldRollNumber);
			this->deleteStudent(oldRollNumber);
			this->InsertNewStudent(newRollNumber, newFirstName, newLastName, newBatch, newDepartment, newCgpa);
			
			return true;
		}
	}


	void printAllStudents()
	{					//this function prints all of the students in BST
		vector<StudentData>* vec;
		StudentData* data;
		vec = BST.inorderPrintKeys();
		cout << "Total Students: " << vec->size() << endl << endl;
		for (int i = 0; i < vec->size(); i++)
		{
			data = &(vec->at(i));
			cout << "Roll Number: " << data->RollNo << endl;
			cout << "First Name: " << data->FirstName << endl;
			cout << "Last Name: " << data->LastName << endl;
			cout << "Batch: " << data->batch << endl;
			cout << "Department: " << data->department << endl;
			cout << "CGPA: " << data->cgpa << endl;
			cout << endl << endl;
		}
	}
	void print()		//pretty obvious what it does
	{
		cout << "Press 'I' to insert a new student." << endl;
		cout << "Press 'D' to delete a student." << endl;
		cout << "Press 'S' to search a student by roll number." << endl;
		cout << "Press 'U' to update the data of a student." << endl;
		cout << "Press 'P' to print all the students sorted by roll number." << endl;
		cout << "Press 'E' to exit. " << endl;
	}
	void SearchPrint(int RollNo) //Function to search a rollNo and print its data
	{
		
		StudentData* data;
		data = BST.searchtree(RollNo);
		if (data)
		{
			cout << "Roll Number: " << data->RollNo << endl;
			cout << "First Name: " << data->FirstName << endl;
			cout << "Last Name: " << data->LastName << endl;
			cout << "Batch: " << data->batch << endl;
			cout << "Department: " << data->department << endl;
			cout << "CGPA: " << data->cgpa << endl;
			cout << endl;
		}
		else
		{
			cout << "The entered Roll No does not exist" << endl;
		}
	}
	~StudentList()
	{

	}
};

void main() {

	StudentList List;
	char choice = 'X';
	string FirstName;
	string LastName;
	string department;
	float cgpa;
	int batch;
	int Roll_No;
	int OldRoll_No;
	bool duplicatecheck;						//simple main printing
	do{								
		List.print();
		cout << endl;
		cout << "Please enter your choice: ";
		cin >> choice;
		cout << endl << endl;
		if (choice == 'I')
		{
			cout << "Please enter the relevant data of new student !" << endl;
			cout << "Roll_No: ";
			cin >> Roll_No;
			cout << "First Name: ";
			cin >> FirstName;
			cout << "Last Name: ";
			cin >> LastName;
			cout << "Department: ";
			cin >> department;
			cout << "CGPA: ";
			cin >> cgpa;
			cout << "Batch: ";
			cin >> batch;
			if (Roll_No < 0 || cgpa > 4.0 || cgpa < 0.0 || batch < 0)
			{
				cout << "Error, you have entered invalid input" << endl;
				continue;
			}
			duplicatecheck = List.InsertNewStudent(Roll_No, FirstName, LastName, batch, department, cgpa);
			if (!(duplicatecheck))
			{
				cout << "Error, duplication found" << endl;
			}
			else
			{
				cout << "Successfully Inserted" << endl;
			}
			
		}
		else  if (choice == 'D')
		{
			cout << "Please enter the roll number of student that you want to delete: ";
			cin >> Roll_No;
			duplicatecheck = List.deleteStudent(Roll_No);
			if (duplicatecheck)
			{
				cout << "Deleted Successfully." << endl;
			}
			else
			{
				cout << "The Roll_No does not exist" << endl;
			}
		}
		else if (choice == 'S')
		{
			cout << "Please enter the roll number of student that you want to search: ";
			cin >> Roll_No;
			List.SearchPrint(Roll_No);
		}
		else if (choice == 'U')
		{
			cout << "Please enter the roll number that you want update: ";
			cin >> OldRoll_No;
			cout << "Please enter the relevant data of new student !" << endl;
			cout << "Roll_No: ";
			cin >> Roll_No;
			cout << "First Name: ";
			cin >> FirstName;
			cout << "Last Name: ";
			cin >> LastName;
			cout << "Department: ";
			cin >> department;
			cout << "CGPA: ";
			cin >> cgpa;
			cout << "Batch: ";
			cin >> batch;
			duplicatecheck = List.updateStudent(OldRoll_No, Roll_No, FirstName, LastName, batch, department, cgpa);
			if (duplicatecheck)
			{
				cout << "SuccessFully Updated" << endl;
			}
			else
			{
				cout << "Could not update the information" << endl;
			}
		}
		else if (choice == 'P')
		{
			List.printAllStudents();
		}
		else if(choice != 'E')
		{
			cout << "Invalid choice, Please try again " << endl;
		}
	
		
		
		cout << endl << endl;
	}while (choice != 'E');

	system("pause");
}