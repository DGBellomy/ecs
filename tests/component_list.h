/* Author: GarRaptor
 * Description: Dynamic array stored as a void* so that the list doesn't care what data it's holding
 *   template functions are used to deal with casting so that the end-user doesn't need to worry about that.
 */

#pragma once

#include <map>

#define _DEFAULT_COMPONENT_VECTOR_SIZE 16

class component_list {
    void* componentList_;
    int active_;
    int size_;
    int capacity_;
    std::map<int, int> entityToIndex_;

    component_list(const component_list&) = delete;
    component_list(const component_list&&) = delete;
    component_list& operator= (const component_list&) = delete;
    component_list& operator= (const component_list&&) = delete;

public:
    component_list(int capacity=_DEFAULT_COMPONENT_VECTOR_SIZE):
      componentList_(nullptr),
      active_(0),
      size_(0),
      capacity_(capacity),
      entityToIndex_()
    {}

public:
    template <typename T>
    void append(const T& component);

    template <typename T>
    void remove(int entityID);

    template <typename T>
    void activate(int entityID);

    template <typename T>
    void deactivate(int entityID);

    template <typename T>
    T* get();

    template <typename T>
    T* get(int entityID);


public:

    int size();

    int active();

    int inactive();

    bool isActive(int entityID);


private:
    template <typename T>
    void _init();

    template <typename T>
    void _resize();

    template <typename T>
    void _swapWithActive(int index);

    inline
    bool _isFull();

    bool _hasEntity(int entityID);
};


// PUBLIC

template <typename T>
void component_list::append(const T& component)
{
    if (!componentList_)
        _init<T>();

    if (_isFull())
        _resize<T>();

    T* componentList = reinterpret_cast<T*>(componentList_);
    componentList[size_++] = componentList[active_];
    componentList[active_++] = component;

    entityToIndex_[component.entityID] = active_ - 1;
    entityToIndex_[componentList[size_ - 1].entityID] = size_ - 1;
}

template <typename T>
void component_list::remove(int entityID)
{
    if (!componentList_)
        return;

    if (!_hasEntity(entityID))
        return;

    int index = entityToIndex_[entityID];
    entityToIndex_.erase(entityID);
    T* componentList = reinterpret_cast<T*>(componentList_);

    if (index < active_)
    {
        componentList[index] = componentList[active_ - 1];
        entityToIndex_[componentList[index].entityID] = index;
        index = --active_;
    }
    componentList[index] = componentList[size_ - 1];
    entityToIndex_[componentList[index].entityID] = index;
    --size_;
}

template <typename T>
void component_list::activate(int entityID)
{
    if (!componentList_)
        return;

    if (!_hasEntity(entityID))
        return;

    int index = entityToIndex_[entityID];
    
    if (index < active_)
        return;

    _swapWithActive<T>(index);
    ++active_;
}

template <typename T>
void component_list::deactivate(int entityID)
{
    if (!componentList_)
        return;

    if (!_hasEntity(entityID))
        return;

    int index = entityToIndex_[entityID];
    
    if (index >= active_)
        return;

    --active_;
    _swapWithActive<T>(index);
}

template <typename T>
T* component_list::get()
{
    return reinterpret_cast<T*>(componentList_);
}

template <typename T>
T* component_list::get(int entityID)
{
    if (!_hasEntity(entityID))
        return nullptr;

    T* componentList = reinterpret_cast<T*>(componentList_);
    return &componentList[entityToIndex_[entityID]];
}

// PUBLIC ACCESSOR FUNCTIONS

int component_list::size()
{
    return size_;
}

int component_list::active()
{
    return active_;
}

int component_list::inactive()
{
    return size_ - active_;
}

bool component_list::isActive(int entityID)
{
    if (!_hasEntity(entityID))
        return false;

    int index = entityToIndex_[entityID];

    return index < active_;
}

// PRIVATE

template <typename T>
void component_list::_init()
{
    T* componentList = new T[capacity_];
    componentList_ = reinterpret_cast<void*>(componentList);
}

template <typename T>
void component_list::_resize()
{
    T* componentList = reinterpret_cast<T*>(componentList_);
    T* newList = new T[2*capacity_];

    for (int i = 0; i < size_; ++i)
    {
        newList[i] = componentList[i];
    }

    componentList_ = reinterpret_cast<void*>(newList);
    delete[] componentList;
}

template <typename T>
void component_list::_swapWithActive(int index)
{
    T* componentList = reinterpret_cast<T*>(componentList_);
    T component = componentList[active_];
    componentList[active_] = componentList[index];
    componentList[index] = component;

    entityToIndex_[componentList[active_].entityID] = active_;
    entityToIndex_[componentList[index].entityID] = index;
}

inline
bool component_list::_isFull()
{
    return (size_ == capacity_);
}

bool component_list::_hasEntity(int entityID)
{
    return (entityToIndex_.find(entityID) != entityToIndex_.end());
}
