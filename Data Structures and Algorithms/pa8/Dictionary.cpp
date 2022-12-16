//-----------------------------------------------------------------------------
// Dictionary.cpp
// Header file for Dictionary ADT based on a Binary Search Tree. Includes a
// built in iterator called current that can perform a smallest-to-largest
// (forward) or a largest-to-smallest (reverse) iteration over all keys.
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<sstream>
#include"Dictionary.h"

#define RED 1
#define BLACK 0

// Private Constructor --------------------------------------------------------

// Node constructor
Dictionary::Node::Node(keyType x,valType y){
    key = x;
    val = y;
    parent = nullptr;
    left = nullptr;
    right = nullptr;
    color = -1;
}


// Class Constructors & Destructors -------------------------------------------

// Creates a new Dictionary in the empty state.
Dictionary::Dictionary(){
   nil = new Node("NIL",-1);
   // nil->left = nil;
   // nil->right = nil;
   // nil->parent = nil;
   root = nil;
   current = nil;
   num_pairs = 0;
}

// Copy Constructor.
Dictionary::Dictionary(const Dictionary& L){
   // make this an empty Dictionary
   nil = new Node("NIL",-1);
   // nil->left = nil;
   // nil->right = nil;
   // nil->parent = nil;
   root = nil;
   current = nil;
   num_pairs = 0;

   // load elements of L into this Dictionary
   preOrderCopy(L.root, L.nil);
}

// Destructor
Dictionary::~Dictionary(){
   clear();
   delete nil;
}

// Helper Functions (Optional) ---------------------------------------------

// inOrderString()
// Appends a string representation of the tree rooted at R to string s. The
// string appended consists of: "key : value \n" for each key-value pair in
// tree R, arranged in order by keys.
void Dictionary::inOrderString(std::string& s, Node* R) const{
   if(R != nil){
      inOrderString(s,R->left);
      s.append(R->key);
      s.append(" : ");
      s.append(std::to_string(R->val));
      s.append("\n");
      /*s+=R->key;
      s+=" : ";
      s+=std::to_string(R->val);
      s+='\n';*/
      inOrderString(s,R->right);
   }
}

// preOrderString()
// Appends a string representation of the tree rooted at R to s. The appended
// string consists of keys only, separated by "\n", with the order determined
// by a pre-order tree walk.
void Dictionary::preOrderString(std::string& s, Node* R) const{
   if(R != nil){
      s.append(R->key);
      s.append("\n");
      preOrderString(s,R->left);
      preOrderString(s,R->right);
   }
}

// preOrderCopy()
// Recursively inserts a deep copy of the subtree rooted at R into this 
// Dictionary. Recursion terminates at N.
void Dictionary::preOrderCopy(Node* R, Node* N){
   if (R != N){
      setValue(R->key,R->val);
      preOrderCopy(R->left,N);
      preOrderCopy(R->right,N);
   }
}

// postOrderDelete()
// Deletes all Nodes in the subtree rooted at R, sets R to nil.
void Dictionary::postOrderDelete(Node* R){
   //op
   // left -> right -> delete
   if(R!=nil){
      postOrderDelete(R->left);
      postOrderDelete(R->right);
      delete R;
   }
}

// search()
// Searches the subtree rooted at R for a Node with key==k. Returns
// the address of the Node if it exists, returns nil otherwise.
Dictionary::Node* Dictionary::search(Node* R, keyType k) const{
   if(R == nil || R->key == k){
      return R;
   }else if((R->left==nil) && (R->right==nil)){
      return nil;
   }else if(k < R->key){
      return search(R->left, k);
   }
   else{
      return search(R->right, k);
   }
}

// findMin()
// If the subtree rooted at R is not empty, returns a pointer to the 
// leftmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMin(Node* R){
   while(R->left != nil){
      R = R->left;
   }
   return R;
}

