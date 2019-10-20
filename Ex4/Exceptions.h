#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>

namespace mtm {

    class MtmException {};

    namespace escaperoom {

        class EscapeRoomException : public MtmException {};
        class EscapeRoomNoEnigmasException : public EscapeRoomException {};
        class EscapeRoomEnigmaNotFoundException : public EscapeRoomException {};
        class EscapeRoomIllegalRateException : public EscapeRoomException {};
        class EscapeRoomMemoryProblemException : public EscapeRoomException{};
        class EscapeRoomEnigmaHasNoElementsException : public EscapeRoomException {};
        class EscapeRoomEnigmaElementNotFoundException : public EscapeRoomException{};

        class ScaryRoomException : public EscapeRoomException{};
        class ScaryRoomIllegalAgeLimit: public ScaryRoomException{};

        class KidsRoomException : public EscapeRoomException{};
        class KidsRoomIllegalAgeLimit: public KidsRoomException{};

        class EnigmaException : public MtmException {};
        class EnigmaIllegalSizeParamException : public EnigmaException{};
        class EnigmaNoElementsException : public EnigmaException{};
        class EnigmaElementNotFoundException : public EnigmaException{};

        class CompanyException : public MtmException {};
        class CompanyRoomNotFoundException : public CompanyException{};
        class CompanyRoomEnigmaNotFoundException : public CompanyException{};
        class CompanyRoomHasNoEnigmasException : public CompanyException{};
        class CompanyRoomEnigmaElementNotFoundException : public CompanyException{};
        class CompanyRoomEnigmaHasNoElementsException : public CompanyException{};
        class CompanyMemoryProblemException : public CompanyException{};
    }  //  namespace escaperoom

    namespace ListExceptions {
        class ElementNotFound : public std::runtime_error {
        public:
            ElementNotFound() : std::runtime_error("Element not found") {}
        };

    }
}  //  namespace mtm

#endif  // EXCEPTIONS_H
