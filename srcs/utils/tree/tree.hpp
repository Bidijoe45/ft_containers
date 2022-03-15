#pragma once
#include <cstddef>
#include <iostream>

#include <utility>

#include "./tree_iterator.hpp"

namespace ft
{

enum NodeColor
{
	BLACK,
	RED
};

template <class T>
struct Node
{
	typedef T value_type;

	value_type data;
	Node *parent;
	Node *left;
	Node *right;
	NodeColor color;
	bool empty;

	Node() : data(), empty(true) { }

	Node(value_type data) : data(data), empty(false) { }

	bool isEmpty() const {
		return empty;
	}

};

template <class T, class Node, class Compare, class Allocator = std::allocator<Node> >
class RedBlackTree
{

public:
	typedef T value_type;
	typedef ft::tree_iterator<Node, Compare> iterator;

	RedBlackTree() : allocator_(Allocator())
	{
		emptyNode_ = createEmptyNode();
		root_ = emptyNode_;
	}

	~RedBlackTree()
	{
		delete this->emptyNode_;
	}

	Node *searchTree(int k)
	{
		return searchTreeHelper(this->root_, k);
	}

	Node *minimum(Node *node)
	{
		while (node->left != emptyNode_)
		{
			node = node->left;
		}
		return node;
	}

	Node *maximum(Node *node)
	{
		while (node->right != emptyNode_)
		{
			node = node->right;
		}
		return node;
	}

	void leftRotate(Node *x)
	{
		Node *y = x->right;
		x->right = y->left;
		if (y->left != emptyNode_)
		{
			y->left->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == NULL)
		{
			this->root_ = y;
		}
		else if (x == x->parent->left)
		{
			x->parent->left = y;
		}
		else
		{
			x->parent->right = y;
		}
		y->left = x;
		x->parent = y;
	}

	void rightRotate(Node *x)
	{
		Node *y = x->left;
		x->left = y->right;
		if (y->right != emptyNode_)
		{
			y->right->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == NULL)
		{
			this->root_ = y;
		}
		else if (x == x->parent->right)
		{
			x->parent->right = y;
		}
		else
		{
			x->parent->left = y;
		}
		y->right = x;
		x->parent = y;
	}

	std::pair<iterator, bool> insert(const value_type &data)
	{
		Node *node = this->allocator_.allocate(1);
		this->allocator_.construct(node, Node(data));
		node->parent = NULL;
		node->left = emptyNode_;
		node->right = emptyNode_;
		node->color = RED;

		Node *y = NULL;
		Node *x = this->root_;

		while (x != emptyNode_) {
			y = x;
			if (node->data.first < x->data.first) {
				x = x->left;
			} else {
				x = x->right;
			}
		}

		node->parent = y;
		if (y == NULL) {
			root_ = node;
		}
		else if (node->data.first < y->data.first) {
			y->left = node;
		}
		else {
			y->right = node;
		}

		if (node->parent == NULL) {
			node->color = BLACK;
			return std::make_pair(iterator(node), true);
		}

		if (node->parent->parent == NULL) {
			return std::make_pair(iterator(node), true);
		}

		insertFix(node);
		return std::make_pair(iterator(node), true);
	}

	void deleteNode(int data)
	{
		deleteNodeHelper(this->root_, data);
	}

	Node *getRoot() const {
		return this->root_;
	}

	void printHelper(Node *root, std::string indent, bool last) {
		if (root != this->emptyNode_) {
			std::cout << indent;
			if (last) {
				std::cout << "R----";
				indent += "   ";
			} else {
				std::cout << "L----";
				indent += "|  ";
			}

			
			std::cout << "[" << root->data.first <<"] " << root->data.second << "(" << (root->color == RED ? "RED" : "BLACK") << ")" << std::endl;
			printHelper(root->left, indent, false);
			printHelper(root->right, indent, true);
		}
	}

	void printTree()
	{
		if (this->root_)
		{
			printHelper(this->root_, "", true);
		}
	}

private:
	Node *root_;
	Node *emptyNode_;
	Allocator allocator_;

	Node *createEmptyNode() {
		Node *emptyNode_ = new Node();
		emptyNode_->color = BLACK;
		emptyNode_->left = NULL;
		emptyNode_->right = NULL;
		return emptyNode_;
	}

