#ifndef COMPANY_H
#define COMPANY_H


#include <iostream>
#include <string.h>
#include <set>
#include "EscapeRoomWrapper.h"
#include "Enigma.h"

using std::set;
using std::string;

namespace mtm{
    namespace escaperoom{
        
        typedef enum{
            SCARY_ROOM, KIDS_ROOM, BASE_ROOM
        }RoomType;
        
        class Company{
            string name;
            string phoneNumber;
            set<EscapeRoomWrapper*> rooms;
            
        public:
            
            // Constructs a new Company with the specified data.
            //
            // @param name : the name of the company.
            // @param phoneNumber : the phone number of the company.
            //
            Company(string name, string phoneNumber);
            
            //CopyConstructor
            //
            Company(const Company& company);
            
            //Assignment operation
            //
            Company& operator=(const Company& company);
            
            //Function creates a basic escape room using the parameters and adds the room created to the company.
            //
            // @param name : the name of the escape room.
            // @param escapeTime : the maximal escape time allowed in the room.
            // @param level : the level of the escape room.
            // @param maxParticipants: the maximal participants allowed in the room.
            // @throws CompanyMemoryProblemException in case of room creation failure.
            void createRoom(char* name, const int& escapeTime, const int& level, const int& maxParticipants);
            
            //Function creates a scary escape room using the parameters and adds the room created to the company.
            //
            // @param name : the name of the escape room.
            // @param escapeTime : the maximal escape time allowed in the room.
            // @param level : the level of the escape room.
            // @param maxParticipants: the maximal participants allowed in the room.
            // @param ageLimit : the age limit for the room.
            // @param numOfScaryEnigmas : the number of scary enigmas in the room.
            // @throws CompanyMemoryProblemException in case of room creation failure.
            void createScaryRoom(char* name, const int& escapeTime, const int& level,
                                 const int& maxParticipants, const int& ageLimit, const int& numOfScaryEnigmas);
            
            //Function creates a scary escape room using the parameters and adds the room created to the company.
            //
            // @param name : the name of the escape room.
            // @param escapeTime : the maximal escape time allowed in the room.
            // @param level : the level of the escape room.
            // @param maxParticipants: the maximal participants allowed in the room.
            // @param ageLimit : the age limit for the room.
            // @throws CompanyMemoryProblemException in case of room creation failure.
            void createKidsRoom(char* name, const int& escapeTime, const int& level,
                                const int& maxParticipants, const int& ageLimit);
            
            //Function returns a set of all the rooms in the company.
            //
            set<EscapeRoomWrapper*> getAllRooms() const;
            
            //Function removes the room specified from the company.
            //
            // @param room : the room to be removed.
            // @throws : CompanyRoomNotFoundException in case that room doesnt exist in company.
            void removeRoom(const EscapeRoomWrapper& room);
            
            //Function adds the enigma to the room specified.
            //
            // @param room : the room to be updated.
            // @param enigma : the enigma to be added.
            // @throws : CompanyRoomNotFoundException in case that room doesnt exist in company.
            void addEnigma(const EscapeRoomWrapper& room, const Enigma& enigma);
            
            //Function removes the enigma from the room specified.
            //
            // @param room : the room to be updated.
            // @param enigma : the enigma to be removed.
            // @throws : CompanyRoomNotFoundException in case that room doesnt exist in company.
            // @throws : CompanyRoomHasNoEnigmasException in case the room is empty.
            // @throws : CompanyRoomEnigmaNotFoundException in case enigma doesnt exist in room.
            void removeEnigma(const EscapeRoomWrapper& room, const Enigma& enigma);
            
            //Function adds the item to the enigma from the room specified.
            //
            // @param room : the room to be updated.
            // @param enigma : the enigma to be updated.
            // @param element : the element to be added.
            // @throws : CompanyRoomNotFoundException in case that room doesnt exist in company.
            // @throws : CompanyRoomEnigmaNotFoundException in case enigma doesnt exist in room.
            void addItem(const EscapeRoomWrapper& room, const Enigma& enigma, const string& element);
            
            //Function removes the item from the enigma from the room specified.
            //
            // @param room : the room to be updated.
            // @param enigma : the enigma to be removed.
            // @param element : the element to be removed.
            // @throws : CompanyRoomNotFoundException in case that room doesnt exist in company.
            // @throws : CompanyRoomEnigmaNotFoundException in case enigma doesnt exist in room.
            // @throws : CompanyRoomEnigmaHasNoElementsException in case enigma has no elements;
            // @throws : CompanyRoomEnigmaElementNotFoundException in case element doesnt exist in enigma.
            void removeItem(const EscapeRoomWrapper& room, const Enigma& enigma, const string& element);
            
            //Function returns all the rooms in the specified type.
            //
            // @param: type : the type requested.
            set<EscapeRoomWrapper*> getAllRoomsByType(RoomType type) const;
            
            
            //Function returns the room with the specified name.
            //
            // @param: name : the name of the room requested.
            // @throws: CompanyRoomNotFoundException if room doesnt exist.
            EscapeRoomWrapper* getRoomByName(const string& name) const;
            
            
            // Prints the data of the company in the following format:
            //
            //     "<CompanyName> : <PhoneNumber>
            //      <Room>
            //      <Room> …"
            //
            // @param output : the output stream to which the data is printed.
            // @param company : the company whose data is printed.
            friend std::ostream& operator<<(std::ostream& output, const Company& company);
            
            //Function returns the company name.
            //
            string getName() const;
            
            //Function returns the company's phone number.
            //
            string getPhone() const;
            
            //Destructor
            ~Company();
        };
        
        std::ostream& operator<<(std::ostream& output, const Company& company);
    }
}


#endif //COMPANY_H
