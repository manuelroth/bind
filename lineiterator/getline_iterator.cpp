#include "getline_iterator.h"
#include <iostream>

std::istringstream line_iterator::dummy { };

line_iterator::value_type line_iterator::operator *(){
	return value;
}

bool line_iterator::operator ==(const line_iterator& other) const {
	std::cout << "in.good" << in.good() << std::endl;
	std::cout << "other.in.good" << other.in.good() << std::endl;
	return !in.good() && !other.in.good();
}




