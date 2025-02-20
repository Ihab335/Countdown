#ifndef COUNTDOWN_H
#define COUNTDOWN_H

#include <string>
#include <sstream>
#include <vector>


std::string intToString(const int x) {
    std::ostringstream str;
    str << x;
    return str.str();
}

class CountdownSolution {
private:
    std::string solution;
    int value;
    
public:
    CountdownSolution() : solution(), value(0) {}
    
    CountdownSolution(const std::string & solutionIn, const int valueIn)
        : solution(solutionIn), value(valueIn) {
    }
    
    const std::string & getSolution() const {
        return solution;
    }
    
    int getValue() const {
        return value;
    }
};

// Do not edit above this line

std::vector<std::vector<int>> allCombinations;

double evaluateCountdown(std::string expression) {
    std::vector<double> expressionList;
    std::stringstream expressionStream(expression);
    std::string temp;
    double a, b;

    while (std::getline(expressionStream, temp, ' ')) {
        if (temp == "+" || temp == "-" || temp == "/" || temp == "*") {
            if (expressionList.size() >= 2) {
                b = expressionList.back();
                expressionList.pop_back();
                a = expressionList.back();
                expressionList.pop_back();

                if (temp == "+") {
                    expressionList.push_back(a + b);
                } else if (temp == "-") {
                    expressionList.push_back(a - b);
                } else if (temp == "*") {
                    expressionList.push_back(a * b);
                } else if (temp == "/" && b != 0) {
                    expressionList.push_back(a / b);
                }
            }
        } else {
            expressionList.push_back(stod(temp));
        }
    }
    
    return expressionList.empty() ? 0 : expressionList.back(); 
}

void generateCombinations(std::vector<int> numbers, std::vector<int> combo, int start, int end, int index, int size);

void storeCombinations(const std::vector<int>& numbers, int size) {
    allCombinations.clear();
    generateCombinations(numbers, {}, 0, size - 1, 0, size);
}

void generateCombinations(std::vector<int> numbers, std::vector<int> combo, int start, int end, int index, int size) {
    if (index == size) {
        allCombinations.push_back(combo);
        return;
    }

    for (int i = start; i <= end && end - i + 1 >= size - index; i++) {
        combo.push_back(numbers[i]);
        generateCombinations(numbers, combo, i + 1, end, index + 1, size);
        combo.pop_back(); 
    }
}

void findBestSolution(std::vector<int> remainingNums, std::string expression, int currentValue, int target, bool isFirst, CountdownSolution &bestSolution) {
    if (std::abs(target - currentValue) < std::abs(target - bestSolution.getValue())) {
        bestSolution = CountdownSolution(expression, currentValue);
    }

    if (remainingNums.empty() || currentValue == target) {
        return;
    }

    for (size_t i = 0; i < remainingNums.size(); ++i) {
        std::vector<int> newRemainingNums = remainingNums;
        newRemainingNums.erase(newRemainingNums.begin() + i);
        std::stringstream exprStream;

        if (isFirst) {
            exprStream << expression << remainingNums[i];
            findBestSolution(newRemainingNums, exprStream.str(), currentValue + remainingNums[i], target, false, bestSolution);
        } else {
            exprStream << expression << " " << remainingNums[i];
            
            findBestSolution(newRemainingNums, exprStream.str() + " +", currentValue + remainingNums[i], target, false, bestSolution);
            
            findBestSolution(newRemainingNums, exprStream.str() + " -", currentValue - remainingNums[i], target, false, bestSolution);
            
            findBestSolution(newRemainingNums, exprStream.str() + " *", currentValue * remainingNums[i], target, false, bestSolution);

            if (remainingNums[i] != 0 && currentValue % remainingNums[i] == 0) {
                findBestSolution(newRemainingNums, exprStream.str() + " /", currentValue / remainingNums[i], target, false, bestSolution);
            }
        }
    }
}

CountdownSolution solveCountdownProblem(const std::vector<int>& numbers, int target) {
    CountdownSolution bestSolution("", 0);
    findBestSolution(numbers, "", 0, target, true, bestSolution);

    if (bestSolution.getSolution().empty()) {
        std::string expression = std::to_string(bestSolution.getValue());
        return CountdownSolution(expression, bestSolution.getValue());
    }
    
    return bestSolution;
}

#endif
