#include "getline_iterator.h"

std::istringstream line_iterator::dummy { };

line_iterator::value_type line_iterator::operator *(){
	return value;
}

bool line_iterator::operator ==(const line_iterator& other)const{
	return !in.good() && !other.in.good();
}




