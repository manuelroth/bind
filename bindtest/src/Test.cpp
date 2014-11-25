#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include <functional>

using namespace std::placeholders;

void testSumFunctor() {
	auto sumFunc = std::bind(std::plus<double> { }, _1, _2);
	double x { 1.0 }, y { 2.0 };
	double expected { x + y };
	ASSERT_EQUAL(expected, sumFunc(x, y));
}

void testTerm() {
	auto multiplyFunc = std::bind(std::multiplies<double> { }, 2, _1);
	auto divideFunc = std::bind(std::divides<double> { }, _2, 3);
	auto combinedFunc = std::bind(std::minus<double> { }, multiplyFunc, divideFunc);
	double x { 2.0 }, y { 3.0 };
	double expected { (2 * x) - (y / 3) };
	ASSERT_EQUAL(expected, combinedFunc(x, y));
}

void testModulo() {
	auto squareFunc = std::bind(std::multiplies<int> { }, _1, _1);
	auto modulusFunc = std::bind(std::modulus<int> { }, squareFunc, _2);
	int x { 2 }, y { 2 };
	int expected { (x * x) % y };
	ASSERT_EQUAL(expected, modulusFunc(x, y));
}

void testSquareRoot() {
	auto squareFunc = std::bind(std::multiplies<double> { }, _1, _1);
	auto sqrtFunc = std::bind(static_cast<double(*)(double)>(&std::sqrt), squareFunc);

	double x { 2 };
	double expected { std::sqrt(x * x) };

	ASSERT_EQUAL(expected, sqrtFunc(x));
}

void testQuadraticEquation() {
	// (x/2)
	auto divideFunc = std::bind(std::divides<double> { }, _1, 2.0);
	// ((x/2)+(x/2))
	auto squareFunc = std::bind(std::multiplies<double> { }, divideFunc, divideFunc);
	// ((x/2)+(x/2)) - y
	auto subtractFunc = std::bind(std::minus<double> { }, squareFunc, _2);
	// sqrt( (x/2)*(x/2) - y )
	auto squareRootFunc = std::bind(static_cast<double(*)(double)>(&std::sqrt), subtractFunc);
	// -(x/2)+sqrt( (x/2)*(x/2) - y )
	auto pqFormulaFunc = std::bind(std::minus<double> { }, squareRootFunc, divideFunc);

	const double x { 4 }, y { 1 };
	double expected { -(x / 2) + std::sqrt((x / 2) * (x / 2) - y) };
	double result = pqFormulaFunc(x, y);
	ASSERT_EQUAL(expected, result);
}

void runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	s.push_back(CUTE(testSumFunctor));
	s.push_back(CUTE(testTerm));
	s.push_back(CUTE(testModulo));
	s.push_back(CUTE(testSquareRoot));
	s.push_back(CUTE(testQuadraticEquation));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<> > lis(xmlfile.out);
	cute::makeRunner(lis, argc, argv)(s, "AllTests");
}

int main(int argc, char const *argv[]) {
	runAllTests(argc, argv);
	return 0;
}

