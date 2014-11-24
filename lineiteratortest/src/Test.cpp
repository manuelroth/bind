#include "getline_iterator.h"
#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include <algorithm>

void testIncrementSetsNextValue() {
	std::istringstream lineStream { "Line 1\nLine 2" };
	auto it = line_iterator(lineStream);
	it++;
	auto secondLine = *it;
	ASSERT_EQUAL("Line 2", secondLine);
}

void testConstructorReadsFirstLine() {
	std::istringstream lineStream { "Line 1\nLine 2" };
	auto it = line_iterator(lineStream);
	ASSERT_EQUAL("Line 1", *it);
}

void testPostfix() {
	std::istringstream lineStream { "Line 1\nLine 2" };
	auto it = line_iterator(lineStream);
	it++;
	ASSERT_EQUAL("Line 2", *it);
}

void testStreamEndsEvenWithNewlineAtEnd() {
	std::istringstream lineStream { "Line 1\nLine 2\n" };
	auto it = line_iterator(lineStream);
	it++;
	it++;
	ASSERT_EQUAL(it, line_iterator { });
}

void testPrefix() {
	std::istringstream lineStream { "Line 1\nLine 2" };
	auto it = line_iterator(lineStream);
	++it;
	ASSERT_EQUAL("Line 2", *it);
}

void testStreamIsAtEnd() {
	std::istringstream lineStream { "First\nSecond\nThird" };
	auto it = line_iterator(lineStream);
	line_iterator end { };
	it++;
	it++;
	ASSERT_NOT_EQUAL_TO(it, end);
	it++;
	ASSERT_EQUAL(it, end);
}

void testIterateOverLinesWithLoop() {
	std::istringstream lineStream { "A long first line\nShorter second line\nLast line" };
	auto actual = std::vector<std::string> { };
	auto expected = std::vector<std::string> { "A long first line", "Shorter second line", "Last line" };

	for (auto it = line_iterator(lineStream); it != line_iterator { }; ++it) {
		actual.push_back(*it);
	}

	ASSERT_EQUAL(expected, actual);
}

void testIterateOverLinesWithVectorCtor() {
	std::istringstream lineStream { "A long first line\nShorter second line\nLast line" };

	auto expected = std::vector<std::string> { "A long first line", "Shorter second line", "Last line" };
	using input = line_iterator;
	auto actual = std::vector<std::string>(input(lineStream), input { });

	ASSERT_EQUAL(expected, actual);
}

void testIterateOverLinesWithCopy() {
	std::istringstream lineStream { "A long first line\nShorter second line\nLast line" };
	auto actual = std::vector<std::string>(3);
	auto expected = std::vector<std::string> { "A long first line", "Shorter second line", "Last line" };
	using input = line_iterator;

	std::copy(input(lineStream), input { }, actual.begin());

	ASSERT_EQUAL(expected, actual);
}

void runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	s.push_back(CUTE(testIterateOverLinesWithLoop));
	s.push_back(CUTE(testPostfix));
	s.push_back(CUTE(testPrefix));
	s.push_back(CUTE(testIncrementSetsNextValue));
	s.push_back(CUTE(testConstructorReadsFirstLine));
	s.push_back(CUTE(testIterateOverLinesWithVectorCtor));
	s.push_back(CUTE(testStreamIsAtEnd));
	s.push_back(CUTE(testStreamEndsEvenWithNewlineAtEnd));
	s.push_back(CUTE(testIterateOverLinesWithCopy));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<> > lis(xmlfile.out);
	cute::makeRunner(lis, argc, argv)(s, "AllTests");
}

int main(int argc, char const *argv[]) {
	runAllTests(argc, argv);
	return 0;
}

