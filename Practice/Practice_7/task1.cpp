#include <string>
#include <memory>
#include <limits>
#include <algorithm>
#include <iostream>

class Node {
private:
	int value;
	std::unique_ptr<Node> left;
	std::unique_ptr<Node> right;

public:
	Node(int _value) : value(_value) {}

	Node* insert_left(int value) {
		left = std::make_unique<Node>(value);
		Node* raw_ptr = left.get();

		return raw_ptr;
	}
	Node* insert_right(int value) {
		right = std::make_unique<Node>(value);
		Node* raw_ptr = right.get();

		return raw_ptr;
	}

	int get_value() const { return value; }
	const Node* get_left() const { return left.get(); }
	const Node* get_right() const { return right.get(); }
};

std::unique_ptr<Node> create_tree() {
	// --- Корень
	std::unique_ptr<Node> root = std::make_unique<Node>(-5);
	// ---

	Node* node_L;
	Node* node_R;

	// --- Левое поддерево
	node_L = root->insert_left(1);
	// ---

	// --- Правое поддерево
	node_R = root->insert_right(7);
	node_L = node_R->insert_left(2);
	node_R = node_R->insert_right(3);
	// ---

	return root;
}

int get_path(const Node* node, int& global_max) {
	if (!node) { return 0; }

	int left = std::max(get_path(node->get_left(), global_max), 0);
	int right = std::max(get_path(node->get_right(), global_max), 0);

	int local_max = node->get_value() + left + right;
	global_max = std::max(global_max, local_max);
	
	int partial_local_max = node->get_value() + std::max(left, right);

	return partial_local_max;
}

int find_max_path(const Node* root) {
	int global_max = std::numeric_limits<int>::min();
	(void)get_path(root, global_max);

	return global_max;
}

int main() {
	setlocale(LC_CTYPE, "rus");

	std::unique_ptr<Node> root = create_tree();
	int max_path = find_max_path(root.get());

	std::cout << "Максимальный путь в дереве: " << max_path << std::endl;

	return 0;
}