#ifndef IOMANAGER_SENDER_H
#define IOMANAGER_SENDER_H


#include <string>
#include "../../MessageManager/include/Message.h"

class Sender
{
protected:
    /**
     *
     * @param identifier
     * @return
     */
    int getId(const std::string &identifier) const;

    /**
     *
     * @param id
     * @param identifier
     */
    void setId(int id, const std::string &identifier);

    /**
     *
     * @param identifier
     * @return
     */
    int getKey(const std::string &identifier) const;

    /**
     *
     * @param identifier
     * @return
     */
    std::string getPipe(const std::string &identifier) const;

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
    virtual void SendMessage(long type, const std::string &text, const std::string& identifier) const;

    /**
     * Receives a message from the messagequeue (waits for message)
     * @return returns a new message struct from the messagequeue
     */
    virtual Message ReceiveMessage(const std::string& identifier) const;

    /**
     *
     * @param identifier
     */
    virtual void GetMessageQueue(const std::string& identifier);

    /**
     *
     * @param microseconds
     */
    void Wait(int microseconds) const;

    int ioMessageId;
    int gameMessageId;

    inline static const std::string IO = "IO";
    inline static const std::string GAME = "GAME";
    inline static const std::string MAP = "MAP";
    inline static const std::string LOG = "LOG";
    inline static const std::string STATS = "STATS";
};


#endif //IOMANAGER_SENDER_H
