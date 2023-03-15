#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;


template <typename T>
class LinkedList {

public:

    struct Node {
        T data;
        Node* next;
        Node* prev;

    };

    unsigned int nodeCount = 0;
    Node* head = nullptr;
    Node* tail = nullptr;

    void AddHead(const T& data);
    void AddTail(const T& data);
    void AddNodesHead(const T* data, unsigned int count);
    void AddNodesTail(const T* data, unsigned int count);
    void InsertAfter(Node* node, const T& data);
    void InsertBefore(Node* node, const T& data);
    void InsertAt(const T& data, unsigned int index);
    //Inserts info in various ways

    void PrintForward() const;
    void PrintReverse() const;
    //Prints information (obviously)

    unsigned int NodeCount() const;
    Node* Head();
    const Node* Head() const;
    Node* Tail();
    const Node* Tail() const;
    Node* GetNode(unsigned int index);
    const Node* GetNode(unsigned int index) const;

    Node* Find(const T& data);
    const Node* Find(const T& data) const;
    void FindAll(vector<Node*>& outData, const T& value) const;
    //Accessor

    bool RemoveHead();
    bool RemoveTail();
    unsigned int Remove(const T& data);
    bool RemoveAt(unsigned int index);
    void Clear();

    const T& operator[](unsigned int index) const;
    T& operator[](unsigned int index);
    LinkedList<T>& operator=(const LinkedList<T>& rhs);
    //Operators

    void PrintForwardRecursive(const Node* node) const;
    void PrintReverseRecursive(const Node* node) const;

    bool operator==(const LinkedList<T>& rhs) const;

    LinkedList();
    ~LinkedList();
    LinkedList(const LinkedList<T>& list);




};



template <typename T>
LinkedList<T>::LinkedList() {

    nodeCount = 0;
    head = nullptr;
    tail = nullptr;
}
//Creates a linked list



template <typename T>
void LinkedList<T>::AddHead(const T& data) {

    Node* soonToBe = new Node;
    soonToBe->data = data;
    soonToBe->next = head;
    head = soonToBe;
    /*Adds a new node to the end (new node is given data,
    current head is now prev node. Head is switched to this) */


    if (nodeCount == 0)
        tail = soonToBe;
    if (nodeCount > 0)
        head->next->prev = head;
    //Makes sure node is connected to everything else
    head->prev = nullptr;
    nodeCount++;
}


template <typename T>
void LinkedList<T>::AddTail(const T& data) {

    Node* soonToBe = new Node;
    soonToBe->data = data;
    //if (tail != nullptr)
    soonToBe->prev = tail;
    tail = soonToBe;


    /*Adds a new node to the end(new node is given data,
    current tail is now prev node. Tail is switched to this) */

    if (nodeCount == 0)
        head = soonToBe;
    if (nodeCount > 0)
        tail->prev->next = tail;

    tail->next = nullptr;
    //Makes sure node is connected to everything else
    nodeCount++;

}

template <typename T>
void LinkedList<T>::AddNodesHead(const T* data, unsigned int count) {


    for (unsigned int i = count; i > 0; i--) {

        Node* soonToBe = new Node;
        soonToBe->data = data[i - 1];
        soonToBe->next = head;
        head = soonToBe;
        nodeCount++;

        if (nodeCount == 0)
            tail = soonToBe;
        if (nodeCount > 0)
            head->next->prev = head;
    }
    //Essentially the same thing as add head, but with an array
}

template <typename T>
void LinkedList<T>::AddNodesTail(const T* data, unsigned int count) {

    for (unsigned int i = 0; i < count; i++) {

        Node* soonToBe = new Node;
        soonToBe->data = data[i];
        soonToBe->prev = tail;
        tail = soonToBe;
        nodeCount++;

        if (nodeCount == 0)
            tail = soonToBe;
        if (nodeCount > 0)
            tail->prev->next = tail;
    }

    //Essentially same functionality as add tail, but with an array

}

template <typename T>
void LinkedList<T>::InsertAfter(Node* node, const T& data) {

    Node* soonToBe = new Node;
    Node* tempPtr = node->next;

    node->next = soonToBe;
    soonToBe->prev = node;
    soonToBe->next = tempPtr;
    soonToBe->data = data;

    soonToBe->next->prev = soonToBe;

    nodeCount++;
}

template <typename T>
void LinkedList<T>::InsertBefore(Node* node, const T& data) {

    Node* soonToBe = new Node;
    soonToBe->data = data;

    Node* tempPtr = node->prev;

    node->prev = soonToBe;
    soonToBe->next = node;
    soonToBe->prev = tempPtr;
    soonToBe->prev->next = soonToBe;

    nodeCount++;

}

