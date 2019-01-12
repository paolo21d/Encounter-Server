#include "Object.h"


//////////////////		KONSTRUKTORY

Object::Object(): width(1), x(0), y(0){
	
}

Object::Object(int x_, int y_, int width_): x(x_), y(y_), width(width_) {
	
}

Object::~Object() {
}

//////////////////////		POZOSTAŁE

int Object::getX() const{
	return x;
}
int Object::getY() const{
	return y;
}


int Object::getId() const {
	return id;
}


string Object::getFileName() const {
	return fileName;
}

void Object::setFileName(string newFileName){
	fileName = newFileName;
}

void Object::setX(int x_){
	x = x_;
}
void Object::setY(int y_){
	y = y_;
}

int Object::freeMoney(){
	// nigdy to się nie wywyoła
	return -1;
}
