#ifndef IOMANAGER_SENDER_H
#define IOMANAGER_SENDER_H


#include <string>
#include "../../MessageManager/include/Message.h"

class Sender
{
protected:
    /**
     * Returns the messagequeue id based on a given identifier
     * @param identifier
     * @return
     */
    int GetId(const std::string &identifier) const;

    /**
     * Sets the messagequeue id based on a given identifier
     * @param id
     * @param identifier
     */
    void SetId(int id, const std::string &identifier);

    /**
     * Returns the key of a messagequeue based on a given identifier
     * @param identifier
     * @return
     */
    int GetKey(const std::string &identifier) const;

    /**
     * Returns the path to a pipe based on a given identifier
     * @param identifier
     * @return Returns the path to a pipe
     */
    std::string GetPipe(const std::string &identifier) const;

public:
    Sender() = default;

    virtual ~Sender() = default;

    /**
     * Write something to the Pipe
     * @param content
     * @param identifier
     */
    virtual void WriteToPipe(const std::string &content, const std::string &identifier) const;

    /**
     * Reads input from a pipe
     * @param identifier
     */
    virtual void ReadFromPipe(const std::string &identifier) const;

    /**
     * Sends a new Message to the Message queue
     * @param type
     * @param text
     * @param identifier
     */
    virtual void SendMessage(long type, const std::string &text, const std::string &identifier) const;

    /**
     * Receives a message from the messagequeue (waits for message)
     * @return returns a new message struct from the messagequeue
     */
    virtual Message ReceiveMessage(const std::string &identifier) const;

    /**
     * Get the id from a messagequeue based on a given identifier
     * @param identifier
     */
    virtual void GetMessageQueue(const std::string &identifier);

    /**
     * Wait for n microseconds
     * @param microseconds
     */
    void Wait(int microseconds) const;

    int ioMessageId;
    int gameMessageId;

    static const int ERR_KEY_NOT_FOUND = 59;
    static const int ERR_ID_NOT_FOUND = 60;

    inline static const std::string IO = "IO";
    inline static const std::string GAME = "GAME";
    inline static const std::string MAP = "MAP";
    inline static const std::string LOG = "LOG";
    inline static const std::string STATS = "STATS";
    inline static const std::string ERR_PIPE_NOT_FOUND = "";
};


#endif //IOMANAGER_SENDER_H
