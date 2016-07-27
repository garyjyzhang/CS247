
#include <sstream>
#include <iomanip>

#include "MenuItem.h"


using namespace std;

// **********************************************************************
// MenuItem
// **********************************************************************

MenuItem::MenuItem( const string name, float price, int cal, bool veggie) :
    MenuComponent(name), price_(price), calories_(cal), isVeggie_(veggie) {}


bool MenuItem::isVeggie() const {
    return isVeggie_;
}

float MenuItem::price() const {
    return price_;
}

void MenuItem::priceIs( float p ) {
    price_ = p;
}

int MenuItem::calories() const {
    return calories_;
}

void MenuItem::caloriesIs ( int c ) {
    calories_ = c;
}

void MenuItem::get_next_iterator( MenuComponent::iterator* it) {
    if (! it->get_end()->empty() && it->get_pointer() == it->get_end()->top()) {
        MenuComponent* next =  it->get_next()->top();
        it->get_next()->pop();
        it->get_end()->pop();

        it->set_pointer(next);
    }
    else {
        it->set_pointer(it->get_pointer() + 1);
    }
}

MenuComponent::iterator MenuItem::begin() {
    return MenuComponent::iterator(this);
}

MenuComponent::iterator MenuItem::end() {
    return MenuComponent::iterator(this->begin().get_pointer() + 1);
}

void MenuItem::print ( ostream& sout ) const {
    sout.precision(2);
    sout.setf(ios::fixed, ios::floatfield);
    sout << menuDepth() << name() << ", $" << price() << ", cal=" << calories();
    if ( isVeggie() )
        sout << " (V)";
}
