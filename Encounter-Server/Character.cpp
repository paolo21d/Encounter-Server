#include "Character.h"

extern int char_id;

Character::Character() {
	id = char_id++;
}


Character::~Character() {
}

int Character::getId() const{
	return id;
}
