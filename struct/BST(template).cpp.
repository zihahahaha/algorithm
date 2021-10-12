#include<iostream>
using namespace std;

template<typename K, typename D>
struct Node {
	Node(K m_key, D m_data) :key(m_key), data(m_data) {}
	K key;
	D data;
	Node<K, D>* left = nullptr;
	Node<K, D>* right = nullptr;
	Node<K, D>* parent = nullptr;
};

template<typename K, typename D>
class Binary_search_tree {
public:
	using NodeType = Node<K, D>;
	void insert(K key, D data);
	void insert_many(NodeType nodes[], int n);
	void remove(int n);
	NodeType* find(int key);
	NodeType* lower_bound(int key);
	NodeType* upper_bound(int key);
	void inorder_tree_walk(NodeType* x = root);
private:
	static NodeType* root;
	NodeType* maxNode(NodeType* node) {
		while (node->right != nullptr)
			node = node->right;
		return node;
	}
	NodeType* minNode(NodeType* node) {
		while (node->left != nullptr)
			node = node->left;
		return node;
	}
	//only change target and his father
	void transplant(NodeType* u, NodeType* v) {
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

template<typename K, typename D>
Node<K, D>* Binary_search_tree<K, D>::root = nullptr;

template<typename K, typename D>
void Binary_search_tree<K, D>::insert(K key, D data) {
	NodeType* now = root;
	NodeType* parent = nullptr;
	NodeType* t = new NodeType(key, data);
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

template<typename K, typename D>
void Binary_search_tree<K, D>::insert_many(Node<K, D> nodes[], int n) {
	for (int i = 0; i < n; ++i)
		insert(nodes[i].key,nodes[i].data);
}

template<typename K, typename D>
Node<K, D>* Binary_search_tree<K, D>::find(int key) {
	NodeType* now = this->root;
	while (now != nullptr)
		if (key < now->key)
			now = now->left;
		else if (key > now->key)
			now = now->right;
		else
			return now;
	return now;
}

template<typename K, typename D>
Node<K, D>* Binary_search_tree<K, D>::lower_bound(int key) {
	NodeType* now = this->find(key);
	if (now != nullptr)
		if (now->left != nullptr)
			return this->maxNode(now->left);
		else if (now->parent != nullptr) {
			NodeType* target = now->parent;
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

template<typename K, typename D>
Node<K, D>* Binary_search_tree<K, D>::upper_bound(int key) {
	NodeType* now = this->find(key);
	if (now != nullptr)
		if (now->right != nullptr)
			return this->minNode(now->right);
		else if (now->parent != nullptr) {
			NodeType* target = now->parent;
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

template<typename K, typename D>
void Binary_search_tree<K, D>::remove(int key) {
	NodeType* now = this->find(key);
	//don't have left child
	if (now != nullptr)
		if (now->left == nullptr)
			this->transplant(now, now->right);
	//don't have right child
		else if (now->right == nullptr) {
			this->transplant(now, now->left);
		}
		else {
			NodeType* successor = this->minNode(now->right);
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

template<typename K, typename D>
void Binary_search_tree<K, D>::inorder_tree_walk(Node<K, D>* x) {
	if (x != nullptr) {
		this->inorder_tree_walk(x->left);
		cout << x->data << " ";
		this->inorder_tree_walk(x->right);
	}
}

int main() {
	Binary_search_tree<int, const char*>tree;
	Binary_search_tree<int, const char*>::NodeType nodes[3] = {
		{1,"hello"},
		{5,"world"},
		{3,"!"}
	};
	tree.insert_many(nodes, 3);
	tree.inorder_tree_walk();
}
