#include<iostream>
using namespace std;

struct Node {
	int key;
	Node* left = nullptr;
	Node* right = nullptr;
	Node* parent = nullptr;
};

class Binary_search_tree {
public:
	void insert(Node n);//pass
	void insert_many(Node nodes[], int n);//pass
	void remove(int n);
	Node* find(int key);//pass
	Node* lower_bound(int key);//pass
	Node* upper_bound(int key);//pass
	void inorder_tree_walk(Node* x = root);//pass
private:
	static Node* root;
	Node* maxNode(Node* node) {
		while (node->right != nullptr)
			node = node->right;
		return node;
	}
	Node* minNode(Node* node) {
		while (node->left != nullptr)
			node = node->left;
		return node;
	}
	//only change target and his father
	void transplant(Node* u, Node* v) {
		if (u == this->root)
			this->root = v;
		else if (u == u->parent->left)
			u->parent->left = v;
		else
			u->parent->right = v;
		if (v != nullptr)
			v->parent = u->parent;
	}
};

Node* Binary_search_tree::root = nullptr;

void Binary_search_tree::insert(Node n) {
	Node* now = root;
	Node* parent = nullptr;
	Node* t = new Node(n);
	//find the position for inserting
	while (now != nullptr) {
		parent = now;
		if (t->key <= now->key)
			now = now->left;
		else
			now = now->right;
	}
	t->parent = parent;
	if (parent == nullptr)
		root = t;
	else if (t->key <= parent->key) {
		parent->left = t;
	}
	else {
		parent->right = t;
	}
}

void Binary_search_tree::insert_many(Node nodes[], int n) {
	for (int i = 0; i < n; ++i)
		insert(nodes[i]);
}

Node* Binary_search_tree::find(int key) {
	Node* now = this->root;
	while (now != nullptr)
		if (key < now->key)
			now = now->left;
		else if (key > now->key)
			now = now->right;
		else
			return now;
	return now;
}

Node* Binary_search_tree::lower_bound(int key) {
	Node* now = this->find(key);
	if (now != nullptr)
		if (now->left != nullptr)
			return this->maxNode(now->left);
		else if (now->parent != nullptr) {
			Node* target = now->parent;
			while (target->left == now) {
				now = target;
				target = now->parent;
			}
			return target;
		}
		else
			return now;
	else
		return now;
}

Node* Binary_search_tree::upper_bound(int key) {
	Node* now = this->find(key);
	if (now != nullptr)
		if (now->right != nullptr)
			return this->minNode(now->right);
		else if (now->parent != nullptr) {
			Node* target = now->parent;
			while (target->right == now) {
				now = now->parent;
				target = now->parent;
			}
			return target;
		}
		else
			return now;
	else
		return now;

}

void Binary_search_tree::remove(int key) {
	Node* now = this->find(key);
	//don't have left child
	if (now != nullptr)
		if (now->left == nullptr)
			this->transplant(now, now->right);
	//don't have right child
		else if (now->right == nullptr) {
			this->transplant(now, now->left);
		}
		else {
			Node* successor = this->minNode(now->right);
			successor->left = now->left;
			now->left->parent = successor;
			if (successor == now->right)
				this->transplant(now, now->right);
			else {
				//build a child tree
				this->transplant(successor, successor->right);
				successor->right = now->right;
				now->right->parent = successor;

				this->transplant(now, successor);
			}
		}
}


int now = -0xffffff;

void Binary_search_tree::inorder_tree_walk(Node* x) {
	if (x != nullptr) {
		this->inorder_tree_walk(x->left);
		if (now <= x->key)
			now = x->key;
		else
			cout << "false\n";
		//cout << x->key << " ";
		this->inorder_tree_walk(x->right);
	}
}


void test() {
	Binary_search_tree tree;
	Node nodes[100];
	for (int i = 0; i < 1000; ++i) {
		nodes[i] = { rand() };
		tree.insert(nodes[i]);
		now = -0xffffff;
		tree.inorder_tree_walk();
	}
	for (int i = 99; i >= 0; --i) {
		tree.remove(nodes[i].key);
		now = -0xffffff;
		tree.inorder_tree_walk();
	}
}

int main() {
	test();
}
