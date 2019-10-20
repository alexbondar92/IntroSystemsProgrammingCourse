#ifndef LIST_H_
#define LIST_H_

#include "Exceptions.h"
#include <list>
/* ********************* Generic Doubly Linked List ****************************
 *
 *	List include Nodes that is doubly linked.
 *	every node in the linked list had a ptr to prev node, next node and data of
 *	object <T>.
 *  at the end of every List there is a "Dummy" node that indicates at the end
 *	of the list.
 *	In addition there is a Iterator class that creates at UI for the list's
 *	objects.
 *
 * List functions:
 *      List();
 *			- Constractor for the List.
 *      List(const List& list);
 *			- Copy Constractor for the List
 *			- copies the data to This.
 *      List& operator=(const List& list);
 *			- Copy assignment operator
 *			- in case the input list is This, it returns itself.
 *			- otherwise the old data from This deletes and a copy of list is created(into This).
 *      ~List();
 *			- Distructor for the List
 *      Iterator begin() const;
 *			- Getting iterator to the start of the list
 *      Iterator end() const;
 *			- Getting iterator to the end of the list(ponits to dummy node, no data node)
 *			- it doesn't points to any object in the List.
 *      void insert(const T& data, Iterator iterator);
 *			- Insert new <T> object into the List, befor the iterator's place
 *			- in case the iterator doesn't points to any object in the list
 *			- exeption is throws, ElementNotFound::ListExceptions.
 *      void insert(const T& data);
 *			- Insert new <T> object into the List, to the end(befor the dummy node)
 *      void remove(Iterator iterator);
 *			- Remove object from the List, the object witch the iterator points at
 *			- in case the list is empty, the iterator points to other list or not to 
 *			- one of the objects of the List, expetion throws, ElementNotFound::ListExceptions.
 *      Iterator find(const Predicate& predicate);
 *			- Find the first object at the List, that upholds the predicate conditions
 *			- in case there is couple of object that upholds this predicate, the
 *			- first one in the List is returns.
 *			- Predicate Object Function is needed(e.g. bool isEqual(T& i){ return (i == 99);})
 *      void sort(const Compare& compare);
 *			- Sort the List by a compare function
			- Compare Object Function is needed(e.g. bool bigger(T& i, T& j){return (i > j);})
 *      int getSize() const;
 *			- Getting the size of the List, number of objects in the List
 *      bool operator==(const List& list) const;
 *			- Equal operator, returns true/false if the lists is equal or not
 *		bool operator!=(const List& list) const
 *			- Not Equal operator, return the opossit from Equal operator
 *
 *
 * Iterator functions:
 *		~Iterator()
 *			- Distructor for Iterator
 *		Iterator& operator++();
 *			- Move(Inc) the iterator to the next object in the List, (++I)
 *		Iterator operator++(int);
 *			- Move(Inc) the iterator to the next object in the List, (I++)
 *		Iterator& operator--();
 *			- Move(Dec) the iterator to the previous object in the List, (--I)
 *		Iterator operator--(int);
 *			- Move(Dec) the iterator to the previous object in the List, (I--)
 *		T& operator*() const;
 *			- Return the object(Data) that the iterator points at, (*I)
 *			- in case the iterator points to the end of the List(dummy node)
 *			- exeption is throws, ListExceptions::ElementNotFound.
 *		bool operator==(const Iterator& iterator) const;
 *			- Equal operator, returns true/false if the iterator points to the same object
 *		bool operator!=(const Iterator& iterator) const;
 *			- Not Equal operator, return the opossit from Equal operator
 *		Iterator(const Iterator&) = default;
 *			- Copy constructor, the default function
 *		Iterator& operator=(const Iterator&) = default;
 *			- Copy assignment operator
 *
 *
 *	List's fields:
 *		- size, the number of objects in the List
 *		- head, prt to the start of the List
 *		- tail, ptr to the end of the List
 *
 *	the Iterator's fields:
 *		- node, ptr to the current node witch the iterator points at
 *
 *	the Node's fields:
 *		- data, the data witch in the current node
 *		- prev, the previous node
 *		- next, the next node
 **/

template<class T>
class List {
    
    class Node{
    private:
        // =========================== Node fields =============================
        Node* prev;
        T* data;
        Node* next;
        bool dummy;
        
        friend class List<T>;
        friend class Iterator;
        
        Node(){
            this->data = nullptr;
            this->prev = nullptr;
            this->next = nullptr;
            this->dummy = true;
        }
        
        Node(N ){
            this->data = new T(data);
            this->prev = prev;
            this->next = next;
            this->dummy = false;
        }
        
        Node(const Node& node){
            this->prev = node.prevNode();
			this->next = node.nextNode();
			if (node.getData() == nullptr){
				this->data = nullptr;
			} else{
				this->data = new T(*node.getData());
			}
            this->dummy = node.dummy;
        }
        
        Node& operator=(const Node& node){
            if (&node == this){
                return *this;
            }
            this->prev = node.prevNode();
            this->next = node.nextNode();
            delete this->data;
            this->data = new T(*node.getData());
            this->dummy = node.dummy;
            return *this;
        }

        ~Node(){
            delete this->data;
        }
        
        T* getData() const{
             return this->data;
        }
        
        Node* nextNode() const{
            return this->next;
        }
        
        void setNext(Node* next){
            this->next = next;
        }
        
        Node* prevNode() const{
            return this->prev;
        }
        
        void setPrev(Node* prev){
            this->prev = prev;
        }
    };
    
public:
    class Iterator{
        // ========================= Iterator fields ===========================
        Node* node;
        friend class List;
        
        Iterator(Node* current_node){
            this->node = current_node;
        }
        
