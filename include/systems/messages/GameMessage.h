#ifndef GAMEMESSAGE_H
#define GAMEMESSAGE_H

namespace systems
{
    namespace messages
    {
        enum MessageID { ContextUpdate = 10, CreateObject, DelteObject };

        struct GameMessage
        {
            int id;
        };
    }
}

#endif // GAMEMESSAGE_H
