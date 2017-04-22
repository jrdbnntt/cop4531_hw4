/*
 * Common test utilities
 */
#include <cstring>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <exception>
#include <string>
#include <iostream>
#include <map>
#include <ctime>
#include "../src/algorithm.h"

using namespace std;

struct TestCase {
    const char* s1;
    const char* s2;
    const char* expectedResult;

    TestCase(const char* s1, const char* s2, const char* expectedResult) {
        this->s1 = s1;
        this->s2 = s2;
        this->expectedResult = expectedResult;
    }

    bool check(const char* result) const {
        return strcmp(expectedResult, result) == 0;
    }
    ostream& printSizeSummary(ostream& out) const {
        out << "[" << strlen(s1) << ":" << to_string(strlen(s2)) << "=" << strlen(expectedResult) << "]";
        return out;
    }

    bool test(AlgorithmSolver *solver) const;

};


class TestException : public exception {
public:
    TestException(const TestCase* testCase, const char* message, const char* result) {
        this->message = "[ \"" + string(testCase->s1) + "\", \"" + string(testCase->s2) + "\" ] :: " + string(message) + " :: ";
        this->message += "Expected \"" + string(testCase->expectedResult);
        this->message += "\", Got \"" + string(result) + "\"";
    }

    virtual const char* what() const throw() {
        return message.c_str();
    }

private:
    string message;
};


bool TestCase::test(AlgorithmSolver *solver) const {
    char* result = new char[solver->getMaxResultLength(s1, s2) + 1];
    solver->solve(s1, s2, result);
    if (!check(result)) {
        throw TestException(this, "FAILED", result);
    };
    delete result;
}


/*
 * Defined test cases
 */
const vector<TestCase> simple_cases = vector<TestCase>({
        TestCase("", "", ""),
        TestCase("A", "A", "A"),
        TestCase("A", "B", ""),
        TestCase("AB", "B", "B"),
        TestCase("AB", "AB", "AB"),
        TestCase("ABC", "AB", "AB"),
        TestCase("ABC", "C", "C"),
        TestCase("ABC", "AC", "AC"),
        TestCase("ACCGGTCGAGTGCGCGGAAGCCGGCCGAA", "GTCGTTCGGAATGCCGTTGCTCTGTAAA", "GTCGTCGGAAGCCGGCCGAA"),
        TestCase("BLEFGKACIILKCGELAEEDAEBIJ", "GICKHEJHIMHFIDBCJKDFEEBKH", "GKIIKEEB"),
        TestCase("EKDEKEJGADACEFK", "IGBHCCGHAIEIEDK", "EEDK"),
        TestCase(
                "WDYBRJAOLKGHPQRMFQZAWZUZHEJBLZLAUVOJVWFMMQAPYGZJSDOQLUROLREHGJQLWZVBLOWBFAE",
                "QMRJSUMXVOKZAVPWLXHAKSAPDYBLUOJRYXPGFIVIXRDLOHYNJBLTSOACTBIUTNSXOUYVJMDZLJA",
                "RJOKZAWHBLUOJPGDLOHJBLOBA"
        )
});


/*
 * Generator utilities
 */


/**
 * Construct random valid string [A-Z] argument with given length
 * @param len
 * @return
 */
char* randStringArgument(int len) {
    char* str = new char[len+1];
    str[len-1] = '\0';
    srand(time(NULL)); // init random seed

    for(int i = 0; i < len; ++i) {
        str[i] = rand() % ('Z' - 'A' + 1) + 'A';
    }
    return str;
}


struct Coordinate {
    double x;
    double y;
    Coordinate(double x, double y) {
        this->x = x;
        this->y = y;
    }
};

double CLOCK_TICKS_PER_MILLISECOND = CLOCKS_PER_SEC / 1000;

void time_runs(vector<Coordinate>& results, AlgorithmSolver* solver, int totalRuns, int testsPerRun) {
    clock_t start;
    double sum;
    char * s1;
    char * s2;
    char * result;
    for (int i = 0; i < totalRuns; ++i) {
        sum = 0;
        for (int j = 0; j < testsPerRun; ++j) {
            s1 = randStringArgument(i);
            s2 = randStringArgument(i);
            result = new char[solver->getMaxResultLength(s1, s2)+1];

            start = clock();
            solver->solve(s1, s2, result);
            sum += (clock() - start)/CLOCK_TICKS_PER_MILLISECOND;

            delete s1;
            delete s2;
            delete result;
        }
        results.push_back(Coordinate(i, sum/testsPerRun));
    }
}

void print_runs(vector<Coordinate>& results, ostream& out) {
    for (int i = 0; i < results.size(); ++i) {
        out << results[i].x << "," << results[i].y << "\n";
    }
}