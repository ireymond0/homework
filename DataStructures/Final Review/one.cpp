#include <iostream>
#include <list>
using namespace std;

void shuffle(int cards[], int size) {
	list<int> one;
	list<int>two;
	int shuffled[size];

	for (int i = 0; i < size/2; i++) {
		one.push_back(cards[i]);
	}
	for (int i = size/2; i < size; i++) {
		two.push_back(cards[i]);
	}
	
	for (int i = 0; i < size; i++) {
		shuffled[i] = one.front();
		one.pop_front();
		++i;
		shuffled[i] = two.front();
		two.pop_front();
	}

	cout << "Shuffled: " << endl;
	for (int i = 0; i < size; i++){
		cout << shuffled[i] << ' ';
	}
	cout << endl;
}

int main() {
	int size = 56;
	int cards[size];

	for (int i = 0; i < 56; i++) {
		cards[i] = i+1;
	}
	shuffle(cards, size);
	return 0;
}