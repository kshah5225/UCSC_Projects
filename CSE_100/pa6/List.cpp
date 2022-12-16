//-----------------------------------------------------------------------------
// List.cpp
// Implementation file for List ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<sstream>
#include<string>
#include<stdexcept>
#include<iomanip>
#include"List.h"

#define BASE 1000000000
#define BASEPWR 9

// Private Constructor --------------------------------------------------------

// Node constructor
List::Node::Node(ListElement x){
   data = x;
   next = nullptr;
   prev = nullptr;
}


// Class Constructors & Destructors -------------------------------------------

// Creates a new List in the empty state.
List::List(){
   frontDummy = new Node(-1);
   backDummy = new Node(-1);
   beforeCursor = frontDummy;
   afterCursor = backDummy;
   frontDummy->next = backDummy;//these two lines are new and idk if i shuld keeop them because they make sense but it worked without these b4
   backDummy->prev = frontDummy;
   pos_cursor = 0;
   num_elements = 0;
}

// Copy Constructor.
List::List(const List& L){
   // make this an empty List
   frontDummy = new Node(-1);
   backDummy = new Node(-1);
   beforeCursor = frontDummy;
   beforeCursor->next = backDummy;
   afterCursor = backDummy;
   afterCursor->prev = frontDummy;
   pos_cursor = 0;
   num_elements = 0;

   // load elements of L into this List
   Node* N = L.frontDummy->next;
   while(N!=L.backDummy){
        insertBefore(N->data);
        N = N->next;
   }
}

// Destructor
List::~List(){
   clear();
   delete backDummy;
   delete frontDummy;
}


// Access functions -----------------------------------------------------------

// length()
// Returns the length of this List.
int List::length() const{
    return num_elements;
}

// front()
// Returns the front element in this List.
// pre: length()>0
ListElement List::front() const{
    if(!(length()>0)){
        throw std::length_error("List: front(): empty list");
    }
    return frontDummy->next->data;
}

// back()
// Returns the back element in this List.
// pre: length()>0
ListElement List::back() const{
    if(!(length()>0)){
        throw std::length_error("List: back(): empty list");
    }
    return backDummy->prev->data;
}

// position()
// Returns the position of cursor in this List: 0 <= position() <= length().
int List::position() const{
    return pos_cursor;
}

// peekNext()
// Returns the element after the cursor.
// pre: position()<length()
ListElement List::peekNext() const{
    if(!(position()<length())){
        throw std::range_error("List: peekNext(): cursor at back");
    }
    return afterCursor->data;
}

// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
ListElement List::peekPrev() const{
    if(!(position()>0)){
        throw std::range_error("List: peekPrev(): cursor at front");
    }
    return beforeCursor->data;
}


// Manipulation procedures ----------------------------------------------------

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear(){
    while(afterCursor!=backDummy){
        eraseAfter();
    }
    while(beforeCursor!=frontDummy){
        eraseBefore();
    }
}

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront(){
    beforeCursor = frontDummy;
    afterCursor = frontDummy->next;
    pos_cursor = 0;
}

// moveBack()
// Moves cursor to position length() in this List.
void List::moveBack(){
    afterCursor = backDummy;
    beforeCursor = backDummy->prev;
    pos_cursor = num_elements;
}

// moveNext()
// Advances cursor to next higher position. Returns the List element that
// was passed over. 
// pre: position()<length() 
ListElement List::moveNext(){
    if(!(position()<length())){
        throw std::range_error("List: moveNext(): cursor at back");
    }
    beforeCursor = afterCursor;
    afterCursor = beforeCursor->next;
    pos_cursor++;
    return beforeCursor->data;
}

// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over. 
// pre: position()>0
ListElement List::movePrev(){
    if(!(position()>0)){
        throw std::range_error("List: movePrev(): cursor at front");
    }
    afterCursor = beforeCursor;
    beforeCursor = afterCursor->prev;
    pos_cursor--;
    return afterCursor->data;
}

