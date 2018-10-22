#ifndef PRIORITY_QUEUE
#define PRIORITY_QUEUE

#include "NodeRecord.h"
#include <queue>

template<class T, class Container = std::vector<T>, class Compare = std::less<typename Container::value_type>>
	class PriorityQueue : public std::priority_queue<T, Container, Compare>
{
public:
	//
	typedef typename std::priority_queue<T, Container, Compare>::container_type::const_iterator const_iterator;

	//Begin
	const_iterator begin() const
	{
		auto first = this->c.cbegin();
		return first;
	}

	//End
	const_iterator end() const
	{
		auto last = this->c.cend();
		return last;
	}

	//Contains
	const_iterator contains(const T&val) const
	{
		auto first = this->c.cbegin();
		auto last = this->c.cend();
		while (first != last) 
		{
			if (*first == val) return first;
			++first;
		}
		return last;
	}

	//Remove
	bool remove(const T& value) 
	{
		auto it = std::find(this->c.begin(), this->c.end(), value);
		if (it != this->c.end()) 
		{
			this->c.erase(it);
			std::make_heap(this->c.begin(), this->c.end(), this->comp);
			return true;
		}
		else
		{
			return false;
		}
	}
};

//Compare cost stuct
struct CompareCost : public std::binary_function<NodeRecord, NodeRecord, bool>
{
	bool operator()(const NodeRecord lhs, const NodeRecord rhs) const
	{
		return lhs.mCostSoFar > rhs.mCostSoFar;
	}
};

//Compare estimated cost struct
struct CompareEstimatedCost : public std::binary_function<NodeRecord, NodeRecord, bool>
{
	bool operator()(const NodeRecord lhs, const NodeRecord rhs) const
	{
		return lhs.mEstimatedTotalCost > rhs.mEstimatedTotalCost;
	}
};

#endif // !PRIORITY_QUEUE