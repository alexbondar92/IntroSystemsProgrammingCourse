#include <stdio.h>
#include "EscapeRoomWrapper.h"
#include "Exceptions.h"
#include <string>

using mtm::escaperoom::EscapeRoomWrapper;
using mtm::MtmException;



EscapeRoomWrapper::EscapeRoomWrapper(char* name, const int& escapeTime,
                                     const int& level,
                                     const int& maxParticipants){
    this->room = escapeRoomCreate(name, escapeTime, maxParticipants ,level);
    if (this->room == NULL){
        throw EscapeRoomMemoryProblemException();
    }
    this->enigmas = vector<Enigma>();
}

EscapeRoomWrapper::EscapeRoomWrapper(char* name, const int& level){
    this->room = escapeRoomCreate(name, 60, 6, level);
    if (this->room == NULL){
        throw EscapeRoomMemoryProblemException();
    }
    this->enigmas = vector<Enigma>();
}

EscapeRoomWrapper::EscapeRoomWrapper(const EscapeRoomWrapper& room){
    this->room = escapeRoomCopy(room.room);
    if (this->room == NULL){
        throw EscapeRoomMemoryProblemException();
    }
    this->enigmas = room.enigmas;
}

EscapeRoomWrapper* EscapeRoomWrapper::clone() const{
    return new EscapeRoomWrapper(*this);
}

EscapeRoomWrapper& EscapeRoomWrapper::operator=(const EscapeRoomWrapper& room){
    if (*this == room){
        return *this;
    }
    escapeRoomDestroy(this->room);
    this->room = escapeRoomCopy(room.room);
    this->enigmas = room.enigmas;
    return *this;
}

int EscapeRoomWrapper::level() const{
    return getLevel(this->room);
}

void EscapeRoomWrapper::rate(const int& newRate){
    if (updateRate(this->room, newRate) == ESCAPEROOM_BAD_PARAM){
        throw EscapeRoomIllegalRateException();
    }
}

bool EscapeRoomWrapper::operator==(const EscapeRoomWrapper& room) const{
    return areEqualRooms(this->room, room.room);
}

bool EscapeRoomWrapper::operator!=(const EscapeRoomWrapper& room) const{
    return !(*this == room);
}

bool EscapeRoomWrapper::operator>(const EscapeRoomWrapper& room) const{
    return isBiggerRoom(this->room, room.room);
}

bool EscapeRoomWrapper::operator<(const EscapeRoomWrapper& room) const{
    if (*this != room){
        return !(*this > room);
    }
    return false;
}

EscapeRoomWrapper::~EscapeRoomWrapper(){
    escapeRoomDestroy(this->room);
}

std::ostream& mtm::escaperoom::operator<<(std::ostream& output,
                                          const EscapeRoomWrapper& room){
    string name = room.getName();
    int time = room.getMaxTime();
    int level = room.level();
    int participants = room.getMaxParticipants();
    return output  << name << " (" << time << "/" << level << "/" <<
                    participants << ")";
}

std::string EscapeRoomWrapper::getName() const{
    char* tmp_str = roomGetName(this->room);
    string name(tmp_str);
    free(tmp_str);
    return name;
}

double EscapeRoomWrapper::getRate() const{
    return roomGetRate(this->room);
}

int EscapeRoomWrapper::getMaxTime() const{
    return roomGetMaxTime(this->room);
}

int EscapeRoomWrapper::getMaxParticipants() const{
    return roomGetMaxParticipants(this->room);
}

void EscapeRoomWrapper::addEnigma(const mtm::escaperoom::Enigma& enigma){
    this->enigmas.push_back(enigma);
}

void EscapeRoomWrapper::removeEnigma(const mtm::escaperoom::Enigma &enigma){
    if (this->enigmas.size() == 0){
        throw EscapeRoomNoEnigmasException();
    }
    vector<Enigma>::iterator i = this->enigmas.begin();
    for (int j=0; j < (int)this->enigmas.size(); i++, j++){
        if (*i == enigma){
            this->enigmas.erase(i);
            return;
        }
    }
    throw EscapeRoomEnigmaNotFoundException();
}

mtm::escaperoom::Enigma EscapeRoomWrapper::getHardestEnigma(){
    if (this->enigmas.size() == 0){
        throw EscapeRoomNoEnigmasException();
    }
    Difficulty max_difficulty = this->enigmas[0].getDifficulty();
    Enigma max_enigma = this->enigmas[0];
    for (int i=0; i < (int)this->enigmas.size(); i++){
        if (this->enigmas[i].getDifficulty() > max_difficulty){
            max_enigma = this->enigmas[i];
        }
    }
    return max_enigma;
}

vector<mtm::escaperoom::Enigma>& EscapeRoomWrapper::getAllEnigmas(){
    return enigmas;
}

void EscapeRoomWrapper::addItem(const mtm::escaperoom::Enigma& enigma,
                                const string& element){
    for (int i=0; i< (int)this->enigmas.size(); i++){
        if (this->enigmas[i] == enigma){
            this->enigmas[i].addElement(element);
            return;
        }
    }
    throw EscapeRoomEnigmaNotFoundException();
}

void EscapeRoomWrapper::removeItem(const mtm::escaperoom::Enigma& enigma,
                                   const string& element){
    for (int i=0; i< (int)this->enigmas.size(); i++){
        if (this->enigmas[i] == enigma){
            try{
                this->enigmas[i].removeElement(element);
            } catch(EnigmaNoElementsException){
                throw EscapeRoomEnigmaHasNoElementsException();
            } catch(EnigmaElementNotFoundException){
                throw EscapeRoomEnigmaElementNotFoundException();
            }
            return;
        }
    }
    throw EscapeRoomEnigmaNotFoundException();
}
