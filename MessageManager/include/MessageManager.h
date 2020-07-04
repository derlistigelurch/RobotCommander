#ifndef MESSAGEMANAGER_MESSAGEMANAGER_H
#define MESSAGEMANAGER_MESSAGEMANAGER_H

#include <sys/types.h>
#include <sys/stat.h>

#include <string>
#include "Message.h"
#include "../../IOManager/include/Sender.h"

class MessageManager : public Sender
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
     * @param content
     */
    void WriteToPipe(const std::string &content);

    /**
     * Reads input from a pipe
     */
    void ReadFromPipe();

    /**
     * Creates a new messagequeue, saves id into ioMessageId
     * @param identifier - key identifier as a string to get the correct key
     */
    void CreateMsgQueue(const std::string& identifier);

    /**
     *
     * @param identifier
     */
    void DeleteMsgQueue(const std::string& identifier) const;

    /**
     * Sends a new Message to the Message queue
     * @param type
     * @param text
     * @param identifier
     */
    // void SendMessage(long type, const std::string &text, const std::string& identifier) const;

    /**
     * Receives a message from the messagequeue (waits for message)
     * @return returns a new message struct from the messagequeue
     */
    // Message ReceiveMessage(const std::string& identifier) const;

    // int ioMessageId;
    // int gameMessageId;
    // inline static const std::string IO = "IO";
    // inline static const std::string GAME = "GAME";

private:
    // int getId(const std::string &identifier) const;

    // void setId(int id, const std::string &identifier);

    // int getKey(const std::string &identifier) const;

    static const int ERRNO_FILE_EXISTS = 17;
    static const int ERRNO_FILE_NOT_FOUND = 2;
    static const int FIGHT = 1;
    static const int CREATOR = 2;
    static const int EXIT = 3;
};


#endif //MESSAGEMANAGER_MESSAGEMANAGER_H
