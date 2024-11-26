template<class T>
class LinkedList
{
  struct Node
  {
    Node *prev;
    Node *next;
    T value;
    Node(const T& v) : prev(nullptr), next(nullptr), value(v) {}
  };

public:
  class Iterator
  {
    Node *cur;

  public:
    Iterator(Node *node) : cur(node) {}

    // Return the element at the iterator's current position in the queue.
    T operator*() const
    {
      return cur->value;
    }

    // Pre-increment overload; advance the iterator one position in the list.
    // Return this iterator. NOTE: if the iterator has reached the end of the
    // list (past the last element), its data should be equal to
    // LinkedList<T>::end().
    Iterator& operator++()
    {
      if (cur)
        cur = cur->next;
      return *this;
    }

    // Pre-decrement overload; recedes one element. Return this iterator. NOTE:
    // if the iterator has reached the end of the list (before the first
    // element), its data should be equal to LinkedList<T>::end().
    Iterator& operator--()
    {
      if (cur)
        cur = cur->prev;
      return *this;
    }

    // Return true it both iterators point to the same node in the list, and
    // false otherwise.
    bool operator==(Iterator const& rhs)
    {
      return cur == rhs.cur;
    }

    // Return false it both iterators point to the same node in the list, and
    // true otherwise.
    bool operator!=(Iterator const& rhs)
    {
      return cur != rhs.cur;
    }
  };

private:
  Node *headnode;
  Node *tailnode;

public:
  // Construct a new LinkedList<T>.
  LinkedList() : headnode(nullptr), tailnode(nullptr) {}

  ~LinkedList()
  {
    clear();
  }

  // Return an Iterator pointing to the beginning of the list.
  Iterator begin() const
  {
    return Iterator(headnode);
  }

  // Return an Iterator pointing to the last node of the list.
  Iterator tail() const
  {
    return Iterator(tailnode);
  }

  // Return an Iterator pointing past the end of the list (an invalid, unique
  // state, data likely pointing to nullptr.)
  Iterator end() const
  {
    return Iterator(nullptr);
  }

  // Return true if there are no elements, false otherwise.
  bool isEmpty() const
  {
    return !headnode;
  }

  // Return the first element in the list.
  T getFront() const
  {
    return headnode->value;
  }

  // Return the last element in the list.
  T getBack() const
  {
    return tailnode->value;
  }

  // Return true if list contains a node whose data equals the specified
  // element and false otherwise.
  bool contains(T element) const
  {
    Node *node = headnode;
    while (node) {
      if (node->value == element) {
        return true;
      }
      node = node->next;
    }
    return false;
  }

  // Adds the specified element to the back of the list.
  void enqueue(T element)
  {
    Node *node = new Node(element);
    if (tailnode) {
      tailnode->next = node;
      node->prev = tailnode;
    } else {
      headnode = node;
    }
    tailnode = node;
  }

  // Remove the first element from the list.
  void dequeue()
  {
    if (headnode) {
      Node *node = headnode;
      headnode = node->next;
      if (headnode)
        headnode->prev = nullptr;
      else
        tailnode = nullptr;
      delete node;
    }
  }

  // Remove the last element from the list.
  void pop()
  {
    if (tailnode) {
      Node *node = tailnode;
      tailnode = node->prev;
      if (tailnode)
        tailnode->next = nullptr;
      else
        headnode = nullptr;
      delete node;
    }
  }

  // Removes all elements from the list.
  void clear()
  {
    while (headnode) {
      Node *node = headnode;
      headnode = node->next;
      delete node;
    }
    tailnode = nullptr;
  }

  // Remove the first node found whose data equals the specified element.
  void remove(T element)
  {
    Node *node = headnode;
    while (node) {
      if (node->value == element) {
        if (node->prev)
          node->prev->next = node->next;
        else
          headnode = node->next;
        if (node->next)
          node->next->prev = node->prev;
        else
          tailnode = node->prev;
        delete node;
        return;
      }
      node = node->next;
    }
  }
};
