#include <initializer_list>
#include <iostream>
#include <cassert>

/**********************************************************************************
 * README 
 * ********************************************************************************
 * This starter code is a skeleton of the Set and Node classes.
 * You can modify this code to create your project_5 submission.
 * Any main() functin or output will be ignoed by testing software.
 * A testing main() can be found on Learn.
 * 
 * From Project 5 Specification: 2.1 Development Stratigies
 * "First, implement the node class and all of its member functions. This should be
 *  straight-forward from the course notes, as they are the same member functions as 
 *  for a linked list.
 * 
 *  Second, start with a skeleton, where each member function is defined, but where
 *  the default values of the return type is returned. ..."
 * 
 * The skeleton has been povided (below) for you to modify.
*/

class Set;
class Node;
std::ostream &operator<<( std::ostream &out, Set const &rhs );
 
  /////////////////////////////
 /// Set class declaration ///
/////////////////////////////
class Set {
  public:
    Set( std::initializer_list<int> initial_values );
   ~Set();
 
    // The instructions will describe exactly what to do
    Set( Set const &orig );
    Set( Set      &&orig );
 
    // The instructions will describe exactly what to do
    Set &operator=( Set const &orig );
    Set &operator=( Set      &&orig );
 
    // Size operations
    bool        empty() const;
    std::size_t size()  const;
 
    // Clear all items out of the set
    void clear();
 
    // Find the value item in the set
    //  - Return the address of the node if found,
    //    and nullptr otherwise.
    Node *find( int const &item ) const;
 
    // Insert the item into the set if it
    // is not already in the set.
    //  - Return 1 if the item is new,
    //    and 0 otherwise.
    std::size_t insert( int const &item );
 
    // Insert all the items in the array
    // from array[begin] to array[end - 1]
    // that are not already in the set.
    //  - Return the number of items inserted
    //    into the set.
    std::size_t insert( int         const array[],
                        std::size_t const begin,
                        std::size_t const end );
 
    // Remove the item from the set and
    // return the number of items removed.
    std::size_t erase( int const &item );
 
    // Move any items from 'other', whose values
    // do not appear in 'this', to 'this'
    // Leave any items that already appear
    // in 'this' and 'other' in 'other'. 
    std::size_t merge( Set &other );

 
    // Set operations
    Set &operator|=( Set const &other );
    Set &operator&=( Set const &other );
    Set &operator^=( Set const &other );
    Set &operator-=( Set const &other );
 
    Set operator|( Set const &other ) const;
    Set operator&( Set const &other ) const;
    Set operator^( Set const &other ) const;
    Set operator-( Set const &other ) const;
 
    // Returns 'true' if the 'other' set
    // is a subset of 'this' set; that is,
    // all entries in the 'other' set are
    // also in this set.
    bool operator<=( Set const &other ) const;
    bool operator>=( Set const &other ) const;
    bool operator<( Set const &other ) const;
    bool operator>( Set const &other ) const;
 
    bool operator==( Set const &other ) const;
    bool operator!=( Set const &other ) const;
   
  private:
    Node *p_head_;
 
  friend std::ostream &operator<<( std::ostream &out, Set const &rhs );
};


  ///////////////////////////////
 /// Node class declaration  ///
///////////////////////////////
class Node {
  public:
    Node( int new_value, Node *new_next );
    int   value() const;
    Node *next()  const;
 
  private:
    int   value_;
    Node *next_;

  // Allow any member function in the class
  // 'Set' to access or modify the member
  // variables of any instance of this class.
  friend class Set;
};
 
  ///////////////////////////////
 /// Node class Definition   ///
///////////////////////////////

// Node member function
Node::Node( int new_value, Node *new_next ):
value_ { new_value },
next_ { new_next } {
    //Empty constructor
}

int Node::value() const {
    return value_;
}

Node *Node::next() const {
    return next_;
}

  ///////////////////////////////
 /// Set class definition    ///
///////////////////////////////

// Initializing constructor
Set::Set( std::initializer_list<int> initial_values):
    p_head_ {nullptr} {
      for ( int const &value : initial_values ) {
        insert( value );
      }
      
    }   

