def knapsack_dp_bottom_up(values, weights, capacity):
    n = len(values)
    dp = [[0 for _ in range(capacity + 1)] for _ in range(n + 1)]
    
    for i in range(1, n + 1):
        for w in range(1, capacity + 1):
            if weights[i-1] <= w:
                dp[i][w] = max(values[i-1] + dp[i-1][w-weights[i-1]], dp[i-1][w])
            else:
                dp[i][w] = dp[i-1][w]
    
    return dp[n][capacity]

# Example usage
values = [3, 4, 5, 6]
weights = [2, 3, 4, 5]
capacity = 10

max_value = knapsack_dp_bottom_up(values, weights, capacity)
print(f"Maximum value: {max_value}")