// findMax()
// If the subtree rooted at R is not empty, returns a pointer to the 
// rightmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMax(Node* R){
   while(R->right != nil){
      R = R->right;
   }
   return R;
}

   // RBT Helper Functions (Optional) -----------------------------------------
   
   // LeftRotate()
   void Dictionary::LeftRotate(Node* N){
      Node* y = N->right;

      // turn y's left subtree into x's right subtree
      N->right = y->left; 
      if (y->left != nil){     // not necessary if using sentinal nil node
         y->left->parent = N;
      }
      // link y's parent to N
      y->parent = N->parent;
      if (N->parent == nil){
         root = y;
      }
      else if (N == N->parent->left){
         N->parent->left = y;
      }
      else{
         N->parent->right = y;
      }
      // put x on y's left
      y->left = N;
      N->parent = y;
   }

   // RightRotate()
   void Dictionary::RightRotate(Node* N){
      // set y
      Node* y = N->left;
      
      // turn y's right subtree into N's left subtree
      N->left = y->right;
      if (y->right != nil){  // not necessary if using sentinal nil node
         y->right->parent = N;
      }
      // link y's parent to N
      y->parent = N->parent;
      if (N->parent == nil){
         root = y;
      }
      else if (N == N->parent->right){
         N->parent->right = y;
      }
      else{
         N->parent->left = y;
      }
      // put N on y's right
      y->right = N;
      N->parent = y;
   }

   // RB_InsertFixUP()
   void Dictionary::RB_InsertFixUp(Node* N){
      Node* y;
      while (N->parent->color == RED){
         if (N->parent == N->parent->parent->left){
            y = N->parent->parent->right;
            if (y->color == RED){
               N->parent->color = BLACK;              // case 1
               y->color = BLACK;                     // case 1
               N->parent->parent->color = RED;         // case 1
               N = N->parent->parent;                 // case 1
            }else{ 
               if (N == N->parent->right){
                  N = N->parent;                     // case 2
                  LeftRotate(N);                 // case 2
               }
               N->parent->color = BLACK;              // case 3
               N->parent->parent->color = RED;         // case 3
               RightRotate(N->parent->parent);     // case 3
            }
         }else{
            y = N->parent->parent->left;
            if (y->color == RED){
               N->parent->color = BLACK;              // case 4
               y->color = BLACK;                     // case 4
               N->parent->parent->color = RED;         // case 4
               N = N->parent->parent;                 // case 4
            }else{ 
               if (N == N->parent->left){
                  N = N->parent;                     // case 5
                  RightRotate(N);                // case 5
               }
               N->parent->color = BLACK;              // case 6
               N->parent->parent->color = RED;         // case 6
               LeftRotate(N->parent->parent);      // case 6
            }
         }
      }
      root->color = BLACK;
   }

   // RB_Transplant()
   void Dictionary::RB_Transplant(Node* u, Node* v){
      if (u->parent == nil){
         root = v;
      }else if (u == u->parent->left){
         u->parent->left = v;
      }else{ 
         u->parent->right = v;
      }
      v->parent = u->parent;
   }

   // RB_DeleteFixUp()
   void Dictionary::RB_DeleteFixUp(Node* N){
   //std::cout<<"remove Fixup: "<<N->key<<std::endl;

      Node* w;
      while (N != root and N->color == BLACK){
         if (N == N->parent->left){
            w = N->parent->right;
            if (w->color == RED){
               w->color = BLACK;                        // case 1
               N->parent->color = RED;                   // case 1
               LeftRotate(N->parent);                // case 1
               w = N->parent->right;                     // case 1
            }
            if ((w->left->color == BLACK) && (w->right->color == BLACK)){
               w->color = RED;                          // case 2
               N = N->parent;                           // case 2
            }else{
               if (w->right->color == BLACK){
                  w->left->color = BLACK;                // case 3
                  w->color = RED;                       // case 3
                  RightRotate(w);                   // case 3
                  w = N->parent->right;                  // case 3
               }
               w->color = N->parent->color;               // case 4
               N->parent->color = BLACK;                 // case 4
               w->right->color = BLACK;                  // case 4
               LeftRotate(N->parent);                // case 4
               N = root;                             // case 4
            }
         }else{
            w = N->parent->left;
            if (w->color == RED){
               w->color = BLACK;                        // case 5
               N->parent->color = RED;                   // case 5
               RightRotate(N->parent);               // case 5
               w = N->parent->left;                      // case 5
            }
            if (w->right->color == BLACK and w->left->color == BLACK){
               w->color = RED;                          // case 6
               N = N->parent;                           // case 6
            }else{
               if (w->left->color == BLACK){
                  w->right->color = BLACK;               // case 7
                  w->color = RED;                       // case 7
                  LeftRotate(w);                    // case 7
                  w = N->parent->left;                   // case 7
               }
               w->color = N->parent->color;               // case 8
               N->parent->color = BLACK;                 // case 8
               w->left->color = BLACK;                   // case 8
               RightRotate(N->parent);               // case 8
               N = root;                             // case 8
            }
         }
      }
      N->color = BLACK;
   }

