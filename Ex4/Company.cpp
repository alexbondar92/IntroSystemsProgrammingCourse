#include <assert.h>
#include "Company.h"
#include "Exceptions.h"
#include "ScaryRoom.h"
#include "KidsRoom.h"
#include "Enigma.h"

using std::set;
using namespace mtm::escaperoom;
using mtm::MtmException;

Company::Company(string name, string phoneNumber){
    this->name = name;
    this->phoneNumber = phoneNumber;
    this->rooms = set<EscapeRoomWrapper*>();
}

Company::Company(const Company& company){
    this->name = company.name;
    this->phoneNumber = company.phoneNumber;
    this->rooms = set<EscapeRoomWrapper*>();
    
    set<EscapeRoomWrapper*>::iterator i = company.rooms.begin();
    for(int j = 0; j < (int)company.rooms.size(); j++, i++){
        EscapeRoomWrapper* tmp = (**i).clone();
        this->rooms.insert(tmp);
    }
}

Company& Company::operator=(const Company& company){
    this->name = company.name;
    this->phoneNumber = phoneNumber;
    
    set<EscapeRoomWrapper*>::iterator i = company.rooms.begin();
    for(int j=0; j < (int)company.rooms.size(); j++,i++){
        EscapeRoomWrapper* tmp = (**i).clone();
        this->rooms.insert(tmp);
    }
    return *this;
}

void Company::createRoom(char* name, const int& escapeTime, const int& level, const int& maxParticipants){
    EscapeRoomWrapper* tmp_room;
    try{
        tmp_room = new EscapeRoomWrapper(name, escapeTime, level, maxParticipants);
    } catch(EscapeRoomMemoryProblemException){
        delete tmp_room;
        throw CompanyMemoryProblemException();
    }
    this->rooms.insert(tmp_room);
}

void Company::createScaryRoom(char* name, const int& escapeTime, const int& level,
                     const int& maxParticipants, const int& ageLimit, const int& numOfScaryEnigmas){
    ScaryRoom* tmp_room = nullptr;
    try{
        tmp_room = new ScaryRoom(name, escapeTime, level, maxParticipants, ageLimit, numOfScaryEnigmas);
    }catch (EscapeRoomMemoryProblemException){
        delete tmp_room;
        throw CompanyMemoryProblemException();
    }
    this->rooms.insert(tmp_room);
}

void Company::createKidsRoom(char* name, const int& escapeTime, const int& level,
                    const int& maxParticipants, const int& ageLimit){
    KidsRoom* tmp_room = nullptr;
    try{
        tmp_room = new KidsRoom(name, escapeTime, level, maxParticipants, ageLimit);
    }catch (EscapeRoomMemoryProblemException){
        delete tmp_room;
        throw CompanyMemoryProblemException();
    }
    this->rooms.insert(tmp_room);
}

set<EscapeRoomWrapper*> Company::getAllRooms() const{
    return this->rooms;                 // ================================== get a copy of rooms....
}

void Company::removeRoom(const EscapeRoomWrapper& room){
    set<EscapeRoomWrapper*>::iterator i = this->rooms.begin();
    for(; i != this->rooms.end(); i++){
        if(*(*i) == room){
            delete (*i);
            this->rooms.erase(i);
            return;
        }
    }
    throw CompanyRoomNotFoundException();
}

void Company::addEnigma(const EscapeRoomWrapper& room, const Enigma& enigma){
    set<EscapeRoomWrapper*>::iterator i = this->rooms.begin();
    for(; i != this->rooms.end(); i++){
        if(*(*i) == room){
            (*i)->addEnigma(enigma);
            return;
        }
    }
    throw CompanyRoomNotFoundException();
}

void Company::removeEnigma(const EscapeRoomWrapper& room, const Enigma& enigma){
    set<EscapeRoomWrapper*>::iterator i = this->rooms.begin();
    for(; i != this->rooms.end(); i++){
        if(*(*i) == room){
            try{
                (**i).removeEnigma(enigma);
            } catch(EscapeRoomNoEnigmasException){
                throw CompanyRoomHasNoEnigmasException();
            } catch(EscapeRoomEnigmaNotFoundException){
                throw CompanyRoomEnigmaNotFoundException();
            }
            return;
        }
    }
    throw CompanyRoomNotFoundException();
}

