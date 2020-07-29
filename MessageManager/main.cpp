#include <memory>

#include "include/Message.h"
#include "include/MessageManager.h"
#include "include/ConfigManager.h"

int main()
{
    std::shared_ptr<MessageManager> messageManager = std::make_shared<MessageManager>();

    system(("gnome-terminal -- " + ConfigManager().ioPath).c_str());

    messageManager->Run();
}