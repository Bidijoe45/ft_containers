
#include <iostream>

using namespace std;

enum NodeColor {
	BLACK = 0,
	RED = 1
};

struct Node {
	int data; 
	Node *parent; 
	Node *left;
	Node *right; 
	int color;
};

typedef Node * NodePtr;

class RBTree {
private:
	NodePtr root;
	NodePtr TNULL;
	std::allocator<Node> allocator_;

	void fixDelete(NodePtr x) {
		NodePtr s;
		while (x != root && x->color == BLACK) {
			if (x == x->parent->left) {
				s = x->parent->right;
				if (s->color == RED) {
					s->color = 0;
					x->parent->color = 1;
					leftRotate(x->parent);
					s = x->parent->right;
				}

				if (s->left->color == BLACK && s->right->color == BLACK) {
					s->color = 1;
					x = x->parent;
				} else {
					if (s->right->color == BLACK) {
						s->left->color = 0;
						s->color = 1;
						rightRotate(s);
						s = x->parent->right;
					} 

					s->color = x->parent->color;
					x->parent->color = 0;
					s->right->color = 0;
					leftRotate(x->parent);
					x = root;
				}
			} else {
				s = x->parent->left;
				if (s->color == RED) {
					s->color = 0;
					x->parent->color = 1;
					rightRotate(x->parent);
					s = x->parent->left;
				}

				if (s->right->color == BLACK && s->right->color == BLACK) {
					s->color = 1;
					x = x->parent;
				} else {
					if (s->left->color == BLACK) {
						s->right->color = 0;
						s->color = 1;
						leftRotate(s);
						s = x->parent->left;
					} 

					s->color = x->parent->color;
					x->parent->color = 0;
					s->left->color = 0;
					rightRotate(x->parent);
					x = root;
				}
			} 
		}
		x->color = 0;
	}


	void rbTransplant(NodePtr u, NodePtr v){
		if (u->parent == NULL) {
			root = v;
		} else if (u == u->parent->left){
			u->parent->left = v;
		} else {
			u->parent->right = v;
		}
		v->parent = u->parent;
	}

	void deleteNodeHelper(NodePtr node, int key) {
		NodePtr z = TNULL;
		NodePtr x, y;
		while (node != TNULL){
			if (node->data == key) {
				z = node;
			}

			if (node->data <= key) {
				node = node->right;
			} else {
				node = node->left;
			}
		}

		if (z == TNULL) {
			return;
		} 

		y = z;
		int y_original_color = y->color;
		if (z->left == TNULL) {
			x = z->right;
			rbTransplant(z, z->right);
		} else if (z->right == TNULL) {
			x = z->left;
			rbTransplant(z, z->left);
		} else {
			y = minimum(z->right);
			y_original_color = y->color;
			x = y->right;
			if (y->parent == z) {
				x->parent = y;
			} else {
				rbTransplant(y, y->right);
				y->right = z->right;
				y->right->parent = y;
			}

			rbTransplant(z, y);
			y->left = z->left;
			y->left->parent = y;
			y->color = z->color;
		}

		allocator_.destroy(z);
		allocator_.deallocate(z, 1);

		if (y_original_color == 0){
			fixDelete(x);
		}
	}

	void fixInsert(NodePtr k){
		NodePtr u;
		while (k->parent->color == RED) {
			if (k->parent == k->parent->parent->right) {
				u = k->parent->parent->left;
				if (u->color == RED) {
					u->color = 0;
					k->parent->color = 0;
					k->parent->parent->color = 1;
					k = k->parent->parent;
				} else {
					if (k == k->parent->left) {
						k = k->parent;
						rightRotate(k);
					}
					k->parent->color = 0;
					k->parent->parent->color = 1;
					leftRotate(k->parent->parent);
				}
			} else {
				u = k->parent->parent->right; 

				if (u->color == RED) {
					u->color = 0;
					k->parent->color = 0;
					k->parent->parent->color = 1;
					k = k->parent->parent;	
				} else {
					if (k == k->parent->right) {
						k = k->parent;
						leftRotate(k);
					}
					k->parent->color = 0;
					k->parent->parent->color = 1;
					rightRotate(k->parent->parent);
				}
			}
			if (k == root) {
				break;
			}
		}
		root->color = 0;
	}

public:
	RBTree() {
		TNULL = allocator_.allocate(1);
		allocator_.construct(TNULL, Node());
		TNULL->color = 0;
		TNULL->left = NULL;
		TNULL->right = NULL;
		root = TNULL;
	}

