#pragma once

template <typename NodeType, typename IteratorType>
class Iterator {
protected:
	NodeType* current;

public:
	Iterator(NodeType* current) : current{current} {}

	virtual IteratorType& operator++() = 0;
	virtual bool operator!=(const IteratorType& other) { return current != other.current; }
	virtual NodeType& operator*() { return *current; }

};
