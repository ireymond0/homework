/************************************************************
* ASSIGNMENT 3												*
* This program implements a priority queue using a 			*
* 	traditional linked-list									*
*															*
* Author:	Ian Reymond										*
* Date due:	08 May 2015										*
* Version: 1												*
************************************************************/
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/************************************************************
* PriorityQueue class to store the task list               *
************************************************************/
class PriorityQueue
{
private:
	/************************************************************
	* Task node class                                          *
	************************************************************/
	class NodeType
	{
	public:
		string task;	//name of the task
		int priority;		// priority of the task
		NodeType * next;  //points to the next task on the queue

		NodeType(string task = "", int priority = -1,
			NodeType * next = NULL)  //default constructor
		{
			this->task = task;  this->priority = priority;
			this->next = next;
		}
	};

public:
	PriorityQueue()
	{  //default constructor: creates an empty queue
		head = NULL; taskCount = 0;
	}
	~PriorityQueue();  //destructor: delete all tasks from the queue

	bool isEmpty() const;  //checks for the queue being empty

	int size() const;  //returns the number of tasks in the queue

	void insert(string taskName, int priority);
	//creates a task and inserts it in order of priority

	void min() const; //prints the task and its priority (the one with the 
	//highest priority)

	void removeMin();  //removes the highest priority task 
	//from the queue

	int findMax() const;	//find the lowest priority task

private:
	NodeType *head;  //head pointer to the list
	int taskCount;  //count of the number of tasks on the list

	void goNext(NodeType * & curr) const; //moves the pointer to point to
	//the next task

	void insertFront(string taskName, int priority); //insert a node
	//in front if it has the highest priority

	void insertBack(string taskName, int priority); //insert a node
	//in back if it has the lowest priority
};

void readFile(PriorityQueue &i, string file); //Function to read in the file

/************************************************************
* goNext() moves the current list pointer from one 			*
*	node to the next.										*
* Inputs:                                                  	*
*      pointer to the current node to moves             	*
* Return:                                                  	*
*      nothing                                             	*
************************************************************/
void PriorityQueue::goNext(NodeType * & curr) const
{
	curr = curr->next;
}

/************************************************************
* findMax() looks for the maximum key and therefore the 	*
*	the last node of the linked-list						*
* Inputs:                                                  	*
*      nothing								             	*
* Return:                                                  	*
*      integer corresponding to the maximum key            	*
************************************************************/
int PriorityQueue::findMax() const
{
	NodeType *current = head;
	if (isEmpty())
	{
		cout << "The queue is empty!" << endl;
		return -1;
	}

	while (current->next != NULL)
	{
		goNext(current);
	}
	return current->priority;
	current = NULL;
	delete current;
}

/************************************************************
* min() prints the lowest priority task and its key number	*
* Inputs:                                                  	*
*      nothing								             	*
* Return:                                                  	*
*      nothing									           	*
************************************************************/
void PriorityQueue::min() const
{
	cout << endl << head->task << " " << head->priority << endl;
}

/************************************************************
* size() returns the number of tasks in the queue			*
* Inputs:                                                  	*
*      nothing								             	*
* Return:                                                  	*
*      integer corresponding to the number of nodes        	*
************************************************************/
int PriorityQueue::size() const
{
	return taskCount;
}

/************************************************************
* isEmpty() checks if the queue is empty					*
* Inputs:                                                  	*
*      nothing								             	*
* Return:                                                  	*
*      true if empty or false if not isEmpty 	          	*
************************************************************/
bool PriorityQueue::isEmpty() const
{
	if (head == NULL)
	{
		return true;
	}
	else
		return false;
}

/************************************************************
* destructor 												*
* Inputs:                                                  	*
*      nothing								             	*
* Return:                                                  	*
*      nothing									           	*
************************************************************/
PriorityQueue::~PriorityQueue()
{
	while (head != NULL)
	{
		NodeType *del;
		del = head;
		goNext(head);
		delete del;
		del = NULL;
	}
	delete head;
}

/************************************************************
* insertBack() inserts a task at the end of the queue		*
* Inputs:                                                  	*
*      taskName and priority key				         	*
* Return:                                                  	*
*      nothing									           	*
************************************************************/
void PriorityQueue::insertBack(string taskName, int priority)
{
	NodeType *back = new NodeType(taskName, priority);
	NodeType *current = head;

	if (head == NULL)
	{
		head = back;
	}
	else
	{
		while (current->next != NULL)
		{
			goNext(current);
		}
		current->next = back;
	}
	back = current = NULL;
}

/************************************************************
* insertFront() inserts a task at the beginning of the 		*
* 	queue.													*
* Inputs:                                                  	*
*      taskname and priority key			             	*
* Return:                                                  	*
*      nothing									          	*
************************************************************/
void PriorityQueue::insertFront(string taskName, int priority)
{
	NodeType *front = new NodeType(taskName, priority);
	if (head == NULL)
	{
		head = front;
	}
	else
	{
		front->next = head;
		head = front;
	}
	front = NULL;
}

/************************************************************
* insert() inserts a task at the right place in the queue 	*
*	depending on its key value								*
* Inputs:                                                  	*
*      taksName and priority queue value	             	*
* Return:                                                  	*
*      nothing								            	*
************************************************************/
void PriorityQueue::insert(string taskName, int priority)
{
	int x;
	if (!isEmpty())
		x = findMax();

	if (head == NULL)
	{
		insertFront(taskName, priority);
	}
	else if (priority < head->priority)
	{
		insertFront(taskName, priority);
	}
	else if (priority > x)
	{
		insertBack(taskName, priority);
	}
	else
	{
		NodeType *ins = new NodeType(taskName, priority);
		NodeType *current = head->next;
		NodeType *before = head;
		while (current->priority < priority)
		{
			goNext(current);
			goNext(before);
		}
		before->next = ins;
		ins->next = current;
		current = ins = before = NULL;
	}
	taskCount++;
}

/************************************************************
* readFile() reads in the file which includes the tasks		*
* Inputs:                                                  	*
*      Reference to the PriorityQueue						*
* 	   file name							             	*
* Return:                                                  	*
*      nothing								            	*
************************************************************/
void readFile(PriorityQueue &i, string file)
{
	ifstream inFile;
	inFile.open(file, ios::in);
	if (!inFile)
	{
		cout << "File does not exist" << endl;
		return;
	}

	while (!inFile.eof())
	{
		string lines, task;
		getline(inFile, lines);
		int position = lines.find(" ");
		task = lines.substr(position + 1);
		string v = lines.substr(0, position);
		int value = atoi(v.c_str());
		i.insert(task, value);
	}
	inFile.close();
}

/************************************************************
* removeMin() removes the highest priority value			*
* Inputs:                                                  	*
*      nothing								             	*
* Return:                                                  	*
*      nothing								            	*
************************************************************/
void PriorityQueue::removeMin()
{
	if (isEmpty())
	{
		cout << "Queue is empty!";
		return;
	}
	NodeType *current = head;
	goNext(head);
	delete current;
	current = NULL;
	taskCount--;
}

int main()
{
	PriorityQueue one;
	readFile(one, "input.txt");
	while (!one.isEmpty())
	{
		one.min();
		one.removeMin();
	}

	//system("pause");
	return 0;
}

//Ian Reymond