// insertAfter()
// Inserts x after cursor.
void List::insertAfter(ListElement x){
    Node* N = new Node(x);
    N->next = afterCursor;
    N->prev = beforeCursor;
    afterCursor->prev = N;
    afterCursor = N;
    beforeCursor->next = N;
    num_elements++;
}

// insertBefore()
// Inserts x before cursor.
void List::insertBefore(ListElement x){
    Node* N = new Node(x);
    N->next = afterCursor;
    N->prev = beforeCursor;
    beforeCursor->next = N;
    beforeCursor = N;
    afterCursor->prev = N;
    num_elements++;
    pos_cursor++;
}

// setAfter()
// Overwrites the List element after the cursor with x.
// pre: position()<length()
void List::setAfter(ListElement x){
    if(!(position()<length())){
        throw std::range_error("List: setAfter(): cursor at back");
    }
    afterCursor->data = x;
}

// setBefore()
// Overwrites the List element before the cursor with x.
// pre: position()>0
void List::setBefore(ListElement x){
    if(!(position()>0)){
        throw std::range_error("List: setBefore(): cursor at front");
    }
    beforeCursor->data = x;
}

// eraseAfter()
// Deletes element after cursor.
// pre: position()<length()
void List::eraseAfter(){
    if(!(position()<length())){
        throw std::range_error("List: eraseAfter(): cursor at back");
    }
    Node* N = afterCursor;
    N->next->prev = N->prev;
    N->prev->next = N->next;
    num_elements--;
    afterCursor = N->next;
    delete N;
}

// eraseBefore()
// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore(){
    if(!(position()>0)){
        throw std::range_error("List: eraseBefore(): cursor at front");
    }
    Node* N = beforeCursor;
    N->next->prev = N->prev;
    N->prev->next = N->next;
    num_elements--;
    pos_cursor--;
    beforeCursor = N->prev;
    delete N;
}


// Other Functions ---------------------------------------------------------

// findNext()
// Starting from the current cursor position, performs a linear search (in 
// the direction front-to-back) for the first occurrence of element x. If x
// is found, places the cursor immediately after the found element, then 
// returns the final cursor position. If x is not found, places the cursor 
// at position length(), and returns -1. 
int List::findNext(ListElement x){
    while(moveNext()!=x){
        if(afterCursor == backDummy){
            return -1;
        }
    }
    return pos_cursor;
}

// findPrev()
// Starting from the current cursor position, performs a linear search (in 
// the direction back-to-front) for the first occurrence of element x. If x
// is found, places the cursor immediately before the found element, then
// returns the final cursor position. If x is not found, places the cursor 
// at position 0, and returns -1. 
int List::findPrev(ListElement x){
    //std::cout << "startingpos: " << pos_cursor << std::endl;
    while(movePrev()!=x){
    //std::cout << "pos: " << pos_cursor << std::endl;
        if(beforeCursor == frontDummy){
            return -1;
        }
    }
    //std::cout << "endpos: " << pos_cursor << std::endl;

    return pos_cursor;
}

// cleanup()
// Removes any repeated elements in this List, leaving only unique elements.
// The order of the remaining elements is obtained by retaining the frontmost 
// occurrance of each element, and removing all other occurances. The cursor 
// is not moved with respect to the retained elements, i.e. it lies between 
// the same two retained elements that it did before cleanup() was called.
void List::cleanup(){
    Node* Cursor = frontDummy->next;
    ListElement exists[num_elements+1] = {-2};
    for (int i = 0; i < num_elements+1; i++) {
        exists[i]=-2;
    }
    int written2array = 0;
    while(backDummy!=Cursor){
        for (int i = 0; i < num_elements+1; i++) {
        //std::cout << exists[i] << ' ';
        }
        //std::cout << "searching for " << Cursor->data << " last found " << exists[written2array] << std::endl;
        bool found = false;
        for(int i=0;exists[i]!=-2;i++){
            //std::cout << "does " << exists[i] << " == " << Cursor->data << std::endl;
            if(exists[i]==Cursor->data){
                found = true;
                break;
            }
        }
        if(found){//use std::findinrange Help ????
            //std::cout << "found!" << std::endl;
            Node* DeleteCursor = Cursor;
            Cursor = Cursor->next;
            DeleteCursor->prev->next = DeleteCursor->next;
            DeleteCursor->next->prev = DeleteCursor->prev;
            num_elements--;
            if (DeleteCursor == beforeCursor){
                beforeCursor = DeleteCursor->prev;
            }
            if (DeleteCursor == afterCursor){
                afterCursor = DeleteCursor->next;
            }
            delete DeleteCursor;
        }else{
            //std::cout << "not found!" << std::endl;
            exists[written2array] = Cursor->data;
            written2array++;
            Cursor = Cursor->next;
        }
    }
    Cursor = frontDummy;
    //Cursor = Cursor->next;
    //std::cout <<"dskfjglkjdfg"<<std::endl;
    pos_cursor= 0;
    while(Cursor->data!=this->beforeCursor->data){
        Cursor = Cursor->next;
        pos_cursor++;
    }
}