template <typename T>
void LinkedList<T>::InsertAt(const T& data, unsigned int index) {

    if (index > nodeCount) {
        throw out_of_range("Invalid index");
    }
    else if (index == nodeCount) {
        AddTail(data);
    }
    else if (index == 0) {
        AddHead(data);
    }
    else {
        Node* tempPtr = head;
        Node* tempPtr2;

        for (unsigned int i = 0; i < index; i++) {
            tempPtr = tempPtr->next;

        }
        
        tempPtr2 = tempPtr->prev;
    
        tempPtr->prev = new Node;
        tempPtr->prev->next = tempPtr;
        tempPtr = tempPtr->prev;
        tempPtr->data = data;
        tempPtr->prev = tempPtr2;
        if (tempPtr->prev != nullptr)
        {
            tempPtr->prev->next = tempPtr;
        }
        nodeCount++;
    }
}

template <typename T>
void LinkedList<T>::PrintForward() const {

    Node* ptr = head;

    for (unsigned int i = 0; i < nodeCount; i++) {
        cout << ptr->data << endl;
        if (ptr->next != nullptr) {
            ptr = ptr->next;
        }
        else
            break;

    }

    //Iterates through all nodes and prints
}



template <typename T>
void LinkedList<T>::PrintReverse() const {

    Node* ptr = tail;

    for (unsigned int i = 0; i < nodeCount; i++) {
        cout << ptr->data << endl;
        if (ptr->prev != nullptr) {
            ptr = ptr->prev;
        }
        else
            break;

    }
    //Iterates through all nodes in reverse and prints

}

template <typename T>
unsigned int LinkedList<T>::NodeCount() const {

    return nodeCount;
}
//Returns node count

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Head() {

    return head;
}
//Non constant head returner

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Head() const {

    return head;
}
//Constant head returner

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Tail() {

    return tail;
}
//Non constant tail returner

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Tail() const {

    return tail;
}
//Constant tail returner

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) {
    Node* tempPtr = head;

    if (index > (nodeCount - 1)) {
        throw out_of_range("Invalid index.");
    }

    for (unsigned int i = 0; i < index; i++) {

        if (tempPtr->next != nullptr)
            tempPtr = tempPtr->next;


    }
    return tempPtr;

}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) const {
    Node* tempPtr = head;

    if (index > (nodeCount - 1)) {
        throw out_of_range("Invalid index.");
    }

    for (unsigned int i = 0; i < index; i++) {

        if (tempPtr->next != nullptr)
            tempPtr = tempPtr->next;


    }
    return tempPtr;

}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Find(const T& data) {

    Node* tempptr = head;

    for (unsigned int i = 0; i < nodeCount; i++) {

        if (tempptr->data == data)
            return tempptr;
        else {
            if (tempptr->next != nullptr)
                tempptr = tempptr->next;
        }
    }
    return nullptr;

}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Find(const T& data) const {

    Node* tempptr = head;

    for (unsigned int i = 0; i < nodeCount; i++) {

        if (tempptr->data == data)
            return tempptr;
        else {
            if (tempptr->next != nullptr)
                tempptr = tempptr->next;
        }
    }
    return nullptr;

}

template <typename T>
void LinkedList<T>::FindAll(vector<Node*>& outData, const T& value) const {

    Node* tempPtr = head;
    int vectorCounter = 0;

    for (unsigned int i = 0; i < nodeCount; i++) {

        if (tempPtr->data == value) {
            outData.push_back(tempPtr);
            vectorCounter++;
        }
        tempPtr = tempPtr->next;
    }
    if (vectorCounter == 0)
        outData.push_back(nullptr);


}

template <typename T>
LinkedList<T>& LinkedList<T>::operator = (const LinkedList<T>& rhs) {

    Node* tempPtr = head;
    Node* tempPtr2 = rhs.head;

    for (unsigned int i = 0; i < rhs.nodeCount; i++) {
        if (tempPtr != nullptr) {
            tempPtr->data = tempPtr2->data;
            tempPtr = tempPtr->next;
            tempPtr2 = tempPtr2->next;
        }
        else {
            AddTail(tempPtr2->data);
            tempPtr2 = tempPtr2->next;

        }
    }

    return *this;
}

template <typename T>
T& LinkedList<T>::operator[](unsigned int index) {

    Node* tempPtr = head;

    if (index > (nodeCount - 1)) {
        throw out_of_range("Invalid index.");
    }

    for (unsigned int i = 0; i < index; i++) {

        if (tempPtr->next != nullptr)
            tempPtr = tempPtr->next;


    }
    return tempPtr->data;

}
//Returns pointer for node at given index--Non Constant version

template <typename T>
void LinkedList<T>::PrintForwardRecursive(const Node* node) const {

 

    if (node->next == nullptr) {
        cout << node->data << endl;
    }
    else {
        cout << node->data << endl;
        PrintForwardRecursive(node->next);
    }


}

