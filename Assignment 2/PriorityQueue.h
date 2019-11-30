#pragma once
// Priority Queue

#include "PriorityQueueLinkList.h"

template<class T, class CMP>
class PriorityQueue
{
public:
	// Constructor & Destructor
	PriorityQueue(const int& size)
	{
		assert(size > 0);
		m_size = size;
	}
	~PriorityQueue() { } // The Link List class takes care of deleting its data
	// Queue Functions
	void push(T val)
	{
		assert(m_elements.GetSize() < m_size);

		if (m_elements.GetSize() == 0) // If my priorty queue is empty, just push
		{
			m_elements.Push(val);
		}
		else // Priority queue has at least 1 item
		{
			LinkIterator<T> it;
			it = m_elements.Begin();

			CMP cmp;	// Used to compare two T objects together

			while (it.isValid()) // Iteratue until iterator object is invalid
			{
				if (cmp(val, *it)) // Compare two values
				{
					// If there's a match then break out of the loop
					break;
				}

				it++;	// Move iterator to the next node
			}

			if (it.isValid())
			{
				m_elements.Insert_Before(it, val); // Insert before an existing node
			}
			else
			{
				m_elements.Push(val); // Push new value to the end of the list
			}
		}
	}
	void pop() // Remove the node at the front of the queue
	{
		m_elements.Pop_Front();
	}
	T& front() // Return a reference to the front of the queue
	{
		LinkIterator<T> it;
		it = m_elements.Begin();	// Points to the beginning of the link list

		return *it;					// Returns the derefences iterator (or the value of the node)
	}
	T& back()
	{
		LinkIterator<T> it;
		it = m_elements.Last();		// Points to the last node of the link list

		return *it;
	}
	// Helper Functions
	int GetSize() const
	{
		return m_elements.GetSize();
	}
	int GetMaxSize() const
	{
		return m_size;
	}
	bool isEmpty() const 
	{
		return (m_elements.GetSize() == 0);
	}
	void Resize(int size)
	{
		assert(size > 0);
		m_size = size;
	}
private:
	LinkList<T> m_elements;		// Link List structure
	int m_size;					// Size of our queue
};
