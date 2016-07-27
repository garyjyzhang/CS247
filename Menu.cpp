#include <iostream>
#include <vector>
#include <string>

#include "Menu.h"

using namespace std;


//****************************************************************************
// MENU
//****************************************************************************

Menu::Menu (const string name) : MenuComponent(name) {}

Menu::~Menu() {
	for (vector<MenuComponent*>::iterator i = entries_.begin(); i != entries_.end(); ++i) {
        if ( *i ) {
            delete *i;
            *i = NULL;
        }
    }
}


void Menu::add( MenuComponent* newEntry ) {
    newEntry->menuDepthInc();
    entries_.push_back( newEntry );
}


void Menu::remove( string name ) {
    for ( auto it = entries_.begin(); it != entries_.end(); it++ ) {
        if ( (*it)->name() == name ) {
            delete *it;
            entries_.erase( it );
            return;
        }
    }
}


int Menu::numChildren() const {
    return entries_.size();
}


int Menu::size() const {
    int size = 1;

    for ( auto it = entries_.begin(); it != entries_.end(); it++ ) {
        size += (*it)->size();
    }

    return size;
}


MenuComponent* Menu::getChild( int i ) const {
    return entries_.at(i);
}


void Menu::menuDepthInc() {
    vector<MenuComponent*>::iterator it;

    MenuComponent::menuDepthInc();
    for (it = entries_.begin(); it != entries_.end(); it++ ) {
        (*it)->menuDepthInc();
    }
}

void Menu::get_next_iterator( MenuComponent::iterator* it) {
    if (entries_.size() == 0) {
        if (! it->get_end()->empty() && it->get_pointer() == it->get_end()->top()) {
            MenuComponent* next =  it->get_next()->top();
            it->get_next()->pop();
            it->get_end()->pop();

            it->set_pointer(next);
        }
        else {
            it->set_pointer(it->get_pointer() + 1);
        }
    } else {
        std::cout << "here" << std::endl;
        std::cout << (entries_.at(0) + 1) << std::endl;
        it->get_next()->push(it->get_pointer() + 1);
        it->get_end()->push(entries_.at(entries_.size() - 1));
        it->set_pointer(entries_.at(0));
    }
}

MenuComponent::iterator Menu::begin() {
    return MenuComponent::iterator(this);
}

MenuComponent::iterator Menu::end() {
    return MenuComponent::iterator(this->begin().get_pointer() + 1);
}


void Menu::print ( ostream& sout ) const {
    sout << "\n" << menuDepth() << name() << ":";
}
