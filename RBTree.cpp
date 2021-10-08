#define WARNING_DISABLE_M

#ifdef WARNING_DISABLE_M
#pragma warning(disable:26812)
#endif

#include<iostream>
using namespace std;

struct Node {
	Node(int m_key) :key(m_key) {}
	int key;
};

struct RBNode
	:public Node
{
	static enum Color :bool { red = 0, black = 1 };
	RBNode(int key) :Node(key) {}
	Color color = red;
	RBNode* left = nullptr;
	RBNode* right = nullptr;
	RBNode* p = nullptr;
};

class RBTree {
public:
	void insert(int key);
	void remove(int key);
	RBNode* find(int key);
	void update();
	void inorder_tree_walk(RBNode* node);
	void dfs(RBNode* now, int n);
private:
	static RBNode* root;
	void insert_fixup(RBNode* node);
	RBNode* get_unclenode(RBNode* node);
	void left_rotate(RBNode* node);
	void right_rotate(RBNode* node);
	RBNode* transplant(RBNode* delete_node, RBNode* v) {
		if (delete_node == RBTree::root)
			RBTree::root = v;
		else if (delete_node == delete_node->p->left)
			delete_node->p->left = v;
		else
			delete_node->p->right = v;
		if (v != nullptr)
			v->p = delete_node->p;
		delete delete_node;
		return v;
	}

};

RBNode* RBTree::root = nullptr;


void RBTree::insert(int key) {
	RBNode* node = new RBNode(key);
	if (root == nullptr) {
		node->color = RBNode::black;
		root = node;
	}
	else {
		RBNode* now = RBTree::root;
		RBNode* p = nullptr;
		while (now != nullptr) {
			p = now;
			if (key <= now->key)
				now = now->left;
			else
				now = now->right;
		}
		node->p = p;
		if (node->key <= p->key)
			p->left = node;
		else
			p->right = node;
		insert_fixup(node);
	}
}

RBNode* RBTree::get_unclenode(RBNode* node) {
	if (node->p == node->p->p->left)
		return node->p->p->right;
	else
		return node->p->p->left;
}

void RBTree::left_rotate(RBNode* node) {
	RBNode* y = node->right;
	y->p = node->p;
	if (y->p == nullptr)
		RBTree::root = y;
	else if (node == node->p->left)
		y->p->left = y;
	else
		y->p->right = y;

	node->right = y->left;

	y->left = node;
	y->left->p = y;

	if (node->right != nullptr)
		node->right->p = node;
}

void RBTree::right_rotate(RBNode* node) {
	RBNode* y = node->left;
	y->p = node->p;
	if (y->p == nullptr)
		RBTree::root = y;
	else if (node == node->p->left)
		y->p->left = y;
	else
		y->p->right = y;

	node->left = y->right;

	y->right = node;
	node->p = y;

	if (node->right != nullptr)
		node->right->p = node;
}

void RBTree::insert_fixup(RBNode* node) {
	while (node->p != nullptr && node->p->color == RBNode::red) {
		RBNode* uncle = this->get_unclenode(node);
		//uncle node is red
		if (uncle != nullptr && uncle->color == RBNode::red) {
			node->p->color = uncle->color = RBNode::black;
			uncle->p->color = RBNode::red;
			node = node->p->p;
		}
		else {
			//case 2,transform to case 3
			if (node == node->p->right) {
				node = node->p;
				left_rotate(node);
			}
			//case 3
			node->p->color = RBNode::black;
			node->p->p->color = RBNode::red;
			//father node is left node
			if (node->p == node->p->p->left)
				right_rotate(node->p->p);
			//or father node is right node
			else
				left_rotate(node->p->p);
		}
	}
	RBTree::root->color = RBNode::black;
}

RBNode* RBTree::find(int key) {
	RBNode* now = RBTree::root;
	while (now != nullptr) {
		if (key < now->left->key)
			now = now->left;
		else if (key > now->right->key)
			now = now->right;
		else
			return now;
	}
	return now;
}


void RBTree::remove(int key) {
	RBNode* now = find(key);
	if (now != nullptr) {
		//case 1
		RBNode* v;
		if (now->left == nullptr)
			v = transplant(now, now->right);
		else
			v = transplant(now, now->left);
		if (v != nullptr)
			v->color = RBNode::black;
	}
}
void RBTree::inorder_tree_walk(RBNode* now = RBTree::root) {
	if (now == nullptr)
		return;
	else {
		inorder_tree_walk(now->left);
		cout << "key: " << now->key << " " << "color: " << (now->color == RBNode::red ? "red" : "black") << endl;
		inorder_tree_walk(now->right);
	}
}

void RBTree::dfs(RBNode* now = RBTree::root, int n = 0) {
	if (now->color == RBNode::black)
		n++;
	if (now->left != nullptr)
		this->dfs(now->left, n);
	if (now->right != nullptr)
		this->dfs(now->right, n);
	if (now->left == nullptr && now->right == nullptr) {
		cout << n << endl;
	}
}
int main() {
	RBTree tree;
	tree.insert(4);
	tree.insert(2);
	tree.insert(3);
	tree.insert(10);
	tree.insert(0);
	tree.insert(7);
	
	tree.inorder_tree_walk();
	tree.dfs();
}
