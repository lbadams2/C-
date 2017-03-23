struct Node {
	Node* next;
	int data;
};

struct Node_iter {
	Node* pos;
};

Node_iter operator++(Node_iter& p) {
	return p.pos = p.pos->next;
}

int operator*(Node_iter p) { // why isn't argument pointer, this is pass by value
	return p.pos->data;
}

bool operator!=(Node_iter p, Node_iter q) {
	return p.pos != q.pos; // compares memory addresses?
}