	Node *searchTreeHelper(Node *node, int key)
	{
		if (node == emptyNode_ || key == node->data)
		{
			return node;
		}

		if (key < node->data)
		{
			return searchTreeHelper(node->left, key);
		}
		return searchTreeHelper(node->right, key);
	}

	void deleteFix(Node *x)
	{
		Node *s;
		while (x != root_ && x->color == BLACK)
		{
			if (x == x->parent->left)
			{
				s = x->parent->right;
				if (s->color == RED)
				{
					s->color = BLACK;
					x->parent->color = RED;
					this->leftRotate(x->parent);
					s = x->parent->right;
				}

				if (s->left->color == BLACK && s->right->color == BLACK)
				{
					s->color = RED;
					x = x->parent;
				}
				else
				{
					if (s->right->color == BLACK)
					{
						s->left->color = BLACK;
						s->color = RED;
						this->rightRotate(s);
						s = x->parent->right;
					}

					s->color = x->parent->color;
					x->parent->color = BLACK;
					s->right->color = BLACK;
					this->leftRotate(x->parent);
					x = root_;
				}
			}
			else
			{
				s = x->parent->left;
				if (s->color == RED)
				{
					s->color = BLACK;
					x->parent->color = RED;
					this->rightRotate(x->parent);
					s = x->parent->left;
				}

				if (s->right->color == BLACK && s->right->color == BLACK)
				{
					s->color = RED;
					x = x->parent;
				}
				else
				{
					if (s->left->color == BLACK)
					{
						s->right->color = BLACK;
						s->color = RED;
						this->leftRotate(s);
						s = x->parent->left;
					}

					s->color = x->parent->color;
					x->parent->color = BLACK;
					s->left->color = BLACK;
					this->rightRotate(x->parent);
					x = root_;
				}
			}
		}
		x->color = BLACK;
	}

	void swap(Node *u, Node *v)
	{
		if (u->parent == NULL)
		{
			root_ = v;
		}
		else if (u == u->parent->left)
		{
			u->parent->left = v;
		}
		else
		{
			u->parent->right = v;
		}
		v->parent = u->parent;
	}

	void deleteNodeHelper(Node *node, int key)
	{
		Node *z = emptyNode_;
		Node *x, *y;
		while (node != emptyNode_)
		{
			if (node->data == key)
			{
				z = node;
			}

			if (node->data <= key)
			{
				node = node->right;
			}
			else
			{
				node = node->left;
			}
		}

		if (z == emptyNode_)
		{
			return;
		}

		y = z;
		int y_original_color = y->color;
		if (z->left == emptyNode_)
		{
			x = z->right;
			this->swap(z, z->right);
		}
		else if (z->right == emptyNode_)
		{
			x = z->left;
			this->swap(z, z->left);
		}
		else
		{
			y = this->minimum(z->right);
			y_original_color = y->color;
			x = y->right;
			if (y->parent == z)
			{
				x->parent = y;
			}
			else
			{
				this->swap(y, y->right);
				y->right = z->right;
				y->right->parent = y;
			}

			this->swap(z, y);
			y->left = z->left;
			y->left->parent = y;
			y->color = z->color;
		}
		delete z;
		if (y_original_color == 0)
		{
			deleteFix(x);
		}
	}

	void insertFix(Node *k)
	{
		Node *u;
		while (k->parent->color == RED)
		{
			if (k->parent == k->parent->parent->right)
			{
				u = k->parent->parent->left;
				if (u->color == RED)
				{
					u->color = BLACK;
					k->parent->color = BLACK;
					k->parent->parent->color = RED;
					k = k->parent->parent;
				}
				else
				{
					if (k == k->parent->left)
					{
						k = k->parent;
						this->rightRotate(k);
					}
					k->parent->color = BLACK;
					k->parent->parent->color = RED;
					this->leftRotate(k->parent->parent);
				}
			}
			else
			{
				u = k->parent->parent->right;

				if (u->color == RED)
				{
					u->color = BLACK;
					k->parent->color = BLACK;
					k->parent->parent->color = RED;
					k = k->parent->parent;
				}
				else
				{
					if (k == k->parent->right)
					{
						k = k->parent;
						this->leftRotate(k);
					}
					k->parent->color = BLACK;
					k->parent->parent->color = RED;
					this->rightRotate(k->parent->parent);
				}
			}
			if (k == root_)
			{
				break;
			}
		}
		root_->color = BLACK;
	}
};

}