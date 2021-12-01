#include <ostream>
#include <stdexcept>
#include "ListNode.h"

template <typename T>
class ConstLinkedListIterator;

template <typename T>
class MutableLinkedListIterator;

// A container class for a singly-linked list
template <typename T>
class LinkedList
{
public:
    // Default constructor
    LinkedList() = default;

    // Destructor
    ~LinkedList();

    // Copy constructor
    LinkedList(const LinkedList<T>& original);

    // Copy assignment op
    // Copy assignment op
    LinkedList<T>& operator= (const LinkedList<T>& original);

    // Move constructor
    LinkedList(LinkedList<T>&& original);

    // Move assignment op
    LinkedList<T>& operator= (LinkedList<T>&& original);

    // Clear list without destroying container
    void clear();

    // Add node to the beginning of the list
    void addFirst(T value);

    // Add node to the end of the list
    void addLast(T value);

    // Remove node from the beginning of the list
    void removeFirst();

    // Get element at the beginning of the list
    const T& getFirst() const;

    // Get element at the beginning of the list
    T& getFirst();

    // Get element at the end of the list
    const T& getLast() const;

    // Get element at the end of the list
    T& getLast();

    // Get number of nodes in the list
    unsigned int getSize() const;

    // Start of forward iterator
    ConstLinkedListIterator<T> begin() const;

    // End of forward iterator
    ConstLinkedListIterator<T> end() const;

    template <typename T2>
    friend class MutableLinkedListIterator;

    // Start of forward mutable iterator
    MutableLinkedListIterator<T> begin();

    // End of forward mutable iterator
    MutableLinkedListIterator<T> end();

private:
    // Pointer to first node in the list
    ListNode<T>* first{ nullptr };

    // Pointer to last node in the list
    ListNode<T>* last{ nullptr };

    // Number of nodes in the list
    unsigned int size{ 0 };
};

template<typename T>
LinkedList<T>::~LinkedList()
{
    clear();
}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& original)
{
    // TODO: implement copy constructor
    first = nullptr;
    size = 0;

    ListNode<T>* temp = original.first;
    for (unsigned int i{ 0 }; i < original.getSize(); ++i)
    {
        addLast(temp->value);
        temp = temp->next;
    }
    delete temp;
   
}

//Copy Assignment Operator
template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& original)
{
    if (this == &original)
    {
        return *this;
    }
    else
    {
        this->clear();
        ListNode<T>* temp = original.first;
        for (unsigned int i{ 0 }; i < original.getSize(); ++i)
        {
            this->addLast(temp->value);
            temp = temp->next;
        }
        delete temp;
        return *this;
    }
}

template<typename T>
LinkedList<T>::LinkedList(LinkedList<T>&& original)
    : first { original.first }, last { original.last }, size { original.size }
{
    // TODO: implement move constructor
    this->size = original.size;
    this->first = original.first;
    this->last = original.last;
    original.size = 0;
    original.first = nullptr;
    original.last = nullptr;
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList<T>&& original)
{
    // TODO: implement move assignment operator

    ListNode<T>* temp = nullptr;
    std::swap(size, original.size);

    temp = first;
    first = original.first;
    original.first = temp;


    temp = last;
    last = original.last;
    original.last = temp;

    return *this;
}

template<typename T>
void LinkedList<T>::clear()
{
    // Keep track of the next node to delete.
    ListNode<T>* toDelete{ first };

    // Loop until toDelete == nullptr
    while (toDelete)
    {
        // Use first as temp storage
        first = toDelete->next;

        delete toDelete;


        // Advance to the next node.
        toDelete = first;
    }
    // first should now be nullptr.

    last = nullptr;
    size = 0;
}

template <typename T>
void LinkedList<T>::addFirst(T value)
{
    // Create a new node
    ListNode<T>* newNode{ new ListNode<T>() };

    // Store the new element in the new node
    newNode->value = value;

    // Link the new node to the old first node
    newNode->next = first;

    // Set the new node as the first node
    first = newNode;

    if (!last)
    {
        // If there is just one element in the 
        // list, first and last are the same.
        last = first;
    }

    size++;
}

template<typename T>
void LinkedList<T>::addLast(T value)
{
    // TODO: Implement this function.

    //Create new node
    ListNode<T>* newNode{ new ListNode<T>{} };
    //store element in new node
    newNode->value = value;
    newNode->next = NULL;
    if (first == NULL)
    {
        //if list is empty, set newNode as first and last node
        first = newNode;
        last = newNode;
        /*newNode = NULL;*/
    }
    else
    {
        //link old last node to the new node
        last->next = newNode;
        //set the new node to last node
        last = newNode;
    }
    //increment size
    size++;
}

template<typename T>
void LinkedList<T>::removeFirst()
{
    // TODO: Implement this function.

    if (size == 0)
    {
        throw std::logic_error("Empty list!");
    }
    else
    {
        //Find the second element of the list and set it as the first element.
        ListNode<T>* temp{ first };
        temp = first;
        first = first->next;
        //Delete the old first node.
        delete temp;
        //Decrement size.
        size--;
        //If the list is now empty, set last to nullptr.
        if (!first)
        {
            last = nullptr;
        }
    }
}

template <typename T>
T const& LinkedList<T>::getFirst() const
{
    if (first)
    {
        return first->value;
    }
    else
    {
        throw std::out_of_range("Empty list");
    }
}

template <typename T>
T& LinkedList<T>::getFirst()
{
    if (first)
    {
        return first->value;
    }
    else
    {
        throw std::out_of_range("Empty list");
    }
}

template <typename T>
T const& LinkedList<T>::getLast() const
{
    if (last)
    {
        return last->value;
    }
    else
    {
        throw std::out_of_range("Empty list");
    }
}

template <typename T>
T& LinkedList<T>::getLast()
{
    if (last)
    {
        return last->value;
    }
    else
    {
        throw std::out_of_range("Empty list");
    }
}

template<typename T>
unsigned int LinkedList<T>::getSize() const
{
    return size;
}

template <typename T>
std::ostream& operator << (
    std::ostream& os, const LinkedList<T>& list)
{
    if (list.getSize() == 0)
    {
        // Special case: empty list
        os << "[]";
    }
    else
    {
        // Print opening bracket and first element
        os << "[" << list.getFirst();

        auto i{ ++list.begin() }; // Start at second element
        while (i != list.end())
        {
            // Print a comma, then the next element
            os << ", " << *i;

            // Advance iterator to the next node
            i++;
        }

        // Print closing bracket
        os << "]";
    }

    return os;
}

#include "ConstLinkedListIterator.h"
#include "MutableLinkedListIterator.h"

template <typename T>
ConstLinkedListIterator<T> LinkedList<T>::begin() const
{
    return ConstLinkedListIterator<T>{first};
}

template <typename T>
ConstLinkedListIterator<T> LinkedList<T>::end() const
{
    return ConstLinkedListIterator<T>{nullptr};
}

template <typename T>
MutableLinkedListIterator<T> LinkedList<T>::begin()
{
    return MutableLinkedListIterator<T>{first, * this};
}

template <typename T>
MutableLinkedListIterator<T> LinkedList<T>::end()
{
    return MutableLinkedListIterator<T>{nullptr, * this};
}
