#include "Nature.h"
#include "EncException.h"


Nature::Nature() {
}


Nature::~Nature() {
}

Mode Nature::interaction(){
	return EXPLORE;
	// docelowo throw IllegalEntry();
}

areaType Nature::checkAdjacent()
{
	return IMPASSABLE;
}

