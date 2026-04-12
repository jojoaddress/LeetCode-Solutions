 using NewMessageCallback = std::function<void (const QSharedPointer<HL7::Message> &)>;

void HL7MessageSender::setNewMessageCallback(NewMessageCallback cb)
{
    pimpl->newMessageCb = cb;
}
HL7MessageSender::getInstance()->setNewMessageCallback([=](const QSharedPointer<HL7::Message> &msg)
                                                       {
                /* set HL7 data to the last client */
                auto clients = rfCommServer->clients();
                if (clients.isEmpty())
                {
                    return;
                }
                auto lastClient = clients.last();
                lastClient->write(msg->toString().toUtf8());
                lastClient->write("\n"); });
