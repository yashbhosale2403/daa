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

    // Sort items by value-to-weight ratio in descending order.
    sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
        return (double)a.value / a.weight >
               (double)b.value / b.weight;
    });

    double maximumValue = 0.0;
    int remainingCapacity = capacity;

    // Take complete items first, then take a fraction if required.
    for (const Item& item : items) {
        if (remainingCapacity == 0) {
            break;
        }

        if (item.weight <= remainingCapacity) {
            remainingCapacity -= item.weight;
            maximumValue += item.value;
        } else {
            maximumValue +=
                (double)item.value * remainingCapacity / item.weight;
            remainingCapacity = 0;
        }
    }

    cout << "Maximum value (Fractional Knapsack): "
         << maximumValue << endl;

    return 0;
}

/*
g++ fractional_knapsack.cpp -o fractional_knapsack
./fractional_knapsack
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
ASSIGNMENT 1(A): FRACTIONAL KNAPSACK USING GREEDY METHOD
=============================================================

1. PROBLEM STATEMENT
--------------------
We are given a bag with a fixed weight capacity and a set of
items. Every item has a weight and a value. We need to fill the
bag so that the total value is as large as possible without
crossing the bag's capacity.

In Fractional Knapsack, we are allowed to take a part of an item.

2. WHAT IS THE GREEDY METHOD?
-----------------------------
A Greedy Algorithm makes the best available choice at each step.

For Fractional Knapsack, the best choice is the item that gives
the highest value for each unit of weight.

Value-to-weight ratio = Item value / Item weight

The program sorts all items in descending order of this ratio.
It takes the best item first. If the next item does not fit
completely, it takes only the fraction that fits.

3. HOW THE ALGORITHM WORKS
--------------------------
Step 1: Store the weight and value of every item.
Step 2: Calculate the value-to-weight ratio for each item.
Step 3: Sort the items from highest ratio to lowest ratio.
Step 4: Start filling the bag with the highest-ratio item.
Step 5: If an item fits, take the complete item.
Step 6: If it does not fit, take the fraction that fits.
Step 7: Stop when the bag is full and display the total value.

4. CODE EXPLANATION
-------------------
struct Item
    Stores two details of an item: its weight and its value.

vector<Item> items
    Stores all the items that are available to put in the bag.

capacity
    Stores the maximum weight that the bag can carry.

sort()
    Arranges items according to their value-to-weight ratio.
    The item with the highest ratio comes first.

remainingCapacity
    Stores how much weight the bag can still carry.

maximumValue
    Stores the total value collected from the selected items.

if (item.weight <= remainingCapacity)
    Checks whether the complete item can fit in the remaining
    capacity. If it fits, the complete item is selected.

else
    The complete item cannot fit, so the program takes only the
    fraction that fits.

(double)item.value * remainingCapacity / item.weight
    Calculates the value of the fraction taken from the item.

cout
    Displays the final maximum value.

5. EXAMPLE
-----------
Items:
    Item 1: Weight = 10, Value = 60, Ratio = 6
    Item 2: Weight = 20, Value = 100, Ratio = 5
    Item 3: Weight = 30, Value = 120, Ratio = 4

Bag capacity = 50

Selection:
    Take all of Item 1: weight = 10, value = 60.
    Take all of Item 2: weight = 20, value = 100.
    Remaining capacity = 20.
    Take 20/30 of Item 3: value = 120 * 20/30 = 80.

Total weight = 10 + 20 + 20 = 50
Maximum value = 60 + 100 + 80 = 240

6. EXPECTED OUTPUT
------------------
Maximum value (Fractional Knapsack): 240

7. TIME AND SPACE COMPLEXITY
----------------------------
Let n = number of items.

Time Complexity:
    O(n log n), because sorting the items takes O(n log n).
    The loop that selects items takes O(n).

Space Complexity:
    O(log n) auxiliary space for the sorting implementation
    (excluding the input items and the sort's internal details).

8. IMPORTANT VIVA QUESTIONS
---------------------------

Q1. What is the Fractional Knapsack Problem?
Ans: It is an optimization problem in which we select items
     to get maximum value, and we are allowed to take fractions
     of items.

Q2. Which technique is used in this program?
Ans: Greedy method.

Q3. What is a Greedy Algorithm?
Ans: It chooses the best available option at each step.

Q4. Why do we calculate the value-to-weight ratio?
Ans: To find how much value an item gives per unit of weight.

Q5. Why are items sorted in descending order?
Ans: So that the item giving the highest value per unit weight
     is selected first.

Q6. Can we take half of an item in Fractional Knapsack?
Ans: Yes. We can take any required fraction of an item.

Q7. What is the time complexity of this solution?
Ans: O(n log n), because of sorting.

Q8. Does the Greedy method give an optimal answer for Fractional
    Knapsack?
Ans: Yes, selecting items by the highest value-to-weight ratio
     gives an optimal solution for Fractional Knapsack.

=============================================================
END OF ASSIGNMENT 1(A)
=============================================================
*/
