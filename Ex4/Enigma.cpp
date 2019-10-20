#include <stdio.h>
#include "Enigma.h"
#include "Exceptions.h"
#include <assert.h>

using mtm::MtmException;
using mtm::escaperoom::Enigma;

Enigma::Enigma(const std::string& name, const Difficulty& difficulty,
       const int& numOfElements, const set<string>& elements){
    if((int)elements.size() != numOfElements){
        throw EnigmaIllegalSizeParamException();
    }
    this->name = name;
    this->difficulty = difficulty;
    this->elements = elements;
}

void Enigma::addElement(const string& element){
    this->elements.insert(element);
}

void Enigma::removeElement(const string& element){
    if (this->NumOfElements() == 0){
        assert(this->elements.size() == 0);
        throw EnigmaNoElementsException();
    }
    assert(this->elements.size() != 0);
    
    set<string>::iterator i = this->elements.begin();
    for (; i != this->elements.end(); i++){
        if (*i == element){
            this->elements.erase(i);
            return;
        }
    }
    throw EnigmaElementNotFoundException();
}

Enigma::Enigma(const std::string& name, const Difficulty& difficulty) :
                                name(name),
                                difficulty(difficulty){
    this->elements = set<string>();
}

bool Enigma::operator==(const Enigma& enigma) const{
    if (this->difficulty == enigma.getDifficulty() &&
        this->name == enigma.getName()){
        return true;
    }
    return false;
}

bool Enigma::operator!=(const Enigma& enigma) const{
    return !(*this == enigma);
}

bool Enigma::operator<(const Enigma& enigma) const{
    if (this->difficulty < enigma.getDifficulty()){
        return true;
    }
    return false;
}

bool Enigma::operator>(const Enigma& enigma) const{
    if (this->difficulty > enigma.getDifficulty()){
        return true;
    }
    return false;
}

bool Enigma::areEqualyComplex(const Enigma& enigma) const{
    return this->getDifficulty() == enigma.getDifficulty() &&
            this->NumOfElements() == enigma.NumOfElements();
}

mtm::escaperoom::Difficulty Enigma::getDifficulty() const{
    return this->difficulty;
}

string Enigma::getName() const{
    return this->name;
}

std::ostream& mtm::escaperoom::operator<<(std::ostream& output,
                                          const Enigma& enigma){
    return output << enigma.getName() << " (" << enigma.getDifficulty()
    << ") " << enigma.NumOfElements();
}


int Enigma::NumOfElements() const{
    return (int)this->elements.size();
}
