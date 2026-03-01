def fractional_knapsack(values, weights, capacity):
    n = len(values)
    # Calculate value-to-weight ratios
    ratios = [(v / w, v, w) for v, w in zip(values, weights)]
    ratios.sort(reverse=True)
    
    total_value = 0
    for ratio, value, weight in ratios:
        if capacity == 0:
            break
        if weight <= capacity:
            # Take the whole item
            total_value += value
            capacity -= weight
        else:
            # Take a fraction of the item
            fraction = capacity / weight
            total_value += value * fraction
            capacity = 0
    
    return total_value

# Example usage
values = [3, 4, 5, 6]
weights = [2, 3, 4, 5]
capacity = 10

max_value = fractional_knapsack(values, weights, capacity)
print(f"Maximum value: {max_value}")