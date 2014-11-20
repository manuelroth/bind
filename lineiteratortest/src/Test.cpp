#include "getline_iterator.h"
#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

void testFoo() {
	std::istringstream lineStream { "Line 1\nLine 2" };
	auto it = line_iterator (lineStream);
	it++;
	it++;
	auto secondLine = *it;
	ASSERT_EQUAL("Line 2", secondLine);
}

void testConstructorReadsFirstLine() {
	std::istringstream lineStream { "Line 1\nLine 2" };
	auto it = line_iterator (lineStream);
	ASSERT_EQUAL("Line 1", *it);
}

void testPostfix() {
	std::istringstream lineStream { "Line 1\nLine 2" };
	auto it = line_iterator (lineStream);
	it++;
	ASSERT_EQUAL("Line 2", *it);
}

void testPrefix() {
	std::istringstream lineStream { "Line 1\nLine 2" };
	auto it = line_iterator (lineStream);
	++it;
	ASSERT_EQUAL("Line 2", *it);
}

void testIterateOverLines() {
	std::istringstream lineStream { "A long first line\nShorter second line\nLast line" };

	auto expected = std::vector<std::string> { "A long first line", "Shorter second line", "Last line" };
	using input = line_iterator;
	auto lines = std::vector<std::string>(input(lineStream), input { });

	ASSERT_EQUAL(expected, lines);
}

void runAllTests(int argc, char const *argv[]){
	cute::suite s{};
	//TODO add your test here
	s.push_back(CUTE(testIterateOverLines));
	s.push_back(CUTE(testPostfix));
	s.push_back(CUTE(testPrefix));
	s.push_back(CUTE(testFoo));
	s.push_back(CUTE(testConstructorReadsFirstLine));
	//s.push_back(CUTE(testStream));
	cute::xml_file_opener xmlfile(argc,argv);
	cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
	cute::makeRunner(lis,argc,argv)(s, "AllTests");
}

int main(int argc, char const *argv[]){
    runAllTests(argc,argv);
    return 0;
}



