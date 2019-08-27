#ifndef COMPONENT_H
#define COMPONENT_H

class Component {
protected:
    unsigned int _key;

    Component(unsigned int key):_key(key){};

public:
    unsigned int getKey() { return this->_key; };
};

#endif //COMPONENT_H
