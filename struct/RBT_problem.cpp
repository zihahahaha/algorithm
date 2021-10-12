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
	RBNode* upper_bound(int key);
	void update();
	void inorder_tree_walk(RBNode* node);
	void dfs(RBNode* now, int n);
private:
	static RBNode* root;
	void insert_fixup(RBNode* node);
	void remove_fixup(RBNode* node);
	RBNode* get_unclenode(RBNode* node);
	void left_rotate(RBNode* node);
	void right_rotate(RBNode* node);
	void transplant(RBNode* delete_node, RBNode* v) {
		if (delete_node == RBTree::root)
			RBTree::root = v;
		else if (delete_node == delete_node->p->left)
			delete_node->p->left = v;
		else
			delete_node->p->right = v;
		if (v != nullptr)
			v->p = delete_node->p;
		delete delete_node;
	}
	RBNode* minNode(RBNode* node) {
		while (node->left != nullptr)
			node = node->left;
		return node;
	}
	void rotate(RBNode* node, bool flag) {
		if (flag == true)
			left_rotate(node);
		else
			right_rotate(node);
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

//都以父节点为准
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
			if (node->p == node->p->p->left) {
				//case 2.1,transform to case 2.1*
				if (node == node->p->right) {
					node = node->p;
					left_rotate(node);
				}
				node->p->color = RBNode::black;
				node->p->p->color = RBNode::red;
				right_rotate(node->p->p);
			}
			else {
				//case 2.2,transform to case 2.2*
				if (node == node->p->left) {
					node = node->p;
					right_rotate(node);
				}
				node->p->color = RBNode::black;
				node->p->p->color = RBNode::red;
				left_rotate(node->p->p);
			}
		}
	}
	RBTree::root->color = RBNode::black;
}

RBNode* RBTree::find(int key) {
	RBNode* now = RBTree::root;
	while (now != nullptr) {
		if (key < now->key)
			now = now->left;
		else if (key > now->key)
			now = now->right;
		else
			return now;
	}
	return now;
}


void RBTree::remove(int key) {
	RBNode* now = find(key);
	RBNode* fix_node = nullptr;
	if (now != nullptr) {
		if (now->left == nullptr) {
			if (now->right != nullptr) {
				now->right->color = RBNode::black;
				transplant(now, now->right);
			}
			else if (now->color == RBNode::red)
				transplant(now, now->right);
			//节点度0的修复情况
			else
				fix_node = now;
		}
		else if (now->right == nullptr) {
			now->left->color = RBNode::black;
			transplant(now, now->left);
		}
		else {
			RBNode* successor = minNode(now->right);
			now->key = successor->key;
			now = successor;
			if (now->right != nullptr) {
				now->right->color = RBNode::black;
				transplant(now, now->right);
			}
			else if (now->color == RBNode::red)
				transplant(now, now->right);
			else
				fix_node = now;
		}
		if (fix_node) {
			cout << "should fix\n";
			remove_fixup(fix_node);
		}
	}
}

void RBTree::remove_fixup(RBNode* node) {
	RBNode* delete_node = node;
	//case 1
	if (node == RBTree::root) {
		RBTree::root = nullptr;
	}
	else
		while (node->color == RBNode::black && node != RBTree::root) {
			//修复节点肯定有兄弟???
			RBNode* cousin = nullptr;
			bool flag;
			if (node == node->p->left) {
				cousin = node->p->right;
				flag = true;
			}
			else {
				cousin = node->p->left;
				flag = false;
			}
			//case 2
			if (cousin->color == RBNode::red) {
				cousin->color = RBNode::black;
				node->p->color = RBNode::red;
				rotate(node->p, flag);
				if (flag)
					cousin = node->p->right;
				else
					cousin = node->p->left;
			}
			else {
				//case 3.1
				if ((cousin->left == nullptr || cousin->left->color == RBNode::black)
					&& (cousin->right == nullptr || cousin->right->color == RBNode::black)) {
					cousin->color = RBNode::red;
					node = node->p;

				}
				//case 3.2 to case 3.3
				else {
					if (flag) {
						if ((cousin->left != nullptr && cousin->left->color == RBNode::red)
							&& (cousin->right == nullptr || cousin->right->color == RBNode::black)) {
							cousin->color = RBNode::red;
							cousin->left->color = RBNode::black;
							right_rotate(cousin);
						}
					}
					else {
						if ((cousin->left == nullptr || cousin->left->color == RBNode::black)
							&& (cousin->right != nullptr && cousin->right->color == RBNode::red)) {
							cousin->color = RBNode::red;
							cousin->right->color = RBNode::black;
							left_rotate(cousin);
						}
					}
					//case 3.3
					cousin->color = node->p->color;
					cousin->p->color = RBNode::black;
					if (flag)
						cousin->right->color = RBNode::black;
					else
						cousin->left->color = RBNode::black;
					rotate(cousin->p, flag);
					if (flag)
						node->p->left = nullptr;
					else
						node->p->right = nullptr;
					break;
				}
			}
		}
	node->color = RBNode::black;
	if (delete_node->p != nullptr)
		if (delete_node == delete_node->p->left)
			delete_node->p->left = nullptr;
		else
			delete_node->p->right = nullptr;
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
	tree.insert(1);
	tree.insert(2);
	tree.insert(3);
	tree.insert(10);
	tree.insert(4);
	tree.remove(1);
	tree.insert(0);
	tree.remove(3);
	tree.remove(10);
	tree.remove(0);
	tree.insert(12);
	tree.insert(15);
	tree.insert(8);
	tree.insert(5);
	tree.insert(3);
	tree.remove(8);
	tree.remove(5);
	tree.insert(100);
	tree.remove(3);
	tree.inorder_tree_walk();
	tree.dfs();
}
