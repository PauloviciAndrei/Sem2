#pragma once
#include "SortedSet.h"

//DO NOT CHANGE THIS PART
class SortedSetIterator
{
	friend class SortedSet;
private:
    SortedSet& multime;
	SortedSetIterator(SortedSet& m);

	Node *currentIndex;

public:
	void first();
	void next();
	TElem getCurrent();
	bool valid() const;
    TElem remove();
};

