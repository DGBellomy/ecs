/* Author: GarRaptor
 * Description: Dynamic array stored as a void* so that the list doesn't care what data it's holding
 *   template functions are used to deal with casting so that the end-user doesn't need to worry about that.
 */

#pragma once

#include "Common.h"

#define _DEFAULT_COMPONENT_VECTOR_SIZE 16

namespace ecs {
    namespace component {

        class ComponentList {
            void *componentList_;
            int active_;
            int size_;
            int capacity_;
            std::map<EntityId, int> entityToIndex_;
            size_t componentSize_;


        public:

            ComponentList(int capacity = _DEFAULT_COMPONENT_VECTOR_SIZE) :
                    componentList_(nullptr),
                    active_(0),
                    size_(0),
                    capacity_(capacity),
                    entityToIndex_(),
                    componentSize_(0) {}


            template<typename T>
            T *append(const T &component) {
                if (!componentList_)
                    _init<T>();

                if (!_matchSize<T>())
                    return nullptr;

                if (_hasEntity(component.entityID))
                    return nullptr;

                if (_isFull())
                    _resize<T>();

                T *componentList = reinterpret_cast<T *>(componentList_);
                componentList[size_++] = componentList[active_];
                componentList[active_++] = component;

                entityToIndex_[componentList[active_ - 1].entityID] = active_ - 1;
                entityToIndex_[componentList[size_ - 1].entityID] = size_ - 1;

                return &componentList[active_ - 1];
            }

            template<typename T>
            void remove(EntityId entityID) {
                if (!_matchSize<T>())
                    return;

                if (!_hasEntity(entityID))
                    return;

                int index = entityToIndex_[entityID];
                entityToIndex_.erase(entityID);
                T *componentList = reinterpret_cast<T *>(componentList_);

                if (index < active_) {
                    componentList[index] = componentList[active_ - 1];
                    entityToIndex_[componentList[index].entityID] = index;
                    index = --active_;
                }
                componentList[index] = componentList[size_ - 1];
                entityToIndex_[componentList[index].entityID] = index;
                --size_;
            }

            template<typename T>
            void destroy() {
                if (!componentList_)
                    return;

                if (!_matchSize<T>())
                    return;

                T *componentList = reinterpret_cast<T *>(componentList_);
                delete[] componentList;

                componentList_ = nullptr;
                active_ = 0;
                size_ = 0;
                capacity_ = 0;
                entityToIndex_.clear();
            }

            template<typename T>
            void activate(EntityId entityID) {
                if (!_matchSize<T>())
                    return;

                _swapWithActive<T>(entityID, true);
            }

            template<typename T>
            void deactivate(EntityId entityID) {
                if (!_matchSize<T>())
                    return;

                _swapWithActive<T>(entityID, false);
            }

            template<typename T>
            T *get() {
                if (!_matchSize<T>())
                    return nullptr;

                return reinterpret_cast<T *>(componentList_);
            }

            template<typename T>
            T *get(EntityId entityID) {
                if (!_matchSize<T>())
                    return nullptr;

                if (!_hasEntity(entityID))
                    return nullptr;

                T *componentList = reinterpret_cast<T *>(componentList_);
                return &componentList[entityToIndex_[entityID]];
            }


            int size() const {
                return size_;
            }

            int active() const {
                return active_;
            }

            bool isActive(EntityId entityID) const {
                if (!_hasEntity(entityID))
                    return false;

                const int index = entityToIndex_.find(entityID)->second;

                return index < active_;
            }

        private:

            ComponentList(const ComponentList &) = delete;

            ComponentList(const ComponentList &&) = delete;

            ComponentList &operator=(const ComponentList &) = delete;

            ComponentList &operator=(const ComponentList &&) = delete;


            template<typename T>
            void _init() {
                T *componentList = new T[capacity_];
                componentList_ = reinterpret_cast<void *>(componentList);
                componentSize_ = sizeof(T);
            }

            template<typename T>
            void _resize() {
                T *componentList = reinterpret_cast<T *>(componentList_);
                T *newList = new T[2 * capacity_];

                for (int i = 0; i < size_; ++i) {
                    newList[i] = componentList[i];
                }

                componentList_ = reinterpret_cast<void *>(newList);
                delete[] componentList;
            }

            template<typename T>
            void _swapWithActive(EntityId entityID, bool activating) {
                if (!_hasEntity(entityID))
                    return;

                int index = entityToIndex_[entityID];

                if (activating && (index < active_))
                    return;
                if (!activating && (index >= active_))
                    return;

                if (!activating)
                    --active_;

                T *componentList = reinterpret_cast<T *>(componentList_);
                T component = componentList[active_];
                componentList[active_] = componentList[index];
                componentList[index] = component;

                entityToIndex_[componentList[active_].entityID] = active_;
                entityToIndex_[componentList[index].entityID] = index;

                if (activating)
                    ++active_;
            }

            inline
            bool _isFull() const {
                return (size_ == capacity_);
            }

            bool _hasEntity(EntityId entityID) const {
                if (!componentList_)
                    return false;

                return (entityToIndex_.find(entityID) != entityToIndex_.end());
            }

            template<typename T>
            bool _matchSize() const {
                return sizeof(T) == componentSize_;
            }
        };
    };
};
