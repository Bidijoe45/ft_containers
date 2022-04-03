#pragma once
#include <iostream>
#include "../pair.hpp"

namespace ft {

enum NodeColor {
	BLACK = 0,
	RED = 1
};

template<class T>
struct Node {
	T data; 
	Node *parent; 
	Node *left;
	Node *right; 
	NodeColor color;

	Node() : data() {}

	Node(T data) : data(data) { }

};

template <class T, class Node, class Compare, class Allocator = std::allocator<Node> >
class RedBalckTree {

private:
	typedef T value_type;
	typedef Node* NodePtr;
	NodePtr root;
	NodePtr TNULL;
	Compare comp_;
	std::allocator<Node> allocator_;

	void fixDelete(NodePtr x) {
		NodePtr s;
		while (x != root && x->color == BLACK) {
			if (x == x->parent->left) {
				s = x->parent->right;
				if (s->color == RED) {
					s->color = BLACK;
					x->parent->color = RED;
					leftRotate(x->parent);
					s = x->parent->right;
				}

				if (s->left->color == BLACK && s->right->color == BLACK) {
					s->color = RED;
					x = x->parent;
				} else {
					if (s->right->color == BLACK) {
						s->left->color = BLACK;
						s->color = RED;
						rightRotate(s);
						s = x->parent->right;
					} 

					s->color = x->parent->color;
					x->parent->color = BLACK;
					s->right->color = BLACK;
					leftRotate(x->parent);
					x = root;
				}
			} else {
				s = x->parent->left;
				if (s->color == RED) {
					s->color = BLACK;
					x->parent->color = RED;
					rightRotate(x->parent);
					s = x->parent->left;
				}

				if (s->right->color == BLACK && s->right->color == BLACK) {
					s->color = RED;
					x = x->parent;
				} else {
					if (s->left->color == BLACK) {
						s->right->color = BLACK;
						s->color = RED;
						leftRotate(s);
						s = x->parent->left;
					} 

					s->color = x->parent->color;
					x->parent->color = BLACK;
					s->left->color = BLACK;
					rightRotate(x->parent);
					x = root;
				}
			} 
		}
		x->color = BLACK;
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

	bool deleteNodeHelper(NodePtr node, typename value_type::first_type key) {
		NodePtr z = TNULL;
		NodePtr x, y;
		while (node != TNULL){
			if (node->data.first == key) {
				z = node;
			}

			if (node->data.first <= key) {
				node = node->right;
			} else {
				node = node->left;
			}
		}

		if (z == TNULL) {
			return false;
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
		return true;
	}

	void fixInsert(NodePtr k){
		NodePtr u;
		while (k->parent->color == RED) {
			if (k->parent == k->parent->parent->right) {
				u = k->parent->parent->left;
				if (u->color == RED) {
					u->color = BLACK;
					k->parent->color = BLACK;
					k->parent->parent->color = RED;
					k = k->parent->parent;
				} else {
					if (k == k->parent->left) {
						k = k->parent;
						rightRotate(k);
					}
					k->parent->color = BLACK;
					k->parent->parent->color = RED;
					leftRotate(k->parent->parent);
				}
			} else {
				u = k->parent->parent->right; 

				if (u->color == RED) {
					u->color = BLACK;
					k->parent->color = BLACK;
					k->parent->parent->color = RED;
					k = k->parent->parent;	
				} else {
					if (k == k->parent->right) {
						k = k->parent;
						leftRotate(k);
					}
					k->parent->color = BLACK;
					k->parent->parent->color = RED;
					rightRotate(k->parent->parent);
				}
			}
			if (k == root) {
				break;
			}
		}
		root->color = BLACK;
	}

public:
	RedBalckTree() {
		TNULL = allocator_.allocate(1);
		allocator_.construct(TNULL, Node());
		TNULL->color = BLACK;
		TNULL->left = NULL;
		TNULL->right = NULL;
		root = TNULL;
		comp_ = Compare();
	}
	~RedBalckTree() {
		this->clearTree(root);

		allocator_.destroy(TNULL);
		allocator_.deallocate(TNULL, 1);
	}

	void clearTree(NodePtr node) {
		
		if (node == NULL || node == TNULL)
			return ;

		clearTree(node->left);	
		clearTree(node->right);

		allocator_.destroy(node);
		allocator_.deallocate(node, 1);
		this->root = TNULL;
	} 

	NodePtr minimum(NodePtr node) const {
		if (node == NULL || node == TNULL)
			return NULL;
		
		while (node->left != TNULL) {
			node = node->left;
		}
		return node;
	}

	NodePtr maximum(NodePtr node) const {
		if (node == TNULL)
			return NULL;

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

	NodePtr createNewNode(value_type key) {
		NodePtr node = allocator_.allocate(1);
		allocator_.construct(node, Node(key));
		node->parent = NULL;
		node->left = TNULL;
		node->right = TNULL;
		node->color = RED;

		return node;
	}

	NodePtr next(NodePtr node) const {
		
		Node *p;
		
		if (node == NULL)
			return NULL;
		else if (node->right != TNULL) {
			node = node->right;
			while (node->left != TNULL)
				node = node->left;
		} else {
			p = node->parent;
			while (p != NULL && node == p->right) {
				node = p;
				p = p->parent;
			}
			node = p;
		}

		return node;
	}

	NodePtr prev(NodePtr node) const {
		NodePtr p;

		if (node == NULL) {
			node = this->maximum(this->getRoot());
			return node;
		}

		if (node->left != TNULL) {
			node = node->left;
			while (node->right != TNULL)
				node = node->right;
		} else {
			p = node->parent;
			while (p != NULL && node == p->left) {
				node = p;
				p = p->parent;
			}
			node = p;
		}

		return node;	
	}

ft::pair<NodePtr, bool> insert(value_type key, NodePtr nodeHint = NULL) {

		if (nodeHint == NULL)
			nodeHint = this->root;

		NodePtr y = NULL;
		NodePtr x = nodeHint;

		while (x != TNULL) {
			y = x;
			if (key.first == x->data.first) {
				return ft::make_pair(x, false);
			}
			else if (comp_(key.first, x->data.first)) {
				x = x->left;
			} else {
				x = x->right;
			}
		}

		NodePtr node = createNewNode(key);
		node->parent = y;
		if (y == NULL) {
			root = node;
		} else if (comp_(node->data.first, y->data.first)) {
			y->left = node;
		} else {
			y->right = node;
		}

		if (node->parent == NULL){
			node->color = BLACK;
			return ft::make_pair(node, true);
		}

		if (node->parent->parent == NULL) {
			return ft::make_pair(node, true);
		}

		fixInsert(node);
		return ft::make_pair(node, true);
	}

	ft::pair<NodePtr, bool> insertWithHint(NodePtr nodeHint, value_type key) {
		NodePtr next_node = this->next(nodeHint);

		if (next_node == NULL)
			return this->insert(key);

		if (this->comp_(nodeHint->data.first, key.first) && this->comp_(key.first, nodeHint->data.first))
			return this->insert(key, nodeHint);

		return this->insert(key);
	}

	NodePtr findByKey(const typename value_type::first_type &key) const {

		NodePtr curretNode = this->root;

		while (curretNode != TNULL) {
			
			if (curretNode->data.first == key)
				return curretNode;
			else if (this->comp_(key, curretNode->data.first))
				curretNode = curretNode->left;
			else
				curretNode = curretNode->right;
		}

		return NULL;
	}

	NodePtr getNullNode() const {
		return this->TNULL;
	}

	void setNullNode(NodePtr node) {
		this->TNULL = node;
	}

	NodePtr getRoot() const {
		if (this->root == TNULL) {
			return NULL;
		}
		return this->root;
	}

	void setRoot(NodePtr newRoot) {
		this->root = newRoot;
	}

	bool deleteNode(typename value_type::first_type &data) {
		return deleteNodeHelper(this->root, data);
	}

	void prettyPrint() {
	    if (root) {
    		printHelper(this->root, "", true);
	    }
	}

	void printHelper(NodePtr root, std::string indent, bool last) {
	   	if (root != TNULL) {
		   std::cout<<indent;
		   if (last) {
		      std::cout<<"R----";
		      indent += "     ";
		   } else {
		      std::cout<<"L----";
		      indent += "|    ";
		   }
            
           std::string sColor = root->color?"RED":"BLACK";
		   std::cout<< "[" << root->data.first << "] => " << root->data.second <<" ("<<sColor<<")"<<std::endl;
		   printHelper(root->left, indent, false);
		   printHelper(root->right, indent, true);
		}
	}

};

}

