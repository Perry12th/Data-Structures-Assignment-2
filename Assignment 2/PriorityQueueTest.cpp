#include <iostream>
#include "PriorityQueue.h"

using namespace std;

// Use for a list that starts low and ends high
template<class T>
class less_cmp 
{
public:
	inline bool operator()(T lVal, T rVal)
	{
		return (lVal < rVal);
	}
};

template<class T>
class less_cmp_ptr
{
public:
	inline bool operator()(T lVal, T rVal)
	{
		return ((*lVal) < (*rVal));
	}
};

// Use for a list that starts high and ends low
template<class T>
class greater_cmp
{
public:
	inline bool operator()(T lVal, T rVal)
	{
		return !(lVal < rVal);
	}
};

template<class T>
class greater_cmp_ptr
{
public:
	inline bool operator()(T lVal, T rVal)
	{
		return !((*lVal) < (*rVal));
	}
};

class Loot
{
public:
	// Constructors and destructor
	Loot() : m_rarity(0), m_id(0) { }
	Loot(int r, int id) : m_rarity(r), m_id(id) { }
	~Loot() { }

	// Get Methods
	int GetRarity() const
	{
		return m_rarity;
	}
	int GetID() const
	{
		return m_id;
	}
	// Overloaded operators ( < and > )
	bool operator<(Loot& m)
	{
		// Check against both priority and id values
		if (m_rarity < m.GetRarity())
		{
			return true;
		}
		else if (m_rarity == m.GetRarity() &&  m_id < m.GetID())	// Issue with the class code, this would return a false true when the id number was greater but the rarity was still lesser
		{
			return true;
		}

		return false;
	}
	bool operator>(Loot& m)
	{
		return !(*this < m);
	}
private:
	int m_rarity, m_id;
};

int main()
{
	cout << "Assignment 2: Priority Queue Data Structure " << endl << endl;

	const int size = 10;
	PriorityQueue<Loot, less_cmp<Loot> > que(size);

	que.push(Loot(3, 10));
	que.push(Loot(2, 86));
	que.push(Loot(1, 62));
	que.push(Loot(3, 35));
	que.push(Loot(1, 68));
	que.push(Loot(3, 5));
	que.push(Loot(2, 12));
	que.push(Loot(4, 35));
	que.push(Loot(2, 58));
	que.push(Loot(4, 6));

	// Display priority queue
	cout << "Priority queue content (Size - " << que.GetSize() << ") : " << endl;

	while (que.isEmpty() == false)
	{
		cout << "   Rarity: " << que.front().GetRarity();
		cout << "   ID: " << que.front().GetID();
		cout << endl;

		que.pop();
	}

	cout << endl << "Cleaning out the container " << endl;

	if (que.isEmpty() == true)
	{
		cout << "The container is now empty" << endl;
	}
	else
	{
		cout << "The container is NOT empty" << endl;
	}


	system("pause");
	return 0;
}