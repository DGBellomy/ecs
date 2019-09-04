//
// Created by Garrett Bellomy on 2019-09-04.
//

#ifndef ECS_EXAMPLES_GETMESSAGESYSTEM_H
#define ECS_EXAMPLES_GETMESSAGESYSTEM_H

class GetMessageSystem : public ISystem {
    MessageComponent* _messageComponents;

public:
    virtual void run() override
    {
        for (int i = 0; i < 55; ++i)
        {
            char buffer[256];
            sprintf(buffer, "this message is from %d", _messageComponents[i].entity_id);
            _messageComponents[i].message = buffer;
        }
    }
};

#endif //ECS_EXAMPLES_GETMESSAGESYSTEM_H
