#include <iostream>
#include <vector>

template<class T>
class TreeNode {

	public:
		typedef TreeNode Node;

		TreeNode() {
			this->_parent = NULL;
			this->_left = NULL;
			this->_right = NULL;
		}

		TreeNode(T value) {
			this->_parent = NULL;
			this->_left = NULL;
			this->_right = NULL;
			this->_value = value;
		}

		T &getValue() { return this->_value; }
		Node *getParentNode() { return this->_parent; }
		Node *getLeftNode() { return this->_left; }
		Node *getRightNode() { return this->_right; }

		Node *getSibling() {
			if (this->getParentNode() == NULL)
				return NULL;
			if (this->getParentNode()->getLeftNode() == this)
				return this->getParentNode()->getRightNode();
			else
				return this->getParentNode()->getLeftNode();
		}

		void setValue(T value) { this->_value = value; }
		void setParentNode(Node *node) { this->_parent = node; }
		void setLeftNode(Node *node) { this->_left = node; }
		void setRightNode(Node *node) { this->_right = node; }

	private:
		T _value;
		Node *_parent;
		Node *_left;
		Node *_right;
};

template<class T>
class Tree {

	public:
		typedef TreeNode<T> Node;
		typedef T value_type;

		Tree() {
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

		void insertNode(Node *node)
		{
			if (this->_root == NULL)
			{
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

		}

		Node *getMinimumOfRightSubtree(Node *node)
		{
			if (node->getRightNode() == NULL)
				return NULL;

			node = node->getRightNode();
			while (node->getLeftNode() != NULL)
				node = node->getLeftNode();

			return node;
		}


		void deleteNode(value_type value)
		{
			Node *current_node = this->_root;
			Node *left_child;
			Node *right_child;
			Node *parent;
			Node *minimumRight;

			while (current_node != NULL && current_node->getValue() != value)
			{
				if (value < current_node->getValue())
					current_node = current_node->getLeftNode();
				else
					current_node = current_node->getRightNode();
			}

			if (current_node == NULL)
				return ;

			left_child = current_node->getLeftNode();
			right_child = current_node->getRightNode();
			parent = current_node->getParentNode();

			if (left_child == NULL && right_child == NULL)
			{
				if (current_node == this->_root)
					this->_root = NULL;
				else if (parent->getLeftNode() == current_node)
					parent->setLeftNode(NULL);
				else
					parent->setRightNode(NULL);
			}
			else if (left_child != NULL && right_child == NULL)
			{
				if (current_node == this->_root)
					this->_root = left_child;
				else if (parent->getLeftNode() == current_node)
					parent->setLeftNode(left_child);
				else
					parent->setRightNode(left_child);
				left_child->setParentNode(parent);
			}
			else if (left_child == NULL && right_child != NULL)
			{
				if (current_node == this->_root)
					this->_root = right_child;
				else if (parent->getLeftNode() == current_node)
					parent->setLeftNode(right_child);
				else
					parent->setRightNode(right_child);
				right_child->setParentNode(parent);
			}
			else
			{
				minimumRight = this->getMinimumOfRightSubtree(current_node);
				
				if (right_child != minimumRight) {
					minimumRight->setRightNode(right_child);
					right_child->setParentNode(minimumRight);

					if (minimumRight->getParentNode()->getLeftNode() == minimumRight)
						minimumRight->getParentNode()->setLeftNode(NULL);
					else
						minimumRight->getParentNode()->setRightNode(NULL);
				}
				minimumRight->setLeftNode(left_child);
				minimumRight->setParentNode(parent);
				
				left_child->setParentNode(minimumRight);

				if (parent == NULL)
					this->_root = minimumRight;
				else if (parent->getLeftNode() == current_node)
					parent->setLeftNode(minimumRight);
				else
					parent->setRightNode(minimumRight);
			}

			delete current_node;
		}

	private:
		Node *_root;

		void printNode(Node &node)
		{
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

	Tree<int> tree;

	typedef TreeNode<int> Node;


	//TREE 1
	/*
	tree.insertNode(new Node(50));
	tree.insertNode(new Node(25));
	tree.insertNode(new Node(60));
	tree.insertNode(new Node(20));
	tree.insertNode(new Node(55));
	tree.insertNode(new Node(40));
	tree.insertNode(new Node(65));
	tree.insertNode(new Node(10));
	tree.insertNode(new Node(22));
	tree.insertNode(new Node(30));
	tree.insertNode(new Node(45));

	tree.deleteNode(50);

	tree.print();

	*/

	//TREE 2
	tree.insertNode(new Node(65));
	tree.insertNode(new Node(50));
	tree.insertNode(new Node(70));
	tree.insertNode(new Node(20));
	tree.insertNode(new Node(55));
	tree.insertNode(new Node(68));
	tree.insertNode(new Node(80));
	tree.insertNode(new Node(90));
	tree.insertNode(new Node(15));


	tree.deleteNode(80);

	tree.print();

}