

#ifndef STACK_HPP
#define STACK_HPP


#include <cstdint>
#include <vector>

#define STACK_BLOCK_SIZE 8

template<typename T = int>
class Stack
{
public:

    static const int DEFAULT_MAX_SIZE = 0;

    Stack();

    Stack(const Stack& rhs);

    Stack& operator=(const Stack& rhs);

    Stack(Stack&& rhs);

    ~Stack();

    explicit Stack(uint32_t maxSize);

    [[nodiscard]] bool isEmpty() const;

    [[nodiscard]] bool isFull() const;

    [[nodiscard]] size_t size() const;

    [[nodiscard]] size_t maxSize() const;

    void push(const T& item);

    [[nodiscard]] T peek();

    T pop();

private /* methods */:
    void resizeItemsBuffer();

    [[nodiscard]] bool isStackFull() const; //TODO need to reconsidered

private:
    T* m_items;

    size_t m_maxSize = DEFAULT_MAX_SIZE;

    size_t m_size;

    bool m_isEmpty;

    bool m_isFull;

};

template<typename T>
Stack<T>::Stack(): Stack::Stack(DEFAULT_MAX_SIZE)
{

}

template<typename T>
Stack<T>::Stack(uint32_t maxSize):
        m_maxSize{ maxSize },
        m_size{ 0 },
        m_isEmpty{ true },
        m_isFull{ false },
        m_items{ new T[STACK_BLOCK_SIZE] }
{

}

template<typename T>
Stack<T>::Stack(const Stack& rhs)
{
    m_items = new T[rhs.size()];
    for (int i = 0; i < rhs.size(); ++i)
    {
        m_items[i] = rhs.m_items[i];
    }
    m_size = rhs.size();
    m_isEmpty = rhs.m_isEmpty;
    m_isFull = rhs.m_isFull;
}


template<typename T>
Stack<T>& Stack<T>::operator=(const Stack& rhs)
{
    if (&rhs == this)
    {
        return *this;
    }

    m_items = new T[rhs.size()];
    for (int i = 0; i < rhs.size(); ++i)
    {
        m_items[i] = rhs.m_items[i];
    }
    m_size = rhs.size();
    m_isEmpty = rhs.m_isEmpty;
    m_isFull = rhs.m_isFull;
    return *this;
}

template<typename T>
Stack<T>::Stack(Stack&& rhs)
{

}

template<typename T>
bool Stack<T>::isEmpty() const
{
    return this->m_isEmpty;
}

template<typename T>
bool Stack<T>::isFull() const
{
    return this->m_isFull;
}

template<typename T>
size_t Stack<T>::size() const
{
    return this->m_size;
}

template<typename T>
size_t Stack<T>::maxSize() const
{
    return this->m_maxSize;
}

template<typename T>
void Stack<T>::push(const T& item)
{
    if (isStackFull())
    {
        return;
    }

    if ((this->size() == 0 ? 1 : this->size()) % STACK_BLOCK_SIZE == 0)
    {
        this->resizeItemsBuffer();
    }

    this->m_isEmpty = false;
    this->m_items[this->m_size++] = item;
    this->m_isFull = this->isStackFull();
}

template<typename T>
bool Stack<T>::isStackFull() const
{
    if (this->maxSize() == 0)
    {
        return false;
    }

    return this->size() >= this->maxSize();
}

template<typename T>
T Stack<T>::peek()
{
    if (this->size() == 0)
    {
        return T();
    }
    return this->m_items[this->size() - 1];
}

template<typename T>
T Stack<T>::pop()
{
    if (this->size() == 0)
    {
        return T();
    }

    T v = this->m_items[this->m_size-- - 1];
    this->m_isEmpty = this->size() == 0;
    this->m_isFull = false;
    return v;
}

template<typename T>
Stack<T>::~Stack()
{
    if (m_items != nullptr)
    {
        delete[] m_items;
    }
}

template<typename T>
void Stack<T>::resizeItemsBuffer()
{
    auto newBuffer = new T[this->size() + STACK_BLOCK_SIZE];
    std::copy(m_items, m_items + this->size(), newBuffer);
    delete[] m_items;
    m_items = newBuffer;
}


#endif //STACK_HPP
