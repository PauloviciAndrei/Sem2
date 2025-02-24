#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>

using namespace std;

SMIterator::SMIterator(const SortedMap& m) : map(m){
	this->currentPos = 0;
}

void SMIterator::first(){
	this->currentPos = 0;
}

void SMIterator::next(){
    if(this->currentPos == this->map.mapSize)
    {
        throw exception();
    }
	this->currentPos++;
}

bool SMIterator::valid() const{

	return this->currentPos < this->map.mapSize;

}

TElem SMIterator::getCurrent() const{
    if(this->currentPos == this->map.mapSize)
    {
        throw exception();
    }
	return this->map.elements[this->currentPos];

}


