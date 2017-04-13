#pragma once
using namespace std;

template<class T> class Sequence
{
public:
		// Constructor - set used and current_index to -1
	Sequence(int capacity = 10)
	{
		used = 0;
		current_index = -1;
		_capacity = capacity;
		data = new T[_capacity];
	}


		// Destructor.
	~Sequence()
	{
		delete[] data;
		data = nullptr;
	}


		// MUTATOR MEMBER FUNCTIONS 

		//Postcondition: The first item in the sequence becomes the current item
	void first() { current_index = size() > 0 ? 0 : -1; }

		//Postcondition: The last item in the sequence becomes the current item
	void last() { current_index = size() - 1; }


		/*Precondition: is_item returns true.
		  Postcondition: If the current item was already the last item in the sequence, then no action could be performed.
		  Otherwise, the new current item is the item immediately after the original current item. */
	void next()
	{
		if (getCurrentIndex() < size() - 1)
			current_index++;
	}


		/*Precondition: is_item returns true.
		  Postcondition: If the current item was already the last item in the sequence, then no action could be performed.
		  Otherwise, the new current item is the item immediately before the original current item. */
	void previous()
	{
		if (getCurrentIndex() > 0)
			current_index--;
	}


		/*Precondition: size( ) < CAPACITY.
		  Postcondition: A new copy of entry has been inserted in the sequence before the current item.
		  If there was no current item, then the new entry has been inserted at the front of the sequence (position 0).
		  In either case, the newly inserted item is now the current item of the sequence. */
	void insert(const T& entry)
	{
		insert_item(entry);
	}


		/*Precondition: size( ) < CAPACITY.
		  Postcondition: A new copy of entry has been inserted in the sequence after the current item.
		  If there was no current item, then the new entry has been attached to the end of the sequence.
		  In either case, the newly inserted item is now the current item of the sequence. */
	void attach(const T& entry)
	{
		insert_item(entry, true);
	}


		/*Precondition: is_item returns true.
		  Postcondition: The current item has been removed from the sequence,
		  and the item after this (if there is one) is now the new current item.*/
	void remove_current()
	{
		if (!is_item())
			return;

		if (getCurrentIndex() == size() - 1)
			current_index--;
		else
		{
			for (int i = getCurrentIndex() + 1; i < size(); i++)
				data[i - 1] = data[i];
		}
		used--;
	}


		// ACCESSOR MEMBER FUNCTIONS


		// Returns a sequence capacity value.
	int getCapacity() const { return _capacity; }

		/*Precondition: is_item( ) returns true.
		  Postcondition: The item returned is the current item in the sequence.*/
	T current() const { return (is_item() ? data[getCurrentIndex()] : NULL); }

		//Postcondition: The value returned is the number of items in the sequence.
	int size() const { return used; }

		//Postcondition: The value returned is the index of current item.
	int getCurrentIndex() const { return current_index; }

		//Postcondition: The value returned is the value of one data item.
	T getDataItem(int index) const { return data[index]; }

		// Determines whether a sequence does not contain any items.
	bool is_empty() const { return (size() == 0); }

		// Determines whether a sequence is full (no room for new items).
	bool is_full() const { return size() == getCapacity(); }


private:
	T *data;

	int used;
	int current_index;
	int _capacity;


	/*Postcondition: A true return value indicates that there is a valid "current" item
	  that may be retrieved by invoking the current member function below.
	  A false return value indicates that there is no valid current item.*/
	bool is_item() const { return (getCurrentIndex() >= 0 && getCurrentIndex() < size()); }


	/*Precondition: If data array is full call reallocate() function to double the size.
	  Postcondition: If set was not empty and (append_to_end = true), an item must be added by ATTACH method,
	  otherwise (append_to_end = false) an item must be added by INSERT method.
	  In either case, the newly inserted item is now the current item of the sequence. */
	void insert_item(const T entry, bool append_to_end=false)
	{
		if (is_full())
			reallocate();

		if (!is_empty())
		{
			if (append_to_end)
				current_index++;
			for (int i = size() - 1; i >= getCurrentIndex(); i--)
				data[i + 1] = data[i];
		}
		else
			current_index++;

		data[getCurrentIndex()] = entry;
		used++;
	}

	/*Postcondition: The storage for an array of twice the size is dynamically allocated.
	  All the elements from the original array have been copied to this new double-size storage
	  and memory for an old array deallocated. 
	  The original pointer to the array points to the new double-size storage.*/
	void reallocate()
	{
		_capacity *= 2;
		T *new_data = new T[_capacity];
		for (int i = 0; i < size(); i++)
			new_data[i] = data[i];

		delete[] data;
		data = new_data;
	}
};
