#include <exception>

template <typename T>
struct LinkedListNode
{
  T value;
  LinkedListNode<T> *prev;
  LinkedListNode<T> *next;

  LinkedListNode(const T &value) : value(value), prev(nullptr), next(nullptr) {}
};

template <typename T>
class LinkedList
{
  LinkedListNode<T> *head, *tail;

public:
  LinkedList() : head(nullptr), tail(nullptr) {}

  ~LinkedList()
  {
    for (LinkedListNode<T> *cur = head, *next; cur != nullptr; cur = next)
    {
      next = cur->next;
      delete cur;
    }
  }
  class Iterator
  {
    LinkedListNode<T> *cur;

  public:
    Iterator(LinkedListNode<T> *cur) : cur(cur) {}
    // Check for equality (inequality)
    bool operator==(const Iterator &other)
    {
      return cur == other.cur;
    }
    bool operator!=(const Iterator &other)
    {
      return !(*this == other);
    }
    // Increment (e.g. --it)
    Iterator &operator--()
    {
      cur = cur->prev;
      return *this;
    }
    // Increment (e.g. ++it)
    Iterator &operator++()
    {
      cur = cur->next;
      return *this;
    }
    // Dereference (e.g. *it)
    T &operator*()
    {
      return cur->value;
    }

    friend LinkedList;
  };
  void pop_front()
  {
    // Let's assume head != nullptr
    // TODO: Subclass std::exception and throw an exception with a proper error message.
    if (head == nullptr)
    {
      throw std::runtime_error("Error: Header is null pointer");
    }
    LinkedListNode<T> *old_head = head;
    if (head->next != nullptr)
    {
      head->next->prev = nullptr;
    }
    head = head->next;
    delete old_head;
  }

  void push_back(const T &value)
  {
    LinkedListNode<T> *new_node = new LinkedListNode<T>(value);
    if (empty())
    {
      head = tail = new_node;
    }
    else
    {
      new_node->prev = tail;
      tail->next = new_node;
      tail = new_node;
    }
  }

  bool empty()
  {
    return head == nullptr;
  }

  Iterator begin()
  {
    return Iterator(head);
  }

  Iterator end()
  {
    return Iterator(nullptr);
  }

  Iterator tail_iterator()
  {
    return Iterator(tail);
  }

  Iterator before_begin_iterator()
  {
    return Iterator(nullptr);
  }

  Iterator insert(Iterator position, const T &newValue)
  {
    LinkedListNode<T> *newNode = new LinkedListNode<T>(newValue);
    if (empty())
    {
      head = tail = newNode;
    }
    else if (position.cur == head)
    {
      newNode->next = position.cur;
      position.cur->prev = newNode;
      head = newNode;
    }
    else if (position.cur == end()) //if it's a nullprt
    {
      push_back(newValue);
    }
    else
    {
      newNode->prev = position.cur->prev;
      newNode->next = position.cur;
      position.cur->prev->next = newNode;
      position.cur->prev = newNode;
    }
    return Iterator(newNode);
  }

  Iterator erase(Iterator position)
  {
    if (position.cur == nullptr)
    {
      throw std::runtime_error("Error: Header is null pointer");
    }
    if (head == tail)
    {
      if (position.cur != head)
      {
        throw std::runtime_error("Error: Internal error"); // TODO throw a specific exception
      }
      head = nullptr;
      tail = nullptr;
      delete position.cur;
      return end();
    }
    else if (position.cur == head)
    {
      head = position.cur->next;
      head->prev = nullptr;
      delete position.cur;
      return begin();
    }else if (position.cur == tail){
      tail = position.cur -> prev;
      tail->next = nullptr;
      delete position.cur;
      return end();
    }else{
      Iterator temp = Iterator(position.cur->next);
      position.cur->prev->next = position.cur->next;
      position.cur->next->prev = position.cur->prev;
      delete position.cur;
      return temp;
    }
  }
};