    public:
        ~Iterator() = default;
        
        Iterator& operator++(){
            if (this->node != nullptr){
                this->node = this->node->nextNode();
            }
            return *this;
        }
        
        Iterator operator++(int){
            Iterator result = *this;
            ++*this;
            return result;
        }
        
        Iterator& operator--(){
			if (this->node != nullptr){
				this->node = this->node->prevNode();
			}
//            this->node = this->node->prevNode();
            return *this;
        }
        
        Iterator operator--(int){
            Iterator result = *this;
            --*this;
            return result;
        }
        
        T& operator*() const{
            if (this->node->dummy == true){
                throw mtm::ListExceptions::ElementNotFound();
            }
            return *(this->node->getData());
        }
        
        bool operator==(const Iterator& iterator) const{
            if (this->node->nextNode() == iterator.node->nextNode() &&
                this->node->prevNode() == iterator.node->prevNode() &&
                this->node == iterator.node){
                return true;
            }
            return false;
        }

        bool operator!=(const Iterator& iterator) const{
            return !(*this == iterator);
        }
        
        bool operator<=(const Iterator& iterator) const = delete;
        bool operator>=(const Iterator& iterator) const = delete;
        bool operator<(const Iterator& iterator) const = delete;
        bool operator>(const Iterator& iterator) const = delete;
        
        Iterator(const Iterator&) = default;
        Iterator& operator=(const Iterator&) = default;
    };
    
    // =========================== List fields =================================
    Node* head;
    Node* tail;
    int size;
    
    List(){
        this->size = 0;
        Node* dummy = new Node();
        dummy->prev = nullptr;
        this->head = dummy;
        this->tail = dummy;
    }
    
    List(const List& list){
        this->size = 0;
        Node* dummy = new Node();
        this->head = dummy;
        this->tail = dummy;
        if (list.getSize() != 0){
            for(Iterator i=list.begin(); i != list.end(); i++){
                this->insert(*i);
            }
        }
    }
    
    List& operator=(const List& list){
        if (this == &list){
            return *this;
        }
        Node* dummy = new Node(*list.end().node);
        if (this->getSize() != 0){
			while(this->begin() != this->end()){
				this->remove(this->begin());
			}
        }
        delete this->head;
        this->head = dummy;
        this->tail = dummy;
        if (list.size != 0){
            for(Iterator i=list.begin(); i != list.end(); i++){
                this->insert(*i);
            }
        }
        return *this;
    }
    
    ~List(){
        if (this->getSize() != 0){
            while(this->head != this->tail){
                Iterator i = this->begin();
                this->remove(i);
                i = this->begin();
            }
        }
        delete this->head;
    }
    
    Iterator begin() const{
        Iterator begin(this->head);
        return begin;
    }
    
    Iterator end() const{
        Iterator end(this->tail);
        return end;
    }
    
    void insert(const T& data, Iterator iterator){
        Iterator i = this->begin();
        if(i == iterator){
            Node* new_node = new Node(data, nullptr, i.node);
            i.node->setPrev(new_node);
            this->head = new_node;
            this->size++;
            return;
        }
        while(i != this->end()){
            if (i == iterator){
                break;
            }
            i++;
        }
        if (i == iterator){
            Node* new_node = new Node(data, i.node->prevNode(), i.node);
            i--;
            iterator.node->setPrev(new_node);
            i.node->setNext(new_node);
            this->size++;
            return;
        }
        throw mtm::ListExceptions::ElementNotFound();
    }
    
    void insert(const T& data){
        Iterator tmp = this->end();
        this->insert(data, tmp);
    }

    void remove(Iterator iterator){
        if(this->getSize() == 0 || iterator.node->dummy == true){
            throw mtm::ListExceptions::ElementNotFound();
        }
        Iterator i = this->begin();
        while(i != this->end()){
            if (i == iterator){
                break;
            }
            i++;
        }
        if (i != iterator){
            throw mtm::ListExceptions::ElementNotFound();
        }
        Iterator next = iterator;
        Iterator prev = iterator;
        next++;
        if (prev.node == this->head){
            this->head = iterator.node->next;
            this->head->prev = 0;
        } else{
            iterator.node->next->prev = iterator.node->prev;
            iterator.node->prev->next = iterator.node->next;
        }
        this->size--;
		if (iterator.node != nullptr){
			delete iterator.node;
		}
    }
    
    template<class Predicate>
    Iterator find(const Predicate& predicate){
        for(Iterator i=this->begin(); i != this->end(); i++){
            if(predicate(*i) == true){
                return i;
            }
        }
        return this->end();
    }
    
    template<class Compare>
    void sort(const Compare& compare){
        for (Iterator i=this->begin(); i != this->end(); i++){
            for (Iterator j=this->begin(); j!= this->end(); j++){
                Iterator next_j = j;
                next_j++;
                if (next_j != this->end() && compare(*j,*next_j) == false){
                    T* tmp_data = j.node->data;
                    j.node->data = next_j.node->data;
                    next_j.node->data = tmp_data;
                }
            }
        }
    }
    
    int getSize() const{
        return this->size;
    }
    
    bool operator==(const List& list) const{
        if (list.size != this->size){
            return false;
        }
        Iterator i_list = list.begin();
        for (Iterator i_this = this->begin(); i_this != this->end(); i_this++){
            if (i_list.node->dummy == false && i_this.node->dummy == false){
                if (*i_this != *i_list){
                    return false;
                }
            } else{
                if (i_list.node->dummy != i_this.node->dummy){
                    return false;
                }
            }
            i_list++;
        }
        return true;
    }
    
    bool operator!=(const List& list) const{
        return !(*this == list);
    }
};

#endif //LIST_H_