// Access functions --------------------------------------------------------

// size()
// Returns the size of this Dictionary.
int Dictionary::size() const{
   return num_pairs;
}

// contains()
// Returns true if there exists a pair such that key==k, and returns false
// otherwise.
bool Dictionary::contains(keyType k) const{
   if(search(root,k)==nil){
      return false;
   }
   return true;
}

// getValue()
// Returns a reference to the value corresponding to key k.
// Pre: contains(k)
valType& Dictionary::getValue(keyType k) const{
   if(!(contains(k))){
      throw std::logic_error("Dictionary: getValue(): key "+k+" does not exist");
   }
   return (search(root,k))->val;
}

// hasCurrent()
// Returns true if the current iterator is defined, and returns false 
// otherwise.
bool Dictionary::hasCurrent() const{
   if(current==nil){
      return false;
   }
   return true;
}

// currentKey()
// Returns the current key.
// Pre: hasCurrent() 
keyType Dictionary::currentKey() const{
   if(current==nil){
      throw std::logic_error("Dictionary: currentKey(): current undefined");
   }
   return current->key;
}

// currentVal()
// Returns a reference to the current value.
// Pre: hasCurrent()
valType& Dictionary::currentVal() const{
   if(current==nil){
      throw std::logic_error("Dictionary: currentVal(): current undefined");
   }
   return current->val;
}


// Manipulation procedures -------------------------------------------------

// clear()
// Resets this Dictionary to the empty state, containing no pairs.
void Dictionary::clear(){
   postOrderDelete(root);
   num_pairs = 0;
   root = nil;
   current = nil;
}

// setValue()
// If a pair with key==k exists, overwrites the corresponding value with v, 
// otherwise inserts the new pair (k, v).
void Dictionary::setValue(keyType k, valType v){
   num_pairs++;
   Node* y = nil;
   Node* x = root;
   Node* z = new Node(k,v);
   z->left = nil;
   z->right = nil;
   while(x != nil){
      y = x;
      if(z->key == x->key){
         x->val = v;
         num_pairs--;
         delete z;
         return;
      }else if (z->key < x->key){
         x = x->left;
      }else{
         x = x->right;
      }
   }
   z->parent = y;
   if(y == nil){
      root = z;    // tree T was empty
   }else if(z->key < y->key){
      y->left = z;
   }else{ 
      y->right = z;
   }
   z->left = nil;
   z->right = nil;
   z->color = RED;
   RB_InsertFixUp(z);
}

void Dictionary::Transplant(Node* u,Node* v){
   if(u->parent == nil){
      root = v;
   }
   else if(u == u->parent->left){
      u->parent->left = v;
   }else{
      u->parent->right = v;
   }
   if (v != nil){
      v->parent = u->parent;
   }
}

