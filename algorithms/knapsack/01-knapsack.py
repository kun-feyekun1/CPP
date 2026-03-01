def knapsack_brute_force(values, weights, capacity):
    n = len(values)
    
    def knapsack_recursive(i, current_weight, current_value):
        if i == n or current_weight > capacity:
            return current_value if current_weight <= capacity else 0
        
        # Don't include the item
        without_item = knapsack_recursive(i + 1, current_weight, current_value)
        
        # Include the item
        with_item = knapsack_recursive(i + 1, current_weight + weights[i], current_value + values[i])
        
        return max(without_item, with_item)
    
    return knapsack_recursive(0, 0, 0)

# Example usage
values = [3, 4, 5, 6]
weights = [2, 3, 4, 5]
capacity = 10

max_value = knapsack_brute_force(values, weights, capacity)
print(f"Maximum value: {max_value}")