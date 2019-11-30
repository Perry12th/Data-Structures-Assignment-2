#pragma once
#include <cassert>

template<class T> class LinkIterator;
template<class T> class LinkList;

// This class describes a single node in the list
template<class T>
class LinkNode
{
	// Give access for LinkIterator and LinkList to private member variables
	friend class LinkIterator<T>;
	friend class LinkList<T>;

private:
	T m_data;
	LinkNode* m_next;
	LinkNode* m_previous;
};

// Be used to access, manipulate and traverse the link list
template <class T>
class LinkIterator
{
public:
	friend class LinkList<T>; // Allow the Iterator to look at all of the Linklist's data

	LinkIterator()
	{
		m_node = NULL;
	}
	~LinkIterator()
	{
	}
	// -------------- OVERLOADED OPERATORS ------------------
	// Assignment operator (=)
	void operator=(LinkNode<T>* node)
	{
		m_node = node;
	}
	// Dereferencing operator (*)
	T& operator*()
	{
		assert(m_node != NULL);
		return m_node->m_data;
	}
	// Incremental operators (++) -- Prefix and Postfix
	void operator++()	// Prefix
	{
		assert(m_node != NULL);
		m_node = m_node->m_next;
	}
	void operator++(int) // Postfix
	{
		assert(m_node != NULL);
		m_node = m_node->m_next;
	}
	// Decremental operators (--) -- Prefix and Postfix
	void operator--() // Prefix
	{
		assert(m_node != NULL);
		m_node = m_node->m_previous;
	}
	void operator--(int)
	{
		assert(m_node != NULL);
		m_node = m_node->m_previous;
	}
	// Comparison operators (!= & ==)
	bool operator!=(LinkNode<T>* node)
	{
		return (m_node != node);
	}
	bool operator==(LinkNode<T>* node)
	{
		return (m_node == node);
	}
	// ------------ END OVERLOADED OPERATORS ----------------
	bool isValid()
	{
		return (m_node != NULL);
	}
private:
	LinkNode<T>* m_node;	// Points to a node in the link list
};

// Actual link list structure
template <class T>
class LinkList
{
public:
	LinkList() : m_size(0), m_root(0), m_lastNode(0)
	{
	}
	~LinkList()
	{
		while (m_root) // While there are still nodes in the list
		{
			Pop(); // Remove each node one by one
		}
	}
	// ---------------- POSITIONING FUNCTIONS ---------------------
	LinkNode<T>* Begin() const// Returns the node at the start of the list
	{
		assert(m_root != NULL);
		return m_root;
	}
	LinkNode<T>* End() const // Simply returns a null ptr
	{
		return NULL;
	}
	LinkNode<T>* Last() const // Returns the node at the end of the list
	{
		return m_lastNode;
	}
	// -------------- END POSITIONING FUNCTIONS -------------------
	// -------------- LINK LIST OPERATIONS ------------------------
	void Insert_Before(LinkIterator<T>& it, T& newData) // Place the new node before an existing node
	{
		assert(it.m_node != NULL); // Check if the node is valid

		LinkNode<T>* node = new LinkNode<T>; // Create a new node
		assert(node != NULL); // Make sure it's valid as well

		node->m_data = newData; // place in the data into the new node
		node->m_next = it.m_node; // set the new node to be in front of the existing node
		node->m_previous = it.m_node->m_previous;

		if (node->m_previous != NULL) // Check if new node is NOT at the front of the list
		{
			node->m_previous->m_next = node; // Assigns the previous nodes "next pointer" to node
		}

		it.m_node->m_previous = node;

		// Check to see if the iterator was pointing to the root
		if (it.m_node == m_root)
		{
			m_root = node;
		}

		m_size++;
	}

	void Insert_After(LinkIterator<T>& it, T& newData) // Place the new node after an existing node
	{
		assert(it.m_node != NULL);

		LinkNode<T>* node = new LinkNode<T>;
		assert(node != NULL);

		node->m_data = newData;
		node->m_next = it.m_node->m_next;
		node->m_previous = it.m_node;

		if (node->m_next != NULL)
		{
			node->m_next->m_previous = node;
		}

		it.m_node->m_next = node;

		if (it.m_node == m_lastNode)
		{
			m_lastNode = node;
		}

		m_size++;
	}

	void Push_Front(T& newData) // Pushes the node to the front of the list
	{
		// Create a new node (new root node)
		LinkNode<T>* node = new LinkNode<T>;

		assert(node != NULL);
		node->m_data = newData;
		node->m_next = NULL;
		node->m_previous = NULL;

		if (m_root != NULL) // Does my root exist?
		{
			node->m_next = m_root;
			m_root->m_previous = node;
			m_root = node;
		}
		else // No items in my list
		{
			m_root = node;
			m_lastNode = node;
		}

		m_size++;
	}
	void Pop_Front() // Remove the node at the front of the list
	{
		assert(m_root != NULL);

		// We are eventually deleting the contents of temp
		LinkNode<T>* temp = m_root;

		m_root = m_root->m_next;

		if (m_root != NULL)
		{
			m_root->m_previous = NULL;
		}
		else // BOOK ERROR
		{
			m_lastNode = NULL;
		}

		delete temp;
		temp = NULL;

		m_size = (m_size == 0 ? m_size : m_size - 1); // Prevent negative numbers
	}
	void Push(T& newData) // Pushes to the back of the list
	{
		// Create a standalone LinkNode object
		LinkNode<T>* node = new LinkNode<T>;

		assert(node != NULL);
		node->m_data = newData;
		node->m_next = NULL;
		node->m_previous = NULL;

		// Add new LinkNode to the existing link list
		if (m_lastNode != NULL) // Items currently exist in the link list
		{
			m_lastNode->m_next = node;
			node->m_previous = m_lastNode; // New node should point to the previous node
		}
		else // An empty link list
		{
			m_root = node;
		}

		m_lastNode = node; // Now set the new node as the last node

		m_size++;
	}
	void Pop() // Removes the last node in the list
	{
		assert(m_root != NULL);

		if (m_root->m_next == NULL) // Check is only 1 node is in the link list
		{
			delete m_root;
			m_root = NULL;
			m_lastNode = NULL;
		}
		else // Link list has 2 or more items in the list
		{
			LinkNode<T>* prevNode = m_lastNode->m_previous;

			prevNode->m_next = NULL;
			delete m_lastNode;
			m_lastNode = prevNode;
			prevNode = NULL;
		}

		m_size = (m_size == 0 ? m_size : m_size - 1); // Prevents negative size
	}
	int GetSize() const // Simply returns the size of the list
	{
		return m_size;
	}
	// ------------ END LINK LIST OPERATIONS ----------------------
private:
	int m_size;					// Holds the size of the link list
	LinkNode<T>* m_root;		// Points to the root of the link list
	LinkNode<T>* m_lastNode;	// Points to the last node of the link list
};