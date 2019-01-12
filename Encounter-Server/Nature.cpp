#include "Nature.h"
#include "EncException.h"

/////////////////////// 	KONSTRUKTORY

Nature::Nature() {
}

Nature::Nature(int x_, int y_, string fileName){
	setX(x_);
	setY(y_);
	setFileName(fileName);
}

Nature::~Nature() {
}

////////////////////////	VIRTUALNE

Mode Nature::interaction(){
	return EXPLORE;
	// docelowo throw IllegalEntry();
}

areaType Nature::checkAdjacent()
{
	return IMPASSABLE;
}

int Nature::freeMoney(){
	// throw cośtam
	return -1;
}

