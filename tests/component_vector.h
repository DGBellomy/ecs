/* Author: GarRaptor
 * Description: Dynamic array stored as a void* so that the vector doesn't care what data it's holding
 *   template functions are used to deal with casting so that the end-user doesn't need to worry about that.
 * Uses:
 *   component_vector cv(32);    // uses a default parameter so the size will be _DEFAULT_COMPONENT_VECTOR_SIZE
 *   cv.append<T>(component);    // where T is the type of component you are passing to the vector.
 *   cv.delete<T>(entityID);     // where T is the type of component you are passing to the vector.
 *   cv.activate<T>(entityID);   // activate component with entityID
 *   cv.deactivate<T>(entityID); // deactivate component with entityID
 *   cv.get<T>();                // returns the component array ptr for direct access.
 *   cv.get<T>(entityID);        // returns the component ptr for a particular entityID.
 *   cv.size();                  // total number of components | size_ is always equal to the next empty index pos
 *   cv.active();                // total number of active components | active_ is the first inactive index or size_
 *   cv.inactive();              // total number of inactive components | difference between size_ and active_
 *   cv.isActive(entityID);      // returns if a component with entityID is active
 */

// NOTE: It is important that you use the same typename T for a single component_vector or you will corrupt your data.
// TODO: add "type" std::string member to ensure that typname T doesn't change between calls

#pragma once

#include <map>

#define _DEFAULT_COMPONENT_VECTOR_SIZE 16

class component_vector {
    void* componentList_;
    int active_;
    int size_;
    int capacity_;
    std::map<int, int> entityToIndex_;

    component_vector(const component_vector&) = delete;
    component_vector(const component_vector&&) = delete;
    component_vector& operator= (const component_vector&) = delete;
    component_vector& operator= (const component_vector&&) = delete;

public:
    component_vector(int capacity=_DEFAULT_COMPONENT_VECTOR_SIZE):
      componentList_(nullptr),
      active_(0),
      size_(0),
      capacity_(capacity),
      entityToIndex_()
    {}

public:
    template <typename T>
    void append(const T& component)
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
    void delete(int entityID)
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
    void activate(int entityID)
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
    void deactivate(int entityID)
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
    T* get()
    {
        return reinterpret_cast<T*>(componentList_);
    }

    template <typename T>
    T* get(int entityID)
    {
        if (!_hasEntity(entityID))
            return nullptr;

        T* componentList = reinterpret_cast<T*>(componentList_);
        return &componentList[entityToIndex_[entityID]];
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

    bool isActive(int entityID)
    {
        if (!_hasEntity(entityID))
            return false;

        int index = entityToIndex_[entityID];

        return index < active_;
    }

private:
    template <typename T>
    void _init()
    {
        T* componentList = new T[capacity_];
        componentList_ = reinterpret_cast<void*>(componentList);
    }

    template <typename T>
    void _resize()
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
    void _swapWithActive(int index)
    {
        T* componentList = reinterpret_cast<T*>(componentList_);
        T component = componentList[active_];
        componentList[active_] = componentList[index];
        componentList[index] = component;

        entityToIndex_[componentList[active_].entityID] = active_;
        entityToIndex_[componentList[index].entityID] = index;
    }

    inline
    bool _isFull()
    {
        return (size_ == capacity_);
    }

    bool _hasEntity(int entityID)
    {
        return (entityToIndex_.find(entityID) != entityToIndex_.end());
    }
};
