/* Author: GarRaptor
 * Description: Dynamic array stored as a void* so that the vector doesn't care what data it's holding
 *   template functions are used to deal with casting so that the end-user doesn't need to worry about that.
 * Uses:
 *   component_vector cv(32); // uses a default parameter so the size will be _DEFAULT_SIZE
 *   cv.push<T>(component);   // where T is the type of component you are passing to the vector.
 *   cv.get<T>();             // returns the component array ptr for direct access.
 *   cv.size();               // total number of components | size_ is always equal to the next empty index pos
 *   cv.active();             // total number of active components | active_ is the first inactive index or size_
 *   cv.inactive();           // total number of inactive components | difference between size_ and active_
 */

// NOTE: It is important that you use the same typename T for a single component_vector or you will corrupt your data.
// TODO: add "type" std::string member to ensure that typname T doesn't change between calls

#pragma once

#define _DEFAULT_SIZE 16

class component_vector {
    void* list_;
    int active_;
    int size_;
    int capacity_;

    component_vector(const component_vector&) = delete;
    component_vector(const component_vector&&) = delete;
    component_vector& operator= (const component_vector&) = delete;
    component_vector& operator= (const component_vector&&) = delete;

public:
    component_vector(int capacity=_DEFAULT_SIZE):
      list_(nullptr),
      active_(0),
      size_(0),
      capacity_(capacity)
    {}

public:
    template<typename T>
    void push(const T& component)
    {
        if (!list_)
            _init<T>();

        if (_isFull())
            _resize<T>();

        T* list = reinterpret_cast<T*>(list_);
        list[size_++] = list[active_];
        list[active_++] = component;
    }

    template<typename T>
    T* get()
    {
        return reinterpret_cast<T*>(list_);
    }

    int size()
    {
        return size_;
    }

    int active()
    {
        return active_;
    }

    int inactive()
    {
        return size_ - active_;
    }

private:
    template<typename T>
    void _init()
    {
        T* list = new T[capacity_];
        list_ = reinterpret_cast<void*>(list);
    }

    template<typename T>
    void _resize()
    {
        T* list = reinterpret_cast<T*>(list_);
        T* newList = new T[2*capacity_];

        for (int i = 0; i < size_; ++i)
        {
            newList[i] = list[i];
        }

        list_ = reinterpret_cast<void*>(newList);
        delete[] list;
    }

    inline
    bool _isFull()
    {
        return (size_ == capacity_);
    }
};
