# Push Swap

## Radix Sort Implementation

The solution is based on the Radix Sort algorithm. High level idea:

1. For each bit position (from LSB to MSB):

-   If current bit is 0: push to stack B (pb)
-   If current bit is 1: rotate stack A (ra)

2. After checking all numbers in A:

-   Push everything from B back to A (pa)

3. Repeat for next bit

## Additional Optimizations

-   Instead of sorting the actual numbers, we sort the indices of the numbers in the sorted order. For example, if we are getting the numbers `1 89 2`, we sort them using the indices `0 2 1`. This guarantees we only need log2(n) bits to represent the numbers (and passes).
-   Early exit: if we don't need to push numbers to B in a pass, we can skip the pass.
-   For each pass, we don't care the order of pushing to B, so we can use the cheapest rotation for each target number (ra or rra).
-   After all `0` bit numbers are pushed to B, we can use `rra` to get the original order if it's more efficient.

## Notes about ordering and printing of stacks

-   When printing the stacks, we print the top of the stack first.

    ```
    4 3 2 1
    ^
    Top
    ```

    ```
    4 > Top
    3
    2
    1
    ```

-   The stack should be ordered so the top is the smallest number.

    `4 3 2 1` -> `1 2 3 4`

-   The top is the 'last' number in the stack
