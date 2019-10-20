#include "KidsRoom.h"
#include "Exceptions.h"

using mtm::escaperoom::KidsRoom;
using mtm::escaperoom::EscapeRoomWrapper;
using mtm::MtmException;

KidsRoom::KidsRoom(char* name, const int& escapeTime, const int& level,
                     const int& maxParticipants, const int& ageLimit) :
                    EscapeRoomWrapper(name, escapeTime, level, maxParticipants),
                    ageLimit(ageLimit){
    
}

KidsRoom& KidsRoom::operator=(const KidsRoom& room){
    if (*this == room){
        return *this;
    }
    
    static_cast<EscapeRoomWrapper>(*this) =
                    static_cast<const EscapeRoomWrapper>(room);
    
    this->setNewAgeLimit(room.getAgeLimit());
    return *this;
}

void KidsRoom::setNewAgeLimit(const int& limit){
    if (limit < 0){
        throw KidsRoomIllegalAgeLimit();
    }
    this->ageLimit = limit;
}

int KidsRoom::getAgeLimit() const{
    return this->ageLimit;
}

KidsRoom::KidsRoom(const KidsRoom& room) : EscapeRoomWrapper(room){
    this->setNewAgeLimit(room.getAgeLimit());
}

EscapeRoomWrapper* KidsRoom::clone() const{
    return new KidsRoom(*this);
}

std::ostream& mtm::escaperoom::operator<<(std::ostream& output,
                                          const KidsRoom& room){
    string name = room.getName();
    int time = room.getMaxTime();
    int level = room.level();
    int participants = room.getMaxParticipants();
    int ageLimit = room.getAgeLimit();
    return output  << "Kids Room: " << name << " (" << time << "/"
                    << level << "/" << participants << "/" << ageLimit << ")";
}