// Destructor
Set::~Set() {
    clear(); 
}
 
// Copy constructor
Set::Set( Set const &orig ):
  p_head_ { nullptr } {
  for ( Node *ptr{ orig.p_head_ }; ptr != nullptr; ptr = ptr->next() ) {
    insert( ptr->value() );
  }
}

// Move constructor
Set::Set( Set &&orig ):
  p_head_ { orig.p_head_ }
 {
  orig.p_head_ = nullptr;
}
 
// Copy assignment
Set &Set::operator=( Set const &orig ) {
  if ( this == &orig ) {
    return *this;
  } else {
    clear();
    for ( Node *p = orig.p_head_; p != nullptr; p = p->next() ) {
      insert( p->value() );
    }
  }
  return *this;
}

// Move assignment
Set &Set::operator=( Set &&orig ) {
  if ( this == &orig ) {
    return *this;
  }
  clear();
  p_head_ = orig.p_head_;
  orig.p_head_ = nullptr;
  return *this;
}
 
// Empty
bool Set::empty() const {
  //empty?
  //1 == it is empty!
  //0 == not empty.
  return ( p_head_ == nullptr );
}

// Size
std::size_t Set::size() const {
  std::size_t size = 0;
  for ( Node *p_node{ p_head_}; p_node != nullptr; 
                                p_node = p_node->next_ )
  {
    ++size;
  }
  return size;
}
 
 
// Clear
void Set::clear() {
  while ( p_head_ != nullptr ) {
    Node *current{ p_head_ };
    p_head_ = p_head_->next_;
    delete current;
    current = nullptr;
  }
  return;
}
 
// Find
Node *Set::find( int const &item ) const {
  for ( Node *p = p_head_; p != nullptr; p = p->next_ ) {
    if ( p->value_ == item ) {
      return p;
    }
  }
  return nullptr;
}


 
// Insert the item into the set
std::size_t Set::insert( int const &item ) {
  if ( find( item ) != nullptr ) {
    return 0;
  } else {
    //insert to the front
    p_head_ = new Node { item, p_head_ };
    return 1;
  }

}
 
// Insert all the items in the array
std::size_t Set::insert( int         const array[],
                         std::size_t const begin,
                         std::size_t const end ) {
  std::size_t count = 0;
  for ( std::size_t i{begin}; i < end; ++i ) {
    if ( insert( array[i] ) ) {
      ++count;
    }
  }
  return count;
}

 
// Remove the item from the set and
// return the number of items removed.
std::size_t Set::erase( int const &item ) {
  std::size_t count = 0;
  Node *p = p_head_;
  while ( p != nullptr ) {
    if ( p->value() == item ) {
      //找到一样的了
      if ( p == p_head_ ) {
        //刚好是头部节点
        p_head_ = p->next();
        delete p;
        p = p_head_;
      } else {
        //非头节点删除
        Node *p_a = p_head_;
        while ( p_a->next() != p ) {
          p_a = p_a->next();
        }
        //update p;
        Node *tem = p_a->next();
        p = p->next();
        p_a->next_ = p;
        delete tem;
      }
      ++count;
    } else {
      p = p->next();
    }
  }
  return count;
}
 
// Move any items from 'other', whose values
// do not appear in 'this', to 'this'.
// Leave any items that already appear
// in both sets, in both sets. 
std::size_t Set::merge( Set &other ) {
  std::size_t count{ 0 };

  Node *p = other.p_head_;
  while ( p != nullptr ) {
    if ( find( p->value()) == nullptr ) {
      //这个entry在this里没有
      //移动到母集
      //first entry case:
      if ( p == other.p_head_ ) {
        Node *p_a = p;
        p = p->next();
        p_a->next_ = p_head_;
        p_head_ = p_a;
        other.p_head_ = p;

      } else {
        //not first entry
        Node *p_a = other.p_head_;
        while ( p_a->next() != p ) {
          p_a = p_a->next();
        }
        Node *tem = p;
        p = p->next();
        p_a->next_ = p;
        tem->next_ = p_head_;
        p_head_ = tem;
      }
      ++count;
    } else {
      //already has this entry
      p = p->next();
    }
  }
  return count;
}

  //////////////////////
 /// Set operations ///
