/* Author: GarRaptor
 * Description: Interface to the Entity Component System
 */

#pragma once

#include <vector>

typedef void (*sysFuncPtr)(void);

class System {
};

class Systems {
    std::vector<sysFuncPtr> systems_;
};