void Company::addItem(const EscapeRoomWrapper& room, const Enigma& enigma, const string& element){
    set<EscapeRoomWrapper*>::iterator i = this->rooms.begin();
    for(; i != this->rooms.end(); i++){
        if(**i == room){
            try{
                (**i).addItem(enigma, element);
            } catch(EscapeRoomEnigmaNotFoundException){
                throw CompanyRoomEnigmaNotFoundException();
            }
            return;
        }
    }
    throw CompanyRoomNotFoundException();
}

void Company::removeItem(const EscapeRoomWrapper& room, const Enigma& enigma, const string& element){
    set<EscapeRoomWrapper*>::iterator i = this->rooms.begin();
    for(; i != this->rooms.end(); i++){
        if((**i) == room){
            try {
                (**i).removeItem(enigma, element);
            } catch (EscapeRoomEnigmaHasNoElementsException) {
                throw CompanyRoomEnigmaHasNoElementsException();
            } catch(EscapeRoomEnigmaElementNotFoundException){
                throw CompanyRoomEnigmaElementNotFoundException();
            } catch(EscapeRoomEnigmaNotFoundException){
                throw CompanyRoomEnigmaNotFoundException();
            }
            return;
        }
    }
    throw CompanyRoomNotFoundException();
}

set<EscapeRoomWrapper*> Company::getAllRoomsByType(RoomType type) const{
    set<EscapeRoomWrapper*> new_set;
    set<EscapeRoomWrapper*>::iterator i = this->rooms.begin();
    for(; i != this->rooms.end(); i++){
        if (dynamic_cast<ScaryRoom*>(*i) != nullptr){
            if ( type == SCARY_ROOM){
                new_set.insert(*i);
            }
        } else if (dynamic_cast<KidsRoom*>(*i) != nullptr){
            if (type == KIDS_ROOM){
                new_set.insert(*i);
            }
        } else if (dynamic_cast<EscapeRoomWrapper*>(*i) != nullptr){
            if (type == BASE_ROOM){
                new_set.insert(*i);
            }
        }
    }
    return new_set;
}

EscapeRoomWrapper* Company::getRoomByName(const string& name) const{
    set<EscapeRoomWrapper*>::iterator i = this->rooms.begin();
    for(; i != this->rooms.end(); i++){
        if ((*(*i)).getName() == name){
            return *i;
        }
    }
    throw CompanyRoomNotFoundException();
}

std::ostream& mtm::escaperoom::operator<<(std::ostream& output, const Company& company){
    using std::cout;
    using std::endl;
    output << company.getName() << " : " << company.getPhone() << endl;
    set<EscapeRoomWrapper*> rooms = company.getAllRooms();
    for (set<EscapeRoomWrapper*>::iterator i = rooms.begin(); i != rooms.end(); i++){
        if (dynamic_cast<ScaryRoom*>(*i) != nullptr){
//            ScaryRoom* tmp_room = dynamic_cast<ScaryRoom*>(*i);
            output << *dynamic_cast<ScaryRoom*>(*i) << endl;
        } else if (dynamic_cast<KidsRoom*>(*i) != nullptr){
//            KidsRoom* tmp_room = dynamic_cast<KidsRoom*>(*i);
            output << *dynamic_cast<KidsRoom*>(*i) << endl;
        } else if (dynamic_cast<EscapeRoomWrapper*>(*i) != nullptr){
//            EscapeRoomWrapper* tmp_room = dynamic_cast<EscapeRoomWrapper*>(*i);
            output << *dynamic_cast<EscapeRoomWrapper*>(*i) << endl;
        }
    }
    
    return output;
}

string Company::getName() const{
    return this->name;
}

string Company::getPhone() const{
    return this->phoneNumber;
}

Company::~Company(){
    set<EscapeRoomWrapper*>::iterator i = this->rooms.begin();
    while (i != this->rooms.end()){
        EscapeRoomWrapper* tmp = *i;
        this->rooms.erase(*i);
        delete tmp;
        i = this->rooms.begin();
    }
}
