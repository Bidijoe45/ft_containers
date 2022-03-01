#include <iostream>
#include <vector>

enum RedBlackTreeNodeColor { RED, BLACK };

template<class T>
class RedBalckTreeNode {

	public:
		typedef RedBalckTreeNode Node;
		typedef RedBlackTreeNodeColor Color;

		RedBalckTreeNode() {
			this->_parent = NULL;
			this->_left = NULL;
			this->_right = NULL;
			this->_color = RED;
		}

		RedBalckTreeNode(T value) {
			this->_parent = NULL;
			this->_left = NULL;
			this->_right = NULL;
			this->_color = RED;
			this->_value = value;
		}

		T &getValue() { return this->_value; }
		Node *getParentNode() { return this->_parent; }
		Node *getLeftNode() { return this->_left; }
		Node *getRightNode() { return this->_right; }
		Color getColor() { return this->_color; }

		void setValue(T value) { this->_value = value; }
		void setParentNode(Node *node) { this->_parent = node; }
		void setLeftNode(Node *node) { this->_left = node; }
		void setRightNode(Node *node) { this->_right = node; }
		void setColor(Color color) { this->_color = color; }

	private:
		T _value;
		Node *_parent;
		Node *_left;
		Node *_right;
		Color _color;
};

template<class T>
class RedBalckTree {

	public:
		typedef RedBalckTreeNode<T> Node;
		typedef T value_type;
		typedef RedBlackTreeNodeColor Color;

		RedBalckTree() {
			this->_root = NULL;
		}

		void print()
		{
			if (this->_root == NULL)
			{
				std::cout << "Empty Tree" << std::endl;
				return ;
			}

			std::vector<Node *> print_queue;

			print_queue.push_back(this->_root);

			while (!print_queue.empty())
			{
				Node *actual_node = print_queue.front();
				printNode(*actual_node);

				if (actual_node->getLeftNode())
					print_queue.push_back(actual_node->getLeftNode());
				if (actual_node->getRightNode())
					print_queue.push_back(actual_node->getRightNode());
				print_queue.erase(print_queue.begin());
			}
			
		}

		void rotateLeft(Node *node)
		{
			Node *parent = node->getParentNode();
			Node *grandparent = parent->getParentNode();
			Node *grand_grandparent = grandparent->getParentNode();

			if (grand_grandparent == NULL)
			{
				this->_root = parent;
				parent->setParentNode(NULL);
			}
			else
			{
				parent->setParentNode(grand_grandparent);
				if (grandparent == grand_grandparent->getLeftNode())
					grand_grandparent->setRightNode(parent);
				else
					grand_grandparent->setLeftNode(parent);
			}

			grandparent->setRightNode(parent->getLeftNode());
			grandparent->setParentNode(parent);
			parent->setLeftNode(grandparent);
		}

		void rotateRight(Node *node)
		{
			Node *parent = node->getParentNode();
			Node *grandparent = parent->getParentNode();
			Node *grand_grandparent = grandparent->getParentNode();

			if (grand_grandparent == NULL)
			{
				this->_root = parent;
				parent->setParentNode(NULL);
			}
			else
			{
				parent->setParentNode(grand_grandparent);
				if (grandparent == grand_grandparent->getLeftNode())
					grand_grandparent->setLeftNode(parent);
				else
					grand_grandparent->setRightNode(parent);
			}

			grandparent->setLeftNode(parent->getRightNode());
			grandparent->setParentNode(parent);
			parent->setRightNode(grandparent);
			
		}

		void fixNode(Node *node)
		{
			Node *currentNode = node;

			while (currentNode->getParentNode()->getColor() == RED)
			{
				Node *parent = currentNode->getParentNode();
				Node *grandparent = parent->getParentNode();
				Node *parent_sibling;

				if (parent == grandparent->getRightNode())
				{
					parent_sibling = grandparent->getRightNode();

					std::cout << "llega 111" << std::endl;

					if (parent_sibling != NULL && parent_sibling->getColor() == RED)
					{
						parent->setColor(BLACK);
						parent_sibling->setColor(BLACK);
						grandparent->setColor(RED);
						currentNode = grandparent;
					}
					else
					{
						if (currentNode == parent->getLeftNode())
						{
							currentNode = parent;
							this->rotateRight(currentNode);
						}
						parent->setColor(BLACK);
						grandparent->setColor(RED);
						this->rotateLeft(grandparent);
					}
					std::cout << "llega 121" << std::endl;

				}
				else
				{
					parent_sibling = grandparent->getLeftNode();

					std::cout << "llega 211" << std::endl;
					if (parent_sibling != NULL && parent_sibling->getColor() == RED)
					{
						grandparent->setColor(RED);
						parent->setColor(BLACK);
						parent_sibling->setColor(BLACK);
						currentNode = grandparent;
					}
					else
					{
						if (currentNode == parent->getRightNode())
						{
							currentNode = parent;
							this->rotateLeft(currentNode);
						}
						parent->setColor(BLACK);
						grandparent->setColor(RED);
						this->rotateRight(grandparent);
					}
					std::cout << "llega 221" << std::endl;


					if (currentNode == this->_root)
						break ;
				}
			
				this->_root->setColor(BLACK);
			}
		
		}

		void insert(Node *node)
		{
			if (this->_root == NULL)
			{
				node->setColor(BLACK);
				this->_root = node;

				return;
			}

			Node *actual_node;
			Node *tmp = this->_root;

			while (tmp != NULL)
			{
				actual_node = tmp;
				if (node->getValue() < actual_node->getValue())
					tmp = actual_node->getLeftNode();
				else
					tmp = actual_node->getRightNode();
			}

			node->setParentNode(actual_node);

			if (node->getValue() < actual_node->getValue())
				actual_node->setLeftNode(node);
			else
				actual_node->setRightNode(node);

			if (node->getParentNode() != NULL)
				if (node->getParentNode()->getColor() == RED)
					this->fixNode(node);
		}

	private:
		Node *_root;

		void printNode(Node &node)
		{
			if (node.getColor() == BLACK)
				std::cout << "\x1b[44m";
			if (node.getColor() == RED)
				std::cout << "\x1b[41m";

			std::cout << "--- NODE ---" << std::endl;
			std::cout << "\x1b[0m";

			std::cout << "Value: " << node.getValue() << std::endl;
			if (node.getParentNode())
				std::cout << "Parent: " << node.getParentNode()->getValue() << std::endl;
			if (node.getLeftNode())
				std::cout << "Left: " << node.getLeftNode()->getValue() << std::endl;
			if (node.getRightNode())
				std::cout << "Right: " << node.getRightNode()->getValue() << std::endl;
		}

};


int main() {

	RedBalckTree<int> tree;

	typedef RedBalckTreeNode<int> Node;

	tree.insert(new Node(5));
	tree.insert(new Node(10));
	tree.insert(new Node(15));
	tree.insert(new Node(21));
	tree.insert(new Node(23));


	tree.print();

}