#pragma once
#include "Set.h"
#include <stack>
#include <exception>

class SetIterator
{
	//DO NOT CHANGE THIS PART
	friend class Set;
private:
	//DO NOT CHANGE THIS PART
	const Set& set;
	SetIterator(const Set& s);

	//TODO - Representation
	int index;
	Set::Node* node;
    std::stack<Set::Node*> previousNodes;

public:
	void first();
	void next();
	TElem getCurrent();
    void jumpBackward(int k);
	bool valid() const;
};


