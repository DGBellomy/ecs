#include <stdio.h>
#include <string>

#include "utils.h"

#define PI 3.1415

class Test {
    const int c_MyInt = 45;
    enum {LookAtThisMa=13};

public:
    const int& getInt()
    {
        return c_MyInt;
    }

    virtual void getMa() = 0;
};

class STest : public Test {
    virtual void getMa()
    {
        printf("Hello World!");
    }
};


void compare_func_ptrs()
{
    void* pv = 0;
    void (*pfn)() = 0;
    int STest::*pmv = 0;
    void (STest::*pmf)(int) const = 0;

    printf("pv: %lu\n", sizeof(pv));
    printf("pfn: %lu\n", sizeof(pfn));
    printf("pmv: %lu\n", sizeof(pmv));
    printf("pmf: %lu\n", sizeof(pmf));
}

void check_tolower()
{
    std::string name = "HERALD\n";
    printf("name: %s", dgb::utils::tolower(name).c_str());
    printf("name: %s", dgb::utils::tolower("HELLO\n").c_str());
}

int main()
{
    check_tolower();

    return 0;
}

