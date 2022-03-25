#pragma once
#include <cstddef>
#include <iostream>
#include <utility>
#include "../pair.hpp"

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
	typedef Compare key_compare;

	//FIXME: usar allocator
	RedBlackTree() : allocator_(Allocator()), comp_(Compare())
	{
		root_ = new Node();
	}

	RedBlackTree(const RedBlackTree &tree) {
		this->root_ = tree.getRoot();
		this->comp_ = tree.comp_;
	}

	RedBlackTree &operator=(const RedBlackTree &tree) {
		this->root_ = tree.getRoot();
		this->comp_ = tree.comp_;

		return *this;
	}

	//TODO:
	~RedBlackTree() {

	}

	Node *minimum(Node *node) const
	{
		while (!node->left->isEmpty()) {
			node = node->left;
		}
		return node;
	}

	Node *maximum(Node *node) const
	{
		while (!node->right->isEmpty()) {
			node = node->right;
		}
		return node;
	}

	void leftRotate(Node *x)
	{
		Node *y = x->right;
		x->right = y->left;
		if (!y->left->isEmpty())
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
		if (!y->right->isEmpty()) {
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

	ft::pair<Node *, bool> insert(const value_type &data)
	{
		Node *new_node;
		Node *current_node;
		Node *last_node;

		if (this->root_->isEmpty()) {
			new_node = createNewNode(data);
			this->root_ = new_node;
			new_node->color = BLACK;
			return ft::make_pair(new_node, true);
		}

		current_node = this->root_;
		while (!current_node->isEmpty()) {
			last_node = current_node;

			if (data.first == current_node->data.first) {
				return ft::make_pair(current_node, false);
			}
			else if (data.first < current_node->data.first) {
				current_node = current_node->left;
			}
			else {
				current_node = current_node->right;
			}
		}

		new_node = createNewNode(data);
		new_node->parent = last_node;
		if (data.first < last_node->data.first) {
			last_node->left = new_node;
		}
		else  {
			last_node->right = new_node;
		}
		
		insertFix(new_node);
		return ft::make_pair(new_node, true);
	}
	
	ft::pair<Node *, bool> insertWithHint(Node *nodeHint, const value_type &data)
	{
		Node *new_node;
		Node *current_node;
		Node *last_node;
		bool correct_hint;

		if (this->root_->isEmpty()) {
			new_node = createNewNode(data);
			this->root_ = new_node;
			new_node->color = BLACK;
			return ft::make_pair(new_node, true);
		}

		correct_hint = checkHint(nodeHint, data);

		if (correct_hint)
			current_node = nodeHint;
		else
			current_node = this->root_;
		
		while (!current_node->isEmpty()) {
			last_node = current_node;

			if (data.first == current_node->data.first) {
				return ft::make_pair(current_node, false);
			}
			else if (data.first < current_node->data.first) {
				current_node = current_node->left;
			}
			else {
				current_node = current_node->right;
			}
		}

		new_node = createNewNode(data);
		new_node->parent = last_node;
		if (data.first < last_node->data.first) {
			last_node->left = new_node;
		}
		else  {
			last_node->right = new_node;
		}
		
		insertFix(new_node);
		return ft::make_pair(new_node, true);
	}


	bool deleteNode(typename value_type::first_type &key) {
		return deleteNodeHelper(this->root_, key);
	}

	Node *getRoot() const {
		return this->root_;
	}

	void printHelper(Node *root, std::string indent, bool last) {
		if (!root->isEmpty()) {
			std::cout << indent;
			if (last) {
				std::cout << "R----";
				indent += "   ";
			} else {
				std::cout << "L----";
				indent += "|  ";
			}
			
			std::cout	<< "[" << root->data.first <<"] " 
						<< root->data.second << "("
						<< (root->color == RED ? "RED" : "BLACK") << ")"
						<< std::endl;
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

	Node *findByKey(const typename value_type::first_type &key) const {

		Node *curretNode = this->root_;

		while (!curretNode->isEmpty()) {
			
			if (curretNode->data.first == key)
				return curretNode;
			else if (key < curretNode->data.first)
				curretNode = curretNode->left;
			else
				curretNode = curretNode->right;
		}

		return NULL;
	}

	Node *next(Node *node) {
		
		Node *p;

		if (!node->right->isEmpty()) {
			node = node->right;
			while (!node->left->isEmpty())
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

	Node *prev(Node *node) {
		Node *p;

		if (node == NULL) {
			node = this->maximum(this->getRoot());
			return node;
		}

		if (!node->left->isEmpty()) {
			node = node->left;
			while (!node->right->isEmpty())
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


private:

	Node *createNewNode(const value_type &data) {
		Node *node = this->allocator_.allocate(1);

		this->allocator_.construct(node, Node(data));
		node->parent = NULL;
		node->left = new Node();
		node->right = new Node();
		node->color = RED;

		return node;
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
		if (u->parent == NULL) {
			root_ = v;
		}
		else if (u == u->parent->left) {
			u->parent->left = v;
		}
		else {
			u->parent->right = v;
		}
		v->parent = u->parent;
	}

	bool deleteNodeHelper(Node *node, typename value_type::first_type &key)
	{
		Node *z = new Node();
		Node *x, *y;

		while (!node->isEmpty())
		{
			if (node->data.first == key) {
				z = node;
			}

			if (node->data.first <= key) {
				node = node->right;
			}
			else {
				node = node->left;
			}
		}

		if (z->isEmpty()) {
			return false;
		}

		y = z;
		int y_original_color = y->color;
		if (z->left->isEmpty()) {
			x = z->right;
			this->swap(z, z->right);
		}
		else if (z->right->isEmpty()) {
			x = z->left;
			this->swap(z, z->left);
		}
		else {
			y = this->minimum(z->right);
			y_original_color = y->color;
			x = y->right;
			if (y->parent == z) {
				x->parent = y;
			}
			else {
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
		if (y_original_color == 0) {
			deleteFix(x);
		}
		
		return true;
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

	bool checkHint(Node *node, const value_type &data) {
		Node *next_node = this->next(node);

		if (node->data.first < data.first &&  data.first < node->data.first)
			return true;

		return false;
	}

	Node *root_;
	Allocator allocator_;
	Compare comp_;

};

}