template <typename T>
void LinkedList<T>::PrintReverseRecursive(const Node* node) const {
   
   

    if (node->prev == nullptr) {
        cout << node->data << endl;
    }
    else {
        cout << node->data << endl;
        PrintReverseRecursive(node->prev);
      
    }

}

template <typename T>
bool LinkedList<T>::RemoveHead() {

    if (head == nullptr) {
        return false;
    }
    if (nodeCount == 1) {
        Node* tempPtr = head;
        delete tempPtr;
        nodeCount--;
        head = nullptr;
        return true;
    }
    Node* tempPtr = head->next;
    Node* soonToDie = head;

    delete soonToDie;
    head = tempPtr;
    head->prev = nullptr;
    nodeCount--;
    return true;
    //May NEED to change previous
}

template <typename T>
bool LinkedList<T>::RemoveTail() {

    if (tail == nullptr) {
        return false;
    }
    if (nodeCount == 1) {
        Node* tempPtr = tail;
        delete tempPtr;
        nodeCount--;
        tail = nullptr;
        return true;
    }
    Node* tempPtr = tail->prev;
    Node* soonToDie = tail;

    delete soonToDie;
    tail = tempPtr;
    tail->next = nullptr;
    nodeCount--;
    
    return true;
}

template <typename T> 
unsigned int LinkedList<T>::Remove(const T& data) {
    Node* tempPtr = head;
    Node* connector = nullptr;
    Node* soonToDie = nullptr;

    unsigned int deleteCount = 0;


    for (unsigned int i = 0; i < nodeCount; i++) {
        if (tempPtr->data == data) {
            soonToDie = tempPtr;
            if (tempPtr -> next != nullptr)
            connector = tempPtr->next;
            if (tempPtr->prev != nullptr) {
                tempPtr = tempPtr->prev;
            }
            delete soonToDie;
            tempPtr->next = connector;
            tempPtr->next->prev = tempPtr;
            deleteCount++;
        }

        tempPtr = tempPtr->next;
    }
    nodeCount = nodeCount - deleteCount;
    return deleteCount;
}

template <typename T>
bool LinkedList<T>::RemoveAt(unsigned int index) {
    Node* tempPtr = head;
    Node* soonToDie = nullptr;
    Node* connector = nullptr;

    if (index > nodeCount) {
        return false;
    }
    if (index == 0) {
        RemoveHead();
        return true;
    }
    if (index == nodeCount) {
        RemoveTail();
        return true;
    }
    else {
        for (unsigned int i = 0; i < index; i++)
        {   
            tempPtr = tempPtr->next;

        }
        connector = tempPtr->prev;
        soonToDie = tempPtr;
        tempPtr = tempPtr->next;
        delete soonToDie;
        tempPtr->prev = connector;
        tempPtr->prev->next = tempPtr;
        nodeCount--;
        return true;
    }

}

template <typename T>
void LinkedList<T>::Clear() {

    Node* ptr = head;
    Node* nextPtr;
    delete head->prev;

    for (unsigned int i = 0; i < nodeCount; i++)
    {

        if (ptr->next != nullptr) {

            nextPtr = ptr->next;
            delete ptr;
            ptr = nextPtr;

        }
        else {
            delete ptr;
            delete ptr->next;
        }

        nodeCount = 0;
    }
}

template <typename T>
const T& LinkedList<T>::operator[](unsigned int index) const {

    Node* tempPtr = head;

    if (index > (nodeCount - 1)) {
        throw out_of_range("Invalid index.");
    }

    for (unsigned int i = 0; i < index; i++) {

        if (tempPtr->next != nullptr)
            tempPtr = tempPtr->next;


    }
    return tempPtr->data;
}
//Returns pointer for node at given index--Constant version

template <typename T>
bool LinkedList<T>::operator==(const LinkedList<T>& rhs) const {

    Node* tempPtr = head;
    Node* otherPointer = rhs.head;

    if (nodeCount != rhs.nodeCount) {
        return false;
    }
    else {
        for (unsigned int i = 0; i < nodeCount; i++) {
            if (tempPtr != otherPointer)
                break;
            tempPtr = tempPtr->next;
            otherPointer = otherPointer->next;
        }

        return true;
    }

}

template <typename T>
LinkedList<T>::~LinkedList() {

    Node* ptr = head;
    Node* nextPtr;

    for (unsigned int i = 0; i < nodeCount; i++)
    {

        if (ptr->next != nullptr) {

            nextPtr = ptr->next;
            delete ptr;
            ptr = nextPtr;

        }
        else {
            delete ptr;
        }


    }
    //Iterates through the entire list from start, deleting every pointer/node
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& list) {


    Node* tempPtr = list.head;

    for (unsigned int i = 0; i < list.nodeCount; i++) {

        AddTail(tempPtr->data);
        tempPtr = tempPtr->next;
    }

}
