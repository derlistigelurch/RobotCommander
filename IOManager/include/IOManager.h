#ifndef IOMANAGER_IOMANAGER_H
#define IOMANAGER_IOMANAGER_H


#include <string>

#include "../../MessageManager/include/Message.h"
#include "Sender.h"

class IOManager : public Sender
{
public:
    IOManager() = default;

    ~IOManager() = default;

    void GameMode();
};


#endif //IOMANAGER_IOMANAGER_H
