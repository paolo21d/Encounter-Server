#include "News.h"

using namespace std;

ostream& operator<<(ostream& os, const News& x) {
	if(x.gameMode == FIGHT)
		os << "FIGHT " <<  x.firstFighter->getId() << " " << x.secondFighter->getId() << endl;
	else if(x.gameMode == DEAL)
		os << "TRADE " << x.SALEFACTOR << endl;
	else
		os << "EXPLO" << endl;
	return os;
}
