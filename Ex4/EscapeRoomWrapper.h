#ifndef ESCAPEROOMWRAPPER_H
#define ESCAPEROOMWRAPPER_H

#include <string>
#include <iostream>
#include "EscapeRoom.h"
#include <vector>
#include "Enigma.h"

using std::string;
using std::vector;

namespace mtm{
namespace escaperoom {

    class EscapeRoomWrapper{
        EscapeRoom room;
        vector<Enigma> enigmas;
        
    public:
        // Constructs a new Escape Room with the specified data.
        //
        // @param name : the name of the escape room.
        // @param escapeTime : the maximal escape time allowed in the room.
        // @param level : the level of the escape room.
        // @param maxParticipants: the maximal participants allowed in the room.
        // The rest of the room's data is initialized as described in the exercise sheet.
        // @throws EscapeRoomMemoryProblemException in case of creation failure.
        EscapeRoomWrapper(char* name, const int& escapeTime, const int& level,
                          const int& maxParticipants);

        // Constructs a new Escape Room with the specified data.
        //
        // @param name : the name of the enigma.
        // @param level : the level of the escape room.
        // The rest of the room's data is initialized as described in the exercise sheet.
        // @throws EscapeRoomMemoryProblemException in case of creation failure.
        EscapeRoomWrapper(char* name, const int& level);

        //copy constructor
        //
        //@param room : the room to be copied.
        //@throws EscapeRoomMemoryProblemException in case of creation failure.
        EscapeRoomWrapper(const EscapeRoomWrapper& room);

        //assignment operator
        //
        //@param room : the room to be assigned.
        virtual EscapeRoomWrapper& operator=(const EscapeRoomWrapper& room);

        // Comparison operators for Escape Rooms. rooms are compared as described in
        // the exercise sheet.
        //
        // @param room : the right-hand side operand.
        bool operator==(const EscapeRoomWrapper& room) const;
        bool operator!=(const EscapeRoomWrapper& room) const;
        bool operator<(const EscapeRoomWrapper& room) const;
        bool operator>(const EscapeRoomWrapper& room) const;

        bool operator<=(const EscapeRoomWrapper& room) const = delete;
        bool operator>=(const EscapeRoomWrapper& room) const = delete;

        // return the level of the Escape Room.
        //
        int level() const;

        // the method changes the rate according to the rate given.
        //
        // @param newRate : the new rate accepted to the room.
        //@throws EscapeRoomIllegalRateException in case of illegal rate parameter.
        void rate(const int& newRate)/* const*/;

        // Destructor for EscapeRoomWrapper
        virtual ~EscapeRoomWrapper();

        // Prints the data of the Room in the following format:
        //
        //     "<name> (<maxTime>/<level>/<maxParticipants>)"
        //
        // @param output : the output stream to which the data is printed.
        // @param room : the room whose data is printed.
        friend std::ostream& operator<<(std::ostream& output, const EscapeRoomWrapper& room);

        //Function returns the name of the EscapeRoom.
        //
        std::string getName() const;

        //Function returns the rate of the EscapeRoom.
        //
        double getRate() const;

        //Function returns the maximum escape time of the EscapeRoom.
        //
        int getMaxTime() const;

        //Function returns the number of participants allowed in the EscapeRoom.
        //
        int getMaxParticipants() const;

        //Function add new enigma to the EscapeRoom's vector.
        // @param enigma the new enigma to add
        //
        void addEnigma(const Enigma& enigma);
        
        //Function remove current enigma from the EscapeRoom's vector
        // @param enigma the enigma to remove from the EscapeRoom
        // in case of room without enigmas at the currect EscapeRoom the function
        // would throw EscapeRoomNoEnigmasException() exception.
        // in case that the current enigma to remove, isn't apart of this room
        // the function would throw EscapeRoomNotFoundException() exception.
        //
        void removeEnigma(const Enigma& enigma);
        
        // Function finds the hardest enigma from the current EscapeRoom,
        // in case of couple of enigmas with the hardest difficulty in the room,
        // the first enigma with this difficulty would be returned.
        // in case of room without enigmas at the currect EscapeRoom the function
        // would throw EscapeRoomNoEnigmasException() exception.
        //
        Enigma getHardestEnigma();
        
        // Function returns the vector of Enigmas at this EscapeRoom
        //
        vector<Enigma>& getAllEnigmas();
        
        //Function adds the item to the enigma.
        //
        // @param enigma : the enigma to be updated.
        // @param element : the element to be added.
        // @throws : EscapeRoomEnigmaNotFoundException in case enigma doesnt exist in room.
        void addItem(const Enigma& enigma, const string& element);
        
        //Function removes the item from the enigma.
        //
        // @param enigma : the enigma to be removed.
        // @param element : the element to be removed.
        // @throws : EscapeRoomEnigmaNotFoundException in case enigma doesnt exist in room.
        // @throws : EscapeRoomEnigmaHasNoElementsException in case enigma has no elements;
        // @throws : EscapeRoomEnigmaElementNotFoundException in case element doesnt exist in enigma.
        void removeItem(const Enigma& enigma, const string& element);
        
        //clone(copy) function for virtual copy
        //
        //@param room : the room to be copied.
        //@throws EscapeRoomMemoryProblemException in case of creation failure.
        virtual EscapeRoomWrapper* clone() const;
    };

    std::ostream& operator<<(std::ostream& output, const EscapeRoomWrapper& room);
} // end of namespace eascaperoom
} // end of namespace mtm


#endif //ESCAPEROOMWRAPPER_H
