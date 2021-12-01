#pragma once
#include "LinkedList.h"

template <typename T>
class LinkedSet
{
public:
    // Checks if the set contains a particular item.
    // Returns true if the item is found; false otherwise.
    bool contains(const T& item) const;

    // Add an item to the set if it doesn't already exist.
    // Return true if an item was added; false otherwise.
    bool add(const T& item);

    // Remove an item from the set.
    // Return true if an item was removed; false otherwise.
    bool remove(const T& item);

    // Remove all items from the set.
    void clear();

    // Get the number of elements in the set.
    unsigned int getSize() const;

    // Create an iterator that starts at the beginning of the set.
    ConstLinkedListIterator<T> begin() const;

    // Create an iterator that has reached the end of the set.
    ConstLinkedListIterator<T> end() const;

    // Create an iterator that starts at the beginning of the set.
    MutableLinkedListIterator<T> begin();

    // Create an iterator that has reached the end of the set.
    MutableLinkedListIterator<T> end();

    template <typename T2>
    friend std::ostream& operator << (std::ostream& out, const LinkedSet<T2>& orderedList);

private:
    // The underlying linked list.
    LinkedList<T> list;
};

template<typename T>
bool LinkedSet<T>::contains(const T& item) const
{
    // TODO: Implement this function.
    for (ConstLinkedListIterator<T> i = list.begin(); i != list.end(); i++) {
        if (*i == item) {
            return true;
        }
    }
    return false;
}

template<typename T>
bool LinkedSet<T>::add(const T& item)
{
    // TODO: Implement this function.
    // Check list for item
    if (contains(item)) {
        // item isn't contained
        return false;
    }
    // item is there
    /*list.addLast(item);*/
    if (list.getSize() == 0 || list.getFirst() >= item) {
        list.addFirst(item);
    }
    else {
        MutableLinkedListIterator<T> i = list.begin();
        while (i.hasNext() && i.peekNext() < item) {
            i++;
        }
        i.addNext(item);
    }
    
    return true;
}

template<typename T>
bool LinkedSet<T>::remove(const T& item)
{
    // TODO: Implement this function.
    if (contains(item))
    {
        //First item special case
        if (list.getFirst() == item)
        {
            list.removeFirst();
            return true;
        }
        //Iterate through list and use peekNext() to check for matching item
        for (MutableLinkedListIterator<T> i = list.begin(); i != list.end(); ++i)
        {
            if (i.peekNext() == item)
            {
                i.removeNext();
                return true;
            }
        }
        return false;
    }
}

template<typename T>
void LinkedSet<T>::clear()
{
    list.clear();
}

template<typename T>
unsigned int LinkedSet<T>::getSize() const
{
    return list.getSize();
}

template<typename T>
ConstLinkedListIterator<T> LinkedSet<T>::begin() const
{
    return list.begin();
}

template<typename T>
ConstLinkedListIterator<T> LinkedSet<T>::end() const
{
    return list.end();
}

template<typename T>
MutableLinkedListIterator<T> LinkedSet<T>::begin()
{
    return list.begin();
}

template<typename T>
MutableLinkedListIterator<T> LinkedSet<T>::end()
{
    return list.end();
}

template <typename T>
std::ostream& operator << (std::ostream& out, const LinkedSet<T>& set)
{
    out << set.list;
    return out;
}
