#ifndef GETLINE_ITERATOR_H_
#define GETLINE_ITERATOR_H_

#include <iterator>
#include <sstream>

struct line_iterator: std::iterator<std::input_iterator_tag, std::string> {
	line_iterator(std::istream &input = dummy) :
			in(input) {
		++(*this);
	}

	value_type operator *();

	line_iterator& operator++() {
		std::getline(in, value);
		if (value.size() && in.eof()) {
			in.clear();
		}
		return *this;
	}

	line_iterator operator++(int) {
		line_iterator old { *this };
		++(*this);
		return old;
	}

	bool operator ==(const line_iterator& other) const;
	bool operator !=(line_iterator const &other) const {
		return !(*this == other);
	}

private:
	std::istream &in;
	static std::istringstream dummy;
	value_type value { };
};

#endif
