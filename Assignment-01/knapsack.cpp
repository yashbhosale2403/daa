#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Item {
    int weight, value;
};

// Greedy Approach (Fractional Knapsack)
bool cmp(pair<double, Item> a, pair<double, Item> b) {
    return a.first > b.first;
}

double greedyKnapsack(vector<Item> items, int W) {
    vector<pair<double, Item>> ratio;

    for (auto i : items) {
        ratio.push_back({(double)i.value / i.weight, i});
    }

    sort(ratio.begin(), ratio.end(), cmp);

    double totalValue = 0.0;
    int currentWeight = 0;

    for (auto r : ratio) {
        if (currentWeight + r.second.weight <= W) {
            currentWeight += r.second.weight;
            totalValue += r.second.value;
        } else {
            int remain = W - currentWeight;
            totalValue += r.first * remain;
            break;
        }
    }

    return totalValue;
}

// Dynamic Programming (0/1 Knapsack)
int dpKnapsack(vector<Item> items, int W) {
    int n = items.size();

    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (items[i - 1].weight <= w) {
                dp[i][w] = max(
                    dp[i - 1][w],
                    dp[i - 1][w - items[i - 1].weight]
                    + items[i - 1].value
                );
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    return dp[n][W];
}

int main() {
    vector<Item> items = {
        {10, 60},
        {20, 100},
        {30, 120}
    };

    int W = 50;

    double greedyResult = greedyKnapsack(items, W);
    int dpResult = dpKnapsack(items, W);

    cout << "Greedy Knapsack Result: " << greedyResult << endl;
    cout << "Dynamic Programming Result: " << dpResult << endl;

    if (greedyResult != dpResult)
        cout << "\n=> The greedy approach does not always give the optimal solution." << endl;
    else
        cout << "\n=> Both approaches give the same result." << endl;

    return 0;
}

/*
=============================================================
ASSIGNMENT 1: FUNCTIONAL KNAPSACK PROBLEM USING GREEDY AND
             DYNAMIC PROGRAMMING
=============================================================

1. PROBLEM STATEMENT
--------------------
There is a bag with a fixed maximum weight capacity. We are given
items, and every item has a weight and a value. The aim is to get
the maximum total value without exceeding the bag's capacity.

This program solves two versions:
- Fractional Knapsack using the Greedy method.
- 0/1 Knapsack using Dynamic Programming.

2. WHAT IS THE GREEDY METHOD?
-----------------------------
Greedy means choosing the best-looking option at each step.

In Fractional Knapsack, we calculate the value-to-weight ratio:

    Ratio = Value / Weight

We sort items from the highest ratio to the lowest ratio. We take
the best item first. If the complete next item does not fit, we
take only the fraction that fits.

This is suitable for Fractional Knapsack because an item can be
divided into smaller parts.

3. WHAT IS DYNAMIC PROGRAMMING?
-------------------------------
Dynamic Programming (DP) solves a large problem by solving smaller
related problems and storing their answers so they do not need to
be calculated again.

In 0/1 Knapsack, each item has only two choices:
- 0: Do not take the item.
- 1: Take the complete item.

We cannot take a fraction of an item in 0/1 Knapsack.

For each item and each capacity, the program checks:
- The value when the current item is not selected.
- The value when the current item is selected, provided it fits.

It stores the larger value in the DP table.

4. CODE EXPLANATION
-------------------
#include <iostream>
    Allows the program to use input and output, such as cout.

#include <vector>
    Allows us to store a collection of items and the DP table.

#include <algorithm>
    Provides functions such as sort() and max().

struct Item
    Creates a type containing two values: weight and value.

cmp()
    Compares two items using their value-to-weight ratios.
    It places the higher ratio first.

greedyKnapsack()
    Calculates each item's ratio, sorts the items, and fills the
    bag. It takes a fraction of the next item when necessary.

dpKnapsack()
    Creates a table with rows for items and columns for capacities.
    It calculates the best value for every item-count/capacity pair.

main()
    Creates three sample items, sets the bag capacity to 50,
    calls both methods, and prints their results.

5. EXAMPLE WALKTHROUGH
---------------------
Items:
    Item 1: Weight = 10, Value = 60, Ratio = 6
    Item 2: Weight = 20, Value = 100, Ratio = 5
    Item 3: Weight = 30, Value = 120, Ratio = 4

Bag capacity = 50.

Greedy / Fractional Knapsack:
    Take all of Item 1: weight 10, value 60.
    Take all of Item 2: weight 20, value 100.
    The bag has 20 capacity left.
    Take 20/30 of Item 3: value = 120 * (20/30) = 80.
    Total value = 60 + 100 + 80 = 240.

Dynamic Programming / 0/1 Knapsack:
    We cannot split items.
    Taking Item 2 and Item 3 gives weight 20 + 30 = 50
    and value 100 + 120 = 220.
    This is the best valid complete-item combination.
    Total value = 220.

6. EXPECTED OUTPUT
------------------
Greedy Knapsack Result: 240
Dynamic Programming Result: 220

=> The greedy approach does not always give the optimal solution.

NOTE:
The two functions solve different versions of Knapsack. The
Fractional version allows parts of an item; the 0/1 version does
not. The output is useful for showing the two methods, but their
results are not a direct comparison on the same problem variant.

7. TIME AND SPACE COMPLEXITY
----------------------------
Let:
    n = Number of items
    W = Maximum bag capacity

Greedy / Fractional Knapsack:
    Time Complexity: O(n log n), mainly because of sorting.
    Space Complexity: O(n), for storing ratios and item data.

Dynamic Programming / 0/1 Knapsack:
    Time Complexity: O(n * W), because the table has n * W states.
    Space Complexity: O(n * W), for the two-dimensional DP table.

8. IMPORTANT VIVA QUESTIONS
---------------------------

Q1. What is the Knapsack Problem?
Ans: It is an optimization problem where we select items to get
     the maximum value without exceeding a weight limit.

Q2. What is a Greedy Algorithm?
Ans: It chooses the best available option at each step.

Q3. What is Dynamic Programming?
Ans: It solves smaller subproblems and stores their results to
     avoid repeating the same calculations.

Q4. What is Fractional Knapsack?
Ans: A Knapsack problem where we can take a part of an item.

Q5. What is 0/1 Knapsack?
Ans: A Knapsack problem where we either take the complete item
     or do not take it.

Q6. Why do we calculate the value-to-weight ratio?
Ans: It tells us how much value an item provides per unit of weight.

Q7. What is the purpose of sort()?
Ans: It arranges the items by their ratios, from highest to lowest.

Q8. What is the purpose of max() in Dynamic Programming?
Ans: It chooses the larger value between taking and not taking
     the current item.

Q9. What is the time complexity of the Greedy method here?
Ans: O(n log n), because the items are sorted.

Q10. What is the time complexity of 0/1 Knapsack using DP?
Ans: O(n * W).

Q11. Can Greedy always give the optimal answer for 0/1 Knapsack?
Ans: No. A locally best choice may prevent the best overall
     combination.

Q12. Why is a two-dimensional DP table used?
Ans: It stores answers for different numbers of items and
     different bag capacities.

=============================================================
END OF ASSIGNMENT 1
=============================================================
*/