// remove()
// Deletes the pair for which key==k. If that pair is current, then current
// becomes undefined.
// Pre: contains(k).
void Dictionary::remove(keyType k){
   //std::cout<<"remove: "<<k<<std::endl;
   Node* z = search(root,k);
   Node* y = z;
   Node* x;
   num_pairs--;
   if(current->key == k){
      current = nil;
   }
   int y_original_color = y->color;
   if (z->left == nil){
      x = z->right;
      RB_Transplant(z, z->right);
   }else if (z->right == nil){
      x = z->left;
      RB_Transplant(z, z->left);
   }else{
      y = findMin(z->right);
      y_original_color = y->color;
      x = y->right;
      if (y->parent == z){
         x->parent = y;
      }else{
         RB_Transplant(y, y->right);
         y->right = z->right;
         y->right->parent = y;
      }
      RB_Transplant(z, y);
      y->left = z->left;
      y->left->parent = y;
      y->color = z->color;
   }
   if (y_original_color == BLACK){
      RB_DeleteFixUp(x);
   }
}

// begin()
// If non-empty, places current iterator at the first (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::begin(){
   if(num_pairs>0){
      current = findMin(root);
   }
}

// end()
// If non-empty, places current iterator at the last (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::end(){
   if(num_pairs>0){
      current = findMax(root);
   }
}

// next()
// If the current iterator is not at the last pair, advances current 
// to the next pair (as defined by the order operator < on keys). If 
// the current iterator is at the last pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::next(){
   Node* x = current;
   if(x->right != nil){                // case 1
      current = findMin(x->right);
      return;
   }
   Node* y = x->parent;                      // case 2
   while((y != nil) && (x == y->right)){
      x = y;
      y = y->parent;
   }
   current = y;
}

// prev()
// If the current iterator is not at the first pair, moves current to  
// the previous pair (as defined by the order operator < on keys). If 
// the current iterator is at the first pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::prev(){
   Node* x = current;
   if(x->left != nil){                // case 1
      current = findMax(x->left);
      return;
   }
   Node* y = x->parent;                      // case 2
   while((y != nil) && (x == y->left)){
      x = y;
      y = y->parent;
   }
   current = y;
}


// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this Dictionary. Consecutive (key, value)
// pairs are separated by a newline "\n" character, and the items key and value 
// are separated by the sequence space-colon-space " : ". The pairs are arranged 
// in order, as defined by the order operator <.
std::string Dictionary::to_string() const{
   std::string s;
   inOrderString(s,root);
   return s;
}

// pre_string()
// Returns a string consisting of all keys in this Dictionary. Consecutive
// keys are separated by newline "\n" characters. The key order is given
// by a pre-order tree walk.
std::string Dictionary::pre_string() const{
   std::string s;
   preOrderString(s,root);
   return s;
}

// equals()
// Returns true if and only if this Dictionary contains the same (key, value)
// pairs as Dictionary D.
bool Dictionary::equals(const Dictionary& D) const{// might need fix
   std::string fstr =  to_string();
   std::string sstr =  D.to_string();
   if(fstr!=sstr){
      return false;
   }
   return true;
}


// Overloaded Operators ----------------------------------------------------

// operator<<()
// Inserts string representation of Dictionary D into stream, as defined by
// member function to_string().
std::ostream& operator<<( std::ostream& stream, Dictionary& D ){
   return stream << D.Dictionary::to_string();
}

// operator==()
// Returns true if and only if Dictionary A equals Dictionary B, as defined
// by member function equals(). 
bool operator==( const Dictionary& A, const Dictionary& B ){
   return A.Dictionary::equals(B);
}

// operator=()
// Overwrites the state of this Dictionary with state of D, and returns a
// reference to this Dictionary.
Dictionary& Dictionary::operator=( const Dictionary& D ){
   if(this != &D){ // not self assignment
      // make a copy of Q
      Dictionary temp = D;

      // then swap the copy's fields with fields of this
      std::swap(nil, temp.nil);
      std::swap(root, temp.root);
      std::swap(current, temp.current);
      std::swap(num_pairs, temp.num_pairs);
   }
   return *this;
}