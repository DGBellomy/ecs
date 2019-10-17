#pragma once

class component_vector {
    void* m_list;
    int m_active; // either equal to the first inactive or m_size
    int m_size; // always equal to the next available index
    int m_capacity;

    component_vector(const component_vector&) = delete;
    component_vector& operator= (const component_vector&) = delete;

public:
    component_vector(int capacity=16):
      m_list(nullptr),
      m_active(0),
      m_size(0),
      m_capacity(capacity)
    {}

    template<typename T>
    void push(const T& component)
    {
        if (!m_list)
            _init<T>();

        if (_isFull())
            _resize<T>();

        T* list = reinterpret_cast<T*>(m_list);
        list[m_size++] = list[m_active];
        list[m_active++] = component;
    }

    template<typename T>
    T* get()
    {
        return reinterpret_cast<T*>(m_list);
    }

    int size()
    {
        return m_size;
    }

    int active()
    {
        return m_active;
    }

private:
    template<typename T>
    void _init()
    {
        T* list = new T[m_capacity];
        m_list = reinterpret_cast<void*>(list);
    }

    template<typename T>
    void _resize()
    {
        T* list = reinterpret_cast<T*>(m_list);
        T* newList = new T[2*m_capacity];

        for (int i = 0; i < m_size; ++i)
        {
            newList[i] = list[i];
        }

        m_list = reinterpret_cast<void*>(newList);
        delete[] list;
    }

    inline
    bool _isFull()
    {
        return (m_size == m_capacity);
    }
};
