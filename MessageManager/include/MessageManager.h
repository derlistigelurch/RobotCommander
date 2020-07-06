#ifndef MESSAGEMANAGER_MESSAGEMANAGER_H
#define MESSAGEMANAGER_MESSAGEMANAGER_H

#include <sys/types.h>
#include <sys/stat.h>

#include <string>
#include "Message.h"
#include "../../IOManager/include/Sender.h"

class MessageManager : public Sender
{
private:
    static const int ERRNO_FILE_EXISTS = 17;
    static const int ERRNO_FILE_NOT_FOUND = 2;
    static const int FIGHT = 1;
    static const int CREATOR = 2;
    static const int EXIT = 3;

public:
    MessageManager();

    ~MessageManager();

    /**
     * Creates a new pipe in the directory which is stated in the RobotCommander.config, does nothing if file exists
     * @param identifier - string identifier to create the correct pipe
     */
    void CreatePipe(const std::string &identifier);

    /**
     * Deletes the pipe, nothing happens if file not exists
     * @param identifier - string identifier to delete the correct pipe
     */
    void DeletePipe(const std::string &identifier);

    /**
     * Creates a new messagequeue, saves id into ioMessageId
     * @param identifier - string identifier to get the correct key
     */
    void CreateMsgQueue(const std::string &identifier);

    /**
     * Deletes a messagequeue, exits on failure
     * @param identifier - string identifier to delete the correct messagequeue
     */
    void DeleteMsgQueue(const std::string &identifier) const;
};


#endif //MESSAGEMANAGER_MESSAGEMANAGER_H
