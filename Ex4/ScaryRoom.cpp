

#include "ScaryRoom.h"
#include "Exceptions.h"

using mtm::escaperoom::ScaryRoom;
using mtm::escaperoom::EscapeRoomWrapper;
using mtm::MtmException;

ScaryRoom::ScaryRoom(char* name, const int& escapeTime, const int& level,
                     const int& maxParticipants, const int& ageLimit,
                     const int& numOfScaryEnigmas) :
                    EscapeRoomWrapper(name, escapeTime, level, maxParticipants),
                       ageLimit(ageLimit), numOfScaryEnigmas(numOfScaryEnigmas){
    
}


ScaryRoom::ScaryRoom(const ScaryRoom& room) : EscapeRoomWrapper(room){
    this->setNewAgeLimit(room.getAgeLimit());
    this->numOfScaryEnigmas = room.numOfScaryEnigmas;
}

ScaryRoom& ScaryRoom::operator=(const ScaryRoom& room){
    if (*this == room){
        return *this;
    }
    static_cast<EscapeRoomWrapper>(*this) =
                                    static_cast<const EscapeRoomWrapper>(room);
    
    this->setNewAgeLimit(room.getAgeLimit());
    this->numOfScaryEnigmas = room.numOfScaryEnigmas;
    return *this;
}

void ScaryRoom::setNewAgeLimit(const int& limit){
    if (limit < 0){
        throw ScaryRoomIllegalAgeLimit();
    }
    this->ageLimit = limit;
}

void ScaryRoom::incNumberOfScaryEnigmas(){
    this->numOfScaryEnigmas++;
}

int ScaryRoom::getAgeLimit() const{
    return this->ageLimit;
}

EscapeRoomWrapper* ScaryRoom::clone() const{
    return new ScaryRoom(*this);
}

std::ostream& mtm::escaperoom::operator<<(std::ostream& output,
                                          const ScaryRoom& room){
    string name = room.getName();
    int time = room.getMaxTime();
    int level = room.level();
    int participants = room.getMaxParticipants();
    int ageLimit = room.getAgeLimit();
    return output  << "Scary Room: " << name << " (" << time << "/" << level
                    << "/" << participants << "/" << ageLimit << ")";
}

