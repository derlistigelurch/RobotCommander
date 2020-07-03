#ifndef MESSAGEMANAGER_MESSAGEMANAGER_H
#define MESSAGEMANAGER_MESSAGEMANAGER_H

#include <sys/types.h>
#include <sys/stat.h>

#include <string>
#include "Message.h"

class MessageManager
{
public:
    MessageManager();

    ~MessageManager();

    /**
     * Creates a new pipe in the directory which is stated in the RobotCommander.config
     * @param pipe - Path to the pipe
     */
    void CreatePipe();

    /**
     * Deletes the pipe
     * @param pipe - Path to the pipe
     */
    void DeletePipe();

    /**
     * Write something to the Pipe
     */
    void WriteToPipe(const std::string &string);

    /**
     * Reads input from a pipe
     */
    void ReadFromPipe();

    void CreateMsgQueue();

    void DeleteMsgQueue() const;

    void SendMessage();

    std::string ReceiveMessage() const;

    int ioMessageId;
private:
    static const int ERRNO_FILE_EXISTS = 17;
    static const int ERRNO_FILE_NOT_FOUND = 2;
};


#endif //MESSAGEMANAGER_MESSAGEMANAGER_H
