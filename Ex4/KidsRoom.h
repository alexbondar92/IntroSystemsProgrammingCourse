#ifndef KIDSROOM_H
#define KIDSROOM_H

#include <iostream>
#include <string>
#include <set>
#include "EscapeRoomWrapper.h"

namespace mtm{
    namespace escaperoom{
        class KidsRoom : public EscapeRoomWrapper{
            int ageLimit;

        public:
            // Constructs a new Kids Room with the specified data.
            //
            // @param name : the name of the escape room.
            // @param escapeTime : the maximal escape time allowed in the room.
            // @param level : the level of the escape room.
            // @param maxParticipants: the maximal participants allowed in the room.
            // @param ageLimit: the age limit for this room
            // The rest of the room's data is initialized as described in the exercise sheet.
            // @throws EscapeRoomMemoryProblemException in case of creation failure.
            KidsRoom(char* name, const int& escapeTime, const int& level,
                     const int& maxParticipants, const int& ageLimit);
            
            //copy constructor
            //
            //@param room : the room to be copied.
            //@throws EscapeRoomMemoryProblemException in case of creation failure.
            KidsRoom(const KidsRoom& room);
            
            //assignment operator
            //
            //@param room : the room to be assigned.
            KidsRoom& operator=(const KidsRoom& room);
            
            // the method changes the Age limit according to the limit given.
            //
            // @param limit : the new limit accepted to the room.
            //@throws ScaryRoomIllegalAgeLimit in case of illegal age limit parameter.
            void setNewAgeLimit(const int& limit);
            
            //Function returns the age limit allowed in the Kids room.
            //
            int getAgeLimit() const;
            
            //clone(copy) function for virtual copy
            //
            //@param room : the room to be copied.
            //@throws EscapeRoomMemoryProblemException in case of creation failure.
            EscapeRoomWrapper* clone() const;

            // Prints the data of the Room in the following format:
            //
            //     "Kids Room: <name> (<maxTime>/<level>/<maxParticipants>/<ageLimit>)"
            //
            // @param output : the output stream to which the data is printed.
            // @param room : the room whose data is printed.
            friend std::ostream& operator<<(std::ostream& output,
                                            const KidsRoom& room);
        };
        
        std::ostream& operator<<(std::ostream& output, const KidsRoom& room);
    }
}

#endif //KIDSROOM_H
