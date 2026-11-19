#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Item {
    int weight;
    int value;
};

int main() {
    vector<Item> items = {
        {10, 60},
        {20, 100},
        {30, 120}
    };

    int capacity = 50;
    int n = items.size();

    // dp[i][w] stores the maximum value using the first i items
    // when the available bag capacity is w.
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {
            if (items[i - 1].weight <= w) {
                int excludeItem = dp[i - 1][w];
                int includeItem = items[i - 1].value
                                + dp[i - 1][w - items[i - 1].weight];

                dp[i][w] = max(excludeItem, includeItem);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    cout << "Maximum value (0/1 Knapsack): "
         << dp[n][capacity] << endl;

    return 0;
}

/*
g++ zero_one_knapsack.cpp -o zero_one_knapsack
./zero_one_knapsack
*/

/*
VALUES TO CHANGE (OPTIONAL)
---------------------------
To test different items, edit the 'items' list inside main():

    vector<Item> items = {
        {10, 60},   // {weight, value}
        {20, 100},
        {30, 120}
    };

Change the numbers in each pair using this format:
    {weight, value}

To change the bag's maximum weight, edit:

    int capacity = 50;

Example:
    vector<Item> items = {{5, 30}, {10, 40}, {15, 50}};
    int capacity = 20;

These are values to edit in the source code, not values to type
in the terminal. Save the file and compile it again after editing.
*/

/*
=============================================================
ASSIGNMENT 1(B): 0/1 KNAPSACK USING DYNAMIC PROGRAMMING
=============================================================

1. PROBLEM STATEMENT
--------------------
We are given a bag with a fixed weight capacity and a set of
items. Every item has a weight and a value. We need to select
items so that the total value is maximum without exceeding the
bag's capacity.

In 0/1 Knapsack, an item must be taken completely or not taken.
We cannot take a fraction of an item.

2. WHAT IS DYNAMIC PROGRAMMING?
-------------------------------
Dynamic Programming (DP) solves a problem by dividing it into
smaller subproblems and storing their answers. This avoids
calculating the same subproblem again and again.

For every item, we consider two choices:
    0: Do not take the item.
    1: Take the complete item, if it fits.

The program compares both choices and stores the one that gives
the greater value.

3. HOW THE ALGORITHM WORKS
--------------------------
Step 1: Store the weight and value of every item.
Step 2: Create a 2D DP table with (n + 1) rows and
        (capacity + 1) columns.
Step 3: Initially fill the table with zero.
Step 4: For each item and each possible capacity, check whether
        the item can fit.
Step 5: If it fits, compare the value from excluding the item
        with the value from including the item.
Step 6: Store the greater value in the DP table.
Step 7: If it does not fit, copy the result from the previous row.
Step 8: The answer is stored in dp[n][capacity].

4. DYNAMIC PROGRAMMING FORMULA
------------------------------
If the current item's weight is greater than the available
capacity:

    dp[i][w] = dp[i - 1][w]

Otherwise:

    dp[i][w] = max(
        dp[i - 1][w],
        item.value + dp[i - 1][w - item.weight]
    )

In simple words:
    First choice  = Do not take the current item.
    Second choice = Take the current item.
    Store whichever choice gives the maximum value.

5. CODE EXPLANATION
-------------------
struct Item
    Stores the weight and value of each item.

vector<Item> items
    Stores all the available items.

capacity
    Stores the maximum weight that the bag can carry.

n
    Stores the total number of items.

dp
    A two-dimensional table that stores the best value for
    different item counts and bag capacities.

for (int i = 1; i <= n; i++)
    Processes the items one by one.

for (int w = 0; w <= capacity; w++)
    Checks every possible bag capacity from zero to the maximum.

excludeItem
    Stores the best value when the current item is not selected.

includeItem
    Stores the value when the current item is selected.
    The remaining capacity is used to look up the best value
    calculated for the previous items.

max(excludeItem, includeItem)
    Selects the option that gives the greater value.

dp[n][capacity]
    Contains the final maximum value after considering all items
    and the full bag capacity.

6. EXAMPLE
-----------
Items:
    Item 1: Weight = 10, Value = 60
    Item 2: Weight = 20, Value = 100
    Item 3: Weight = 30, Value = 120

Bag capacity = 50

Possible best selection:
    Take Item 2: weight = 20, value = 100.
    Take Item 3: weight = 30, value = 120.

Total weight = 20 + 30 = 50
Maximum value = 100 + 120 = 220

We cannot take 20/30 of Item 3 because 0/1 Knapsack does not
allow fractions of an item.

7. EXPECTED OUTPUT
------------------
Maximum value (0/1 Knapsack): 220

8. TIME AND SPACE COMPLEXITY
----------------------------
Let:
    n = number of items
    W = maximum bag capacity

Time Complexity:
    O(n * W), because the program fills a table with
    (n + 1) rows and (W + 1) columns.

Space Complexity:
    O(n * W), because the 2D DP table stores these results.

9. IMPORTANT VIVA QUESTIONS
---------------------------

Q1. What is the 0/1 Knapsack Problem?
Ans: It is an optimization problem in which each item is either
     selected completely or not selected.

Q2. Which technique is used in this program?
Ans: Dynamic Programming.

Q3. What does 0/1 mean?
Ans: 0 means do not take the item, and 1 means take the complete
     item.

Q4. Can we take a fraction of an item in 0/1 Knapsack?
Ans: No. We must take the complete item or leave it.

Q5. What is Dynamic Programming?
Ans: It solves smaller subproblems and stores their answers
     to avoid repeated calculations.

Q6. What does dp[i][w] represent?
Ans: The maximum value possible using the first i items with
     a bag capacity of w.

Q7. Why do we use max()?
Ans: To choose the better result between taking and not taking
     the current item.

Q8. What is the time complexity of this solution?
Ans: O(n * W).

Q9. What is the space complexity?
Ans: O(n * W), because a two-dimensional DP table is used.

Q10. Does Greedy always give the optimal solution for 0/1
     Knapsack?
Ans: No. A locally best choice may not give the best overall
     combination.

=============================================================
END OF ASSIGNMENT 1(B)
=============================================================
*/
