# Countdown Game Solver

Welcome to the Countdown game solver! This program is designed to solve the Countdown numbers game, where the challenge is to use six integer numbers and basic mathematical operators to achieve a result as close as possible to a target integer.

## The Game

The Countdown numbers game is played as follows:

- You are given six integer numbers and a target integer.
- The goal is to combine the six numbers using the operators `+`, `-`, `*`, and `/` to get as close as possible to the target number.
- Each number can be used only once, but it is allowed not to use some numbers.
- Divisions by zero are discarded.

For example, given the numbers `(100, 4, 17, 9, 3, 2)` and the target `37`, one possible solution is: `((100 / (3 + 2)) + 17)`.

## How to Use

To use the Countdown game solver, follow this example:

```cpp
#include <iostream>
#include <vector>

#include "Countdown.h"  // Include the header file for the Countdown solver

int main() {
    // Define the input numbers and target
    std::vector<int> numbers{1, 2, 3, 4, 5, 6};
    int target = 123;

    // Solve the Countdown problem
    CountdownSolution answer = solveCountdownProblem(numbers, target);

    // Display the solution
    std::cout << "Countdown Solution: " << answer.expression << " = " << answer.result << std::endl;

    return 0;
}
