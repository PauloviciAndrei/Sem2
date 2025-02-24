#pragma once

//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM 0

class Matrix {

private:
    struct BSTNode {
        int line;
        int column;
        TElem value;
        BSTNode* left;
        BSTNode* right;

        BSTNode(int l, int c, TElem v) : line(l), column(c), value(v), left(nullptr), right(nullptr) {}
    };
    BSTNode* root;
    int nr_lines;
    int nr_cols;
public:
	//constructor
	Matrix(int nrLines, int nrCols);

 ///BC - Theta(1), WC - Theta(n), AC - Theta(logn)
    BSTNode* insert(BSTNode* node, int i, int j, TElem e) {
        if (!node) {
            return new BSTNode(i, j, e);
        }
        if (i < node->line || (i == node->line && j < node->column)) {
            node->left = insert(node->left, i, j, e);
        } else if (i > node->line || (i == node->line && j > node->column)) {
            node->right = insert(node->right, i, j, e);
        } else {
            node->value = e;
        }
        return node;
    }
    ///BC - Theta(1), WC - Theta(n), AC - Theta(logn)
    BSTNode* find(BSTNode* node, int i, int j) const {
        if (!node) {
            return nullptr;
        }
        if (i == node->line && j == node->column) {
            return node;
        }
        if (i < node->line || (i == node->line && j < node->column)) {
            return find(node->left, i, j);
        } else {
            return find(node->right, i, j);
        }
    }
    ///BC - Theta(1), WC - Theta(n), AC - Theta(logn)
    TElem remove(BSTNode*& node, int i, int j) {
        if (!node) {
            return NULL_TELEM;
        }
        if (i < node->line || (i == node->line && j < node->column)) {
            return remove(node->left, i, j);
        } else if (i > node->line || (i == node->line && j > node->column)) {
            return remove(node->right, i, j);
        } else {
            TElem oldValue = node->value;
            if (!node->left) {
                BSTNode* temp = node->right;
                delete node;
                node = temp;
            } else if (!node->right) {
                BSTNode* temp = node->left;
                delete node;
                node = temp;
            } else {
                BSTNode* minNode = minimum(node->right);
                node->line = minNode->line;
                node->column = minNode->column;
                node->value = minNode->value;
                remove(node->right, minNode->line, minNode->column);
            }
            return oldValue;
        }
    }

    BSTNode* minimum(BSTNode* node) const {
        while (node && node->left) {
            node = node->left;
        }
        return node;
    }
	//returns the number of lines
	int nrLines() const;

	//returns the number of columns
	int nrColumns() const;

	//returns the element from line i and column j (indexing starts from 0)
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem element(int i, int j) const;

	//modifies the value from line i and column j
	//returns the previous value from the position
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem modify(int i, int j, TElem e);

    TElem maxValue() const;

};
