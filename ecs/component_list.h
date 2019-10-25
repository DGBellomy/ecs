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

public: // modifying functions

    template <typename T> void append(const T& component);
    template <typename T> void remove(int entityID);
    template <typename T> void destroy();
    template <typename T> void activate(int entityID);
    template <typename T> void deactivate(int entityID);
    template <typename T> T* get();
    template <typename T> T* get(int entityID);

public: // accessor functions

    int size() const;
    int active() const;
    bool isActive(int entityID) const;

private: // helper functions

    template <typename T> void _init();
    template <typename T> void _resize();
    template <typename T> void _swapWithActive(int entityID, bool activating);
    inline bool _isFull() const;
    bool _hasEntity(int entityID) const;
};


// PUBLIC MODIFYING FUNCTIONS - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

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
void component_list::destroy()
{
    if (!componentList_)
        return;

    T* componentList = reinterpret_cast<T*>(componentList_);
    delete[] componentList;

    componentList_ = nullptr;
    active_ = 0;
    size_ = 0;
    capacity_ = 0;
    entityToIndex_.clear();
}

template <typename T>
void component_list::activate(int entityID)
{
    _swapWithActive<T>(entityID, true);
}

template <typename T>
void component_list::deactivate(int entityID)
{
    _swapWithActive<T>(entityID, false);
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

// PUBLIC ACCESSOR FUNCTIONS - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int component_list::size() const
{
    return size_;
}

int component_list::active() const
{
    return active_;
}

bool component_list::isActive(int entityID) const
{
    if (!_hasEntity(entityID))
        return false;

    const int index = entityToIndex_.find(entityID)->second;

    return index < active_;
}

// PRIVATE HELPER FUNCTIONS - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

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
void component_list::_swapWithActive(int entityID, bool activating)
{
    if (!_hasEntity(entityID))
        return;

    int index = entityToIndex_[entityID];

    if (activating && (index < active_))
        return;
    if (!activating && (index >= active_))
        return;

    if (!activating)
        --active_;

    T* componentList = reinterpret_cast<T*>(componentList_);
    T component = componentList[active_];
    componentList[active_] = componentList[index];
    componentList[index] = component;

    entityToIndex_[componentList[active_].entityID] = active_;
    entityToIndex_[componentList[index].entityID] = index;

    if (activating)
        ++active_;
}

inline
bool component_list::_isFull() const
{
    return (size_ == capacity_);
}

bool component_list::_hasEntity(int entityID) const
{
    if (!componentList_)
        return false;

    return (entityToIndex_.find(entityID) != entityToIndex_.end());
}
