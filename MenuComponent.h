
#ifndef MENU_COMPONENT_H
#define MENU_COMPONENT_H

#include <string>
#include <stack>
#include <iostream>


class MenuComponent {
public:
    friend std::ostream& operator<< ( std::ostream&, const MenuComponent* );

    // Exception to be throw if container operation is called on a leaf node
    class InvalidOp {};

    // Constructor and destructor; destructor is useful in subclasses to cleanup pointer elements in collection
    MenuComponent( std::string );
    virtual ~MenuComponent() {}

    // leaf-only operations
    virtual bool isVeggie() const {return false;}               // is the menu item vegetarian?
    virtual float price() const { return 0; }                   // what is the price?
    virtual void priceIs( float ) {}                            // set the price of the item
    virtual int calories() const { return 0; }                  // how many calories?
    virtual void caloriesIs( int ) {}                           // modify the number of calories

    // component-only operations
    virtual void add( MenuComponent* ) { throw InvalidOp(); }   // add a menuitem or submenu to a menu
    virtual void remove( std::string ) { throw InvalidOp(); }   // remove a menuitem or submenu from a menu; delete it
    virtual int numChildren() const {return 0;}                 // number of children in the menu
    virtual MenuComponent* getChild(int) const {return NULL;}   // the ith child of the menu

    // shared operations
    std::string name() const { return name_; }                  // return name of menu or menuitem
    std::string menuDepth() const { return menuDepth_; }        // depth of menu component in composite structure (used to indent the element when printing
    virtual void menuDepthInc ();                               // increment the depth of the menu component
    virtual int size() const { return 1; }                      // number of elements in menu component, including all descendents and including self

    class iterator {
    public:
        typedef iterator self_type;
        typedef MenuComponent& reference;
        typedef MenuComponent* pointer;
        typedef std::forward_iterator_tag iterator_category;
        typedef int difference_type;
        iterator(pointer ptr) : ptr_(ptr), next_(new std::stack<MenuComponent*>()), end_(new std::stack<MenuComponent*>()) {}
        ~iterator() { delete next_; delete end_; std::cout << "deleted" << std::endl;}
        virtual self_type operator++() { self_type i = *this; ptr_->get_next_iterator(this); return i; }
        virtual self_type operator++(int junk) { ptr_->get_next_iterator(this); return *this; }
        reference operator*() { return *ptr_; }
        pointer operator->() { return ptr_; }
        bool operator==(const self_type& rhs) {
            std::cout << "equal" << std::endl;
            return ptr_ == rhs.ptr_; }

        bool operator!=(const self_type& rhs) {
            if (ptr_ == rhs.ptr_)
                std::cout << "equal" << std::endl;
            return ptr_ != rhs.ptr_; }

        std::stack<pointer>* get_next() { return next_; }
        std::stack<pointer>* get_end() { return end_; }
        pointer get_pointer() { return ptr_; }

        void set_pointer(pointer p) { ptr_ = p; }
    protected:
        pointer ptr_;
        std::stack<pointer>* next_, *end_;
    };


    virtual iterator begin() = 0;
    virtual iterator end() = 0;
    virtual void get_next_iterator(iterator*) = 0;

protected:
    virtual void print ( std::ostream& ) const = 0;             // used to within operator<< to create a polymorphic operator<<

private:
    std::string name_;
    std::string menuDepth_;
};

std::ostream& operator<< ( std::ostream&, const MenuComponent* );

#endif
