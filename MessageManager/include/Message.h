#ifndef MESSAGEMANAGER_MESSAGE_H
#define MESSAGEMANAGER_MESSAGE_H

#include <string>

struct Message
{
    long type;
    char text[1024];
};

#endif //MESSAGEMANAGER_MESSAGE_H
