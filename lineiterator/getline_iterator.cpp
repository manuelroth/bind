#include "getline_iterator.h"

namespace{
	std::stringstream empty{};
}
line_iterator::line_iterator():in(empty){
	in.clear(std::ios_base::eofbit);
}

std::istringstream line_iterator::dummy{};

line_iterator::value_type line_iterator::operator *(){
	value_type value{};
	in >> value;
	return value;
}

bool line_iterator::operator ==(const line_iterator& other)const{
	return !in.good() && !other.in.good();
}