	~RBTree() {
		this->clearTree(root);

		allocator_.destroy(TNULL);
		allocator_.deallocate(TNULL, 1);
	}

	void clearTree(NodePtr node) {
		
		if (node == TNULL)
			return ;

		clearTree(node->left);	
		clearTree(node->right);

		allocator_.destroy(node);
		allocator_.deallocate(node, 1);
	} 

	NodePtr minimum(NodePtr node) {
		while (node->left != TNULL) {
			node = node->left;
		}
		return node;
	}

	NodePtr maximum(NodePtr node) {
		while (node->right != TNULL) {
			node = node->right;
		}
		return node;
	}

	void leftRotate(NodePtr x) {
		NodePtr y = x->right;
		x->right = y->left;
		if (y->left != TNULL) {
			y->left->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == NULL) {
			this->root = y;
		} else if (x == x->parent->left) {
			x->parent->left = y;
		} else {
			x->parent->right = y;
		}
		y->left = x;
		x->parent = y;
	}

	void rightRotate(NodePtr x) {
		NodePtr y = x->left;
		x->left = y->right;
		if (y->right != TNULL) {
			y->right->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == NULL) {
			this->root = y;
		} else if (x == x->parent->right) {
			x->parent->right = y;
		} else {
			x->parent->left = y;
		}
		y->right = x;
		x->parent = y;
	}

	NodePtr createNewNode(int key) {
		NodePtr node = allocator_.allocate(1);
		allocator_.construct(node, Node());
		node->parent = NULL;
		node->data = key;
		node->left = TNULL;
		node->right = TNULL;
		node->color = 1;

		return node;
	}

	void insert(int key) {
		

		NodePtr y = NULL;
		NodePtr x = this->root;

		while (x != TNULL) {
			y = x;
			if (key == x->data) {
				return ;
			}
			else if (key < x->data) {
				x = x->left;
			} else {
				x = x->right;
			}
		}

		NodePtr node = createNewNode(key);

		node->parent = y;
		if (y == NULL) {
			root = node;
		} else if (node->data < y->data) {
			y->left = node;
		} else {
			y->right = node;
		}

		if (node->parent == NULL){
			node->color = 0;
			return;
		}

		if (node->parent->parent == NULL) {
			return;
		}

		fixInsert(node);
	}

	NodePtr getRoot(){
		return this->root;
	}

	void deleteNode(int data) {
		deleteNodeHelper(this->root, data);
	}

	void prettyPrint() {
	    if (root) {
    		printHelper(this->root, "", true);
	    }
	}

	void printHelper(NodePtr root, string indent, bool last) {
	   	if (root != TNULL) {
		   cout<<indent;
		   if (last) {
		      cout<<"R----";
		      indent += "     ";
		   } else {
		      cout<<"L----";
		      indent += "|    ";
		   }
            
           string sColor = root->color?"RED":"BLACK";
		   cout<<root->data<<"("<<sColor<<")"<<endl;
		   printHelper(root->left, indent, false);
		   printHelper(root->right, indent, true);
		}
	}

};

void check_leaks() {
	system("leaks a.out");
}

int main() {
	
	atexit(&check_leaks);
	
	RBTree bst;
	bst.insert(8);
	bst.insert(18);
	bst.insert(18);
	bst.insert(5);
	bst.insert(15);
	bst.insert(17);
	bst.insert(25);
	bst.insert(40);
	bst.insert(80);
	bst.deleteNode(25);
	bst.deleteNode(8);
	
	bst.prettyPrint();

	return 0;
}