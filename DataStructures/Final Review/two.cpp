#include <iostream>
#include <queue>
using namespace std;

class Stack {
	class Element {
		int key, int value;
	};
	priority_queue<int> q;

	int top = 0;

	void push(int key);
};

void Stack::push(int key) {
	q.push(Element(top++, key));
}

int main() {
	priority_queue<int> one;



	return 0;
}