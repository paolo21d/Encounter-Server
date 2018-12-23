#include "Nature.h"
#include "EncException.h"


Nature::Nature() {
}


Nature::~Nature() {
}

void Nature::interaction(Hero& invader, News& news){
	throw IllegalEntry();
}
