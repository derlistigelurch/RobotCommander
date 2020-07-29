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

    static const char REGISTRATION = 'R';
    static const char FIGHT = 'F';
    static const char EXIT = 'E';

public:
    MessageManager();

    ~MessageManager();

    /**
     * Creates a new pipe in the directory which is stated in the RobotCommander.config, does nothing if file exists
     * @param identifier
     */
    void CreatePipe(const std::string &identifier);

    /**
     * Deletes the pipe, nothing happens if file not exists
     * @param identifier
     */
    void DeletePipe(const std::string &identifier);

    /**
     * Creates a new messagequeue, saves id into ioMessageId
     * @param identifier
     */
    void CreateMsgQueue(const std::string &identifier);

    /**
     * Deletes a messagequeue, exits on failure
     * @param identifier
     */
    void DeleteMsgQueue(const std::string &identifier) const;

    /**
     * starts the main loop of the message manager, where it receives and processes messages from the user
     */
    void Run();
};


#endif //MESSAGEMANAGER_MESSAGEMANAGER_H
