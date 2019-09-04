//
// Created by Garrett Bellomy on 2019-09-04.
//

#ifndef ECS_EXAMPLES_DISPLAYMESSAGESYSTEM_H
#define ECS_EXAMPLES_DISPLAYMESSAGESYSTEM_H

class DisplayMessageSystem : public ISystem {
    MessageComponent* _messageComponents;

public:
    virtual void run() override
    {
        for (int i = 0; i < 55; ++i)
        {
            printf("%s", _messageComponents[i].message);
        }
    }
};

#endif //ECS_EXAMPLES_DISPLAYMESSAGESYSTEM_H
