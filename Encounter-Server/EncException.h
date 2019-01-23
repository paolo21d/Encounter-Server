#include<exception>


class IllegalEntry : public std::exception{

};

class LeavingMap : public std::exception{

};

class GotInvalidCard : public std::exception{

};

class SomeoneIsStealing : public std::exception{

};