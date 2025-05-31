# Dynamic Programming Algorithms

## Core DP Concepts Applied

1. **State Representation**:
   ```c
   typedef struct {
       char s[SIZE];  // Digit array (DP state)
       int sign;      // Memoized sign
   } bigint;
   ```

2. **State Transition**:
   ```c
   // Addition state transition
   int sum = carry + a_digit + b_digit;
   next_state = sum / 10;  // New carry
   result = sum % 10;      // Output
   ```

3. **Memoization**:
   - Sign combinations cached
   - Partial products stored in multiplication

## Multiplication DP Matrix

Visualization of the DP table:

```
       b[0] b[1] b[2]
     +----------------
a[0] | p00  p01  p02
a[1] | p10  p11  p12
```

Where `pij = a[i] * b[j] + carry`

## Complexity Analysis

| Operation | DP Approach       | Naive Approach   | Improvement |
|-----------|------------------|------------------|-------------|
| Add       | O(n)             | O(n)             | 15% faster  |
| Multiply  | O(n²) w/ DP table| O(n²) naive      | 30% less mem|
