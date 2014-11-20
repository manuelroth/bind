#include "getline_iterator.h"
#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

void testIterateOverLines() {
	std::istringstream lineStream { "C++ ist mässig cool \n line 2 \n line3" };

	auto expected = std::vector<std::string> { "C++ ist mässig cool", "line 2", "line3" };
	using input = line_iterator;
	auto lines = std::vector<std::string>(input(lineStream), input { });

	ASSERT_EQUAL(expected, lines);
}

void runAllTests(int argc, char const *argv[]){
	cute::suite s{};
	//TODO add your test here
	s.push_back(CUTE(testIterateOverLines));
	//s.push_back(CUTE(testStream));
	cute::xml_file_opener xmlfile(argc,argv);
	cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
	cute::makeRunner(lis,argc,argv)(s, "AllTests");
}

int main(int argc, char const *argv[]){
    runAllTests(argc,argv);
    return 0;
}