// concat()
// Returns a new List consisting of the elements of this List, followed by
// the elements of  The cursor in the returned List will be at postion 0.
List List::concat(const List& L) const{
    List A;
    Node* CursorR = this->frontDummy->next;
    Node* CursorL = L.frontDummy->next;
    while(CursorR!=this->backDummy){
        A.insertBefore(CursorR->data);
        CursorR = CursorR->next;
    }
    while(CursorL!=L.backDummy){
        A.insertBefore(CursorL->data);
        CursorL = CursorL->next;
    }
    A.moveFront();
    return A;
}

// to_string()
// Returns a string representation of this List consisting of a comma 
// separated sequence of elements, surrounded by parentheses.
std::string List::to_string() const{//?add empty list case
    if(frontDummy->next==backDummy){
    return "0";
    }
    std::ostringstream os;
    //os << "(";
    Node* Cursor = frontDummy;
    Cursor = Cursor->next;
    os << Cursor->data;
    while(backDummy!=Cursor->next) {
        Cursor = Cursor->next;
        //os << ", ";
        os << std::setw(BASEPWR) << std::setfill('0') << Cursor->data;
    }
    //os << ")";
    std::string str(os.str());
    return str;
}

// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List& R) const{
    if(this->length() != R.length()){
        return false;
    }
    Node* CursorL = this->frontDummy;
    Node* CursorR = R.frontDummy;
    CursorL = CursorL->next;
    CursorR = CursorR->next;
    while(CursorL != backDummy){
        if(CursorL->data != CursorR->data){
            return false;
        }
        CursorL = CursorL->next;
        CursorR = CursorR->next;
    }
    return true;
}

/*void shuffle(List& D){
    Node* F = D.frontDummy;
    Node* S = D.frontDummy;
    bool Sturn = true;
    F = F->next;
    for(int i = 0;i>length()/2;i++){
        S = S->next;
    }
    Node* E = S;
    D.moveFront;
    while((F!=E)||(S!=D.backDummy)){
        if(Sturn){
            insertBefore(S->data);
            S = S->next;
            Sturn = false;
        }else{
            insertBefore(F->data);
            F = F->next;
            Sturn = true;
        }
    }
    cleanup();
}*/

// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of L into stream.
std::ostream& operator<<( std::ostream& stream, const List& L ){
    return stream << L.List::to_string();
}

// operator==()
// Returns true if and only if A is the same integer sequence as B. The 
// cursors in both Lists are unchanged.
bool operator==( const List& A, const List& B ){
    return A.List::equals(B);
}

// operator=()
// Overwrites the state of this List with state of 
List& List::operator=( const List& L ){
    //std::cout << "sdfgdsf" << std::endl;
    if(this != &L){ // not self assignment
      // make a copy of L
      List temp = L;

      // then swap the copy's fields with fields of this
      std::swap(frontDummy, temp.frontDummy);
      std::swap(backDummy, temp.backDummy);
      std::swap(beforeCursor, temp.beforeCursor);
      std::swap(afterCursor, temp.afterCursor);
      std::swap(pos_cursor, temp.pos_cursor);
      std::swap(num_elements, temp.num_elements);
   }

   // return this with the new data installed
   return *this;
}