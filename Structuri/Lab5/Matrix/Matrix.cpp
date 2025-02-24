#include "Matrix.h"
#include <exception>
using namespace std;

Matrix::Matrix(int nrLines, int nrCols) : root(nullptr), nr_lines(nrLines), nr_cols(nrCols) {}


int Matrix::nrLines() const {
	return nr_lines;
}


int Matrix::nrColumns() const {
    return nr_cols;
}

///BC - Theta(1), WC - Theta(n), AC - Theta(logn)
TElem Matrix::element(int i, int j) const {
    if (i < 0 || i >= nr_lines || j < 0 || j >= nr_cols) {
        throw exception();
    }
    BSTNode* node = find(root, i, j);
    return node ? node->value : NULL_TELEM;
}

///BC - Theta(1), WC - Theta(n), AC - Theta(logn)
TElem Matrix::modify(int i, int j, TElem e) {
    if (i < 0 || i >= nr_lines || j < 0 || j >= nr_cols) {
        throw exception();
    }
    BSTNode* node = find(root, i, j);
    TElem oldValue = node ? node->value : NULL_TELEM;
    if (e != NULL_TELEM) {
        root = insert(root, i, j, e);
    } else if (node) {
        oldValue = remove(root, i, j);
    }
    return oldValue;
}

///BC - Theta(1), WC - Theta(n), AC - Theta(logn)
TElem Matrix::maxValue() const {
    if (!root) {
        return NULL_TELEM;
    }
    BSTNode* currentNode = root;
    while (currentNode->right) {
        currentNode = currentNode->right;
    }
    return currentNode->value;
}


