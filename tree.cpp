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
			Node *tmp = node->getRightNode();
			node->setRightNode(tmp->getLeftNode());

			if (tmp->getLeftNode() != NULL)
				tmp->getLeftNode()->setParentNode(node);
			
			tmp->setParentNode(node->getParentNode());
			if (node->getParentNode() == NULL)
				this->_root = tmp;
			else if (node == node->getParentNode()->getLeftNode())
				node->getParentNode()->setLeftNode(tmp);
			else
				node->getParentNode()->setRightNode(tmp);
			tmp->setLeftNode(node);
			node->setParentNode(tmp);
		}
		
		void rotateRight(Node *node)
		{
			Node *tmp = node->getLeftNode();
			node->setLeftNode(tmp->getRightNode());

			if (tmp->getRightNode() != NULL)
				tmp->getRightNode()->setParentNode(node);
			
			tmp->setParentNode(node->getParentNode());
			if (node->getParentNode() == NULL)
				this->_root = tmp;
			else if (node == node->getParentNode()->getRightNode())
				node->getParentNode()->setRightNode(tmp);
			else
				node->getParentNode()->setLeftNode(tmp);
			tmp->setRightNode(node);
			node->setParentNode(tmp);
		}

		void fixNode(Node *node)
		{
			Node *currentNode = node;

			while(currentNode->getParentNode() != NULL && currentNode->getParentNode()->getColor() == RED)
			{
				Node *grandparent = currentNode->getParentNode()->getParentNode();

				if(grandparent->getLeftNode() == currentNode->getParentNode())
				{
					if(grandparent->getRightNode() != NULL)
					{
						tmp = grandparent->getRightNode();
						if(tmp->getColor() == RED)
						{
							node->getParentNode()->setColor(BLACK);
							tmp->setColor(BLACK);
							grandparent->setColor(RED);
							currentNode = grandparent;
						}
					}
					else
					{
						if (currentNode->getParentNode()->getRightNode() == currentNode)
						{
							currentNode = currentNode->getParentNode();
							this->rotateLeft(currentNode);
						}
						currentNode->getParentNode()->setColor(BLACK);
						grandparent->setColor(RED);
						this->rotateRight(grandparent);
					}
				}
				else
				{
					if(grandparent->getLeftNode() != NULL)
					{
						tmp = grandparent->getLeftNode();
						if (tmp->getColor() == RED)
						{
							currentNode->getParentNode()->setColor(BLACK);
							tmp->setColor(BLACK);
							grandparent->setColor(RED);
							currentNode = grandparent;
						}
					}
					else
					{
						if (currentNode->getParentNode()->getLeftNode() == currentNode)
						{
							currentNode = currentNode->getParentNode();
							this->rotateRight(currentNode);
						}
						currentNode->getParentNode()->setColor(BLACK);
						grandparent->setColor(RED);
						this->rotateLeft(grandparent);
					}
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

			if (node->getParentNode() != NULL && node->getParentNode()->getColor() == RED)
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

	tree.insert(new Node(50));
	tree.insert(new Node(51));
	tree.insert(new Node(52));
	tree.insert(new Node(59));
	tree.insert(new Node(55));
	tree.insert(new Node(56));


	tree.print();

}