//////////////////////
Set &Set::operator|=( Set const &other ) {
  for ( Node *p = other.p_head_; p != nullptr; p = p->next() ) {
    //挨个查看find 看是不是已经在母集里
    Node *i = find( p->value());
    if ( i == nullptr ) {
      //不在：那么头插入
      insert( p->value());
    }  
  }
  return *this;
}

Set &Set::operator&=( Set const &other ) {
  Node *p = p_head_;  
  while ( p != nullptr ) {
    Node *p_a = p->next();
    Node *b = other.find( p->value());
    if ( b == nullptr ) {
      erase( p->value() );
    }
    p = p_a;
  }
  return *this;
}
 
Set &Set::operator^=( Set const &other ) {
  for ( Node *p = other.p_head_; p != nullptr; p = p->next()) {
    if ( find( p->value()) != nullptr ) {
      erase( find( p->value())->value());      
    } else {
      insert( p->value() );
    }
  }
  return *this;
}
 
Set &Set::operator-=( Set const &other ) {
  for ( Node *p = other.p_head_; p != nullptr; p = p->next() ) {
    if ( find( p->value()) != nullptr ) {
      erase( find( p->value())->value());
    }
  }
  return *this;
}
 
Set Set::operator|( Set const &other ) const {
  Set result{ *this };
  result |= other;
  return result;
}
 
Set Set::operator&( Set const &other ) const {
  Set result{ *this };
  result &= other;
  return result;
}
 
Set Set::operator^( Set const &other ) const {
  Set result{ *this };
  result ^= other;
  return result;
}
 
Set Set::operator-( Set const &other ) const {
  Set result{ *this };
  result -= other;
  return result;
}

// Returns 'true' if the 'other' set
// is a subset of 'this' set; that is,
// all entries in the 'other' set are
// also in this set.
bool Set::operator>=( Set const &other ) const {
  bool same = true;
  if ( size() < other.size() ) {
    return false;
  }
  for ( Node *p = other.p_head_; p != nullptr; p = p->next() ) {
    Node *i = find( p->value() );
    if ( i == nullptr ) {
      same = false;
      break;
    }
  }
  return same;
}
 
bool Set::operator<=( Set const &other ) const {
  return ( other >= *this );
}
 
bool Set::operator>( Set const &other ) const {
  bool b = true;
  if ( size() <= other.size() ) {
    return false;
  }
  for ( Node *p = other.p_head_; p != nullptr; p = p->next() ) {
    Node *i = find( p->value() );
    if ( i == nullptr ) {
      b = false;
      break;
    }
  }
  return b;
}
 
bool Set::operator<( Set const &other ) const {
  bool b = true;
  if ( size() >= other.size() ) {
    return false;
  }
  for ( Node *p = p_head_; p != nullptr; p = p->next()) {
    Node *i = other.find( p->value() );
    if ( i == nullptr ) {
      b = false;
      break;
    }
  }
  return b;
}
 
bool Set::operator==( Set const &other ) const {
  if ( size() != other.size() ) {
    return false;
  }
  return ( other >= *this )&&( other <= *this );
}
 
bool Set::operator!=( Set const &other ) const {
  return ( !( other == *this ));
}


  ////////////////////////////////////////////
 /// Supplied Code for print Set objects  ///
////////////////////////////////////////////
/// @brief Overloads the << operator allowing the print of Set objects
/// @param out The ostream to print to (e.g. std::cout <<)
/// @param rhs The Set to print (e.g. << set_A)
/// @note You do not need to edit or alter this code
std::ostream &operator<<( std::ostream &out, Set const &rhs ) {
  out << "{";
  if ( !rhs.empty() ) {
    out << rhs.p_head_->value();   
    for ( Node *ptr{ rhs.p_head_->next() }; ptr != nullptr; ptr = ptr->next() ) {
      out << ", " << ptr->value();
    }
  }
  out << "}";
 
  return out;
}