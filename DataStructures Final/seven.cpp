#include <iostream>
#include <string>
using namespace std;

class IntBinaryTree {
private:
	class TreeNode {
		friend class IntBinaryTree;
		int value;
		TreeNode *left;
		TreeNode *right;
		TreeNode(int value1, TreeNode *left1 = NULL,
			TreeNode *right1 = NULL) {
			value = value1;
			left = left1;
			right = right1;
		}
	};

	TreeNode *root;
	void insert(TreeNode *&, int);
	void destroySubtree(TreeNode *);
	void remove(TreeNode *&, int);
	void makeDeletion(TreeNode *&);
	void displayInOrder(TreeNode *) const;
	void displayPreOrder(TreeNode *) const;
	void displayPostOrder(TreeNode *) const;
	void increment(TreeNode *) const;
	int largest(TreeNode *) const;
	int count(TreeNode *, int ) const;
	int height(TreeNode *, int, int ) const;

public:

	IntBinaryTree() {
		root = NULL;
	}
	~IntBinaryTree() {
		destroySubtree(root);
	}
	void insert(int num) {
		insert(root, num);
	}
	bool search(int) const;
	void remove(int num) {
		remove(root, num);
	}
	void showInOrder(void) const {
		displayInOrder(root);
	}
	void showPreOrder() const {
		displayPreOrder(root);
	}
	void showPostOrder() const {
		displayPostOrder(root);
	}
	void plusOne() const{
		increment(root);
	}
	int large() const{
		return largest(root);
	}
	int total() const {
		int tot = 0;
		return count(root, tot);
	}
	int altitude() const {
		int l = 1;
		int r = 1;
		return height(root, l, r);
	}
};

int IntBinaryTree::height(TreeNode *tree, int l, int r) const {
	if (total() == 1)
		return 1;
	if (tree->left != NULL) {
		l++;
		l = height(tree->left, l, r);
	}
	if(tree->left == NULL && tree->right != NULL) {
		l = height(tree->right, l, r);
	}
	
	// if(l < r)
	// 	l = r;
	// if (tree->left != NULL) {
	// 	l++;
	// 	l = height(tree->left, l, r);
	// }
	// if (tree->right != NULL) {
	// 	r++;
	// 	r = height(tree->right, l, r);
	// }
	int hl = l;
	int hr = 0;

	if(hl >= hr)
		return hl;
	else if (hl < hr)
		return hr;
	return 0;
}

int IntBinaryTree::count(TreeNode *tree, int tot) const{
	tot++;
	if (tree->left != NULL)
		tot = count(tree->left, tot);
	if (tree->right != NULL)
		tot = count(tree->right, tot);

	return tot;
}

void IntBinaryTree::increment(TreeNode *tree) const {
	if(tree) {
		tree->value += 1;
		increment(tree->left);
		increment(tree->right);
	}
}

int IntBinaryTree::largest(TreeNode *tree) const {
	int high = tree->value;
	tree = tree->right;
	while (tree) {
		high = tree->value;
		tree = tree->right;
	}

	return high;
}

void IntBinaryTree::insert(TreeNode * &tree, int num) {
	if(!tree) {
		tree = new TreeNode(num);
		return;
	}
	if(tree->value == num) {
		return;
	}
	if(num < tree->value)
		insert(tree->left, num);
	else
		insert(tree->right, num);
}

void IntBinaryTree::destroySubtree(TreeNode *tree) {
	if(!tree) return;
	destroySubtree(tree->left);
	destroySubtree(tree->right);
	delete tree;
}

bool IntBinaryTree::search(int num) const {
	TreeNode *tree = root;

	while (tree) {
		if(tree->value == num)
			return true;
		else if( num < tree->value)
			tree = tree->left;
		else 
			tree = tree->right;
	}
	return false;
}

void IntBinaryTree::remove(TreeNode *&tree, int num) {
	if (tree == NULL) return;
	if(num < tree->value)
		remove(tree->left, num);
	else if (num > tree->value)
		remove(tree->right, num);
	else
		makeDeletion(tree);
}

void IntBinaryTree::makeDeletion(TreeNode *&tree) {
	TreeNode *nodeToDelete = tree;
	TreeNode *attachPoint;

	if(tree->right == NULL) {
		tree = tree->left;
	}
	else if(tree->left == NULL) {
		tree = tree->right;
	}
	else {
		attachPoint = tree->right;
		while(attachPoint->left != NULL)
			attachPoint = attachPoint->left;

		attachPoint->left = tree->left;
		tree = tree->right;
	}
	delete nodeToDelete;
}

void IntBinaryTree::displayInOrder(TreeNode *tree) const {
	if (tree) {
		displayInOrder(tree->left);
		cout << tree->value << " ";
		displayInOrder(tree->right);
	}
}

void IntBinaryTree::displayPreOrder(TreeNode *tree) const {
	if (tree) {
		cout << tree->value << " ";
		displayPreOrder(tree->left);
		displayPreOrder(tree->right);
	}
}

void IntBinaryTree::displayPostOrder(TreeNode *tree) const {
	if(tree) {
		displayPostOrder(tree->left);
		displayPostOrder(tree->right);
		cout << tree->value << " ";
	}
}

int main() {
	IntBinaryTree tree;
	cout << "Inserting the numbers 5, 8, 3, 12, 9, 1"
		", 1000, 3, 500.\n\n";
	tree.insert(6);
	// tree.insert(8);
	tree.insert(3);
	// tree.insert(12);
	// tree.insert(9);
	// tree.insert(1);
	tree.insert(5);
	// tree.insert(1000);
	// tree.insert(4);
	// tree.insert(2);
	// tree.insert(500);

	// tree.plusOne();

	cout << "Inorder traversal: ";
	tree.showInOrder();

	cout << "\n\nPreorder traversal: ";
	tree.showPreOrder();

	cout << "\n\nPostorder traversal: ";
	tree.showPostOrder();

	cout << "\n\nLargest is: " << tree.large();

	cout << "\n\nTotal number of nodes: " << tree.total();

	cout << "\n\nHeight: " << tree.altitude();

	if(tree.search(3)) {
		cout << "\n\n3 is found in the tree.\n";
	}
	else
		cout << "\n\n3 was not found in the tree.\n";

	cout << "\nDeleting 8...\n";
	tree.remove(8);
	cout << "\nDeleting 12...\n";
	tree.remove(12);
	cout << "Now, here are the nodes:\n";
	tree.showInOrder();
	cout << endl;
    
    return 0;
}
