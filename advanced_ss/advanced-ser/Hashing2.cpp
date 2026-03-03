#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <string>

using namespace std;

// Simple structure for a product sale record
struct Sale {
    string product_id;      // e.g. "LAP123", "PHONE-XR"
    string product_name;
    string category;        // "Electronics", "Clothing", "Books", ...
    double price;
    int quantity;
};

int main() {
    // Simulated sales data from one day (realistic example)
    vector<Sale> sales = {
        {"LAP123", "Dell XPS 13",        "Electronics", 1299.99,  3},
        {"PHONE-XR", "iPhone XR",        "Electronics",  599.00, 12},
        {"TSH-BLK", "Black T-Shirt M",   "Clothing",      19.99, 45},
        {"BOOK-CPP", "C++ Primer 5th Ed","Books",         54.99,  8},
        {"LAP123", "Dell XPS 13",        "Electronics", 1299.99,  2},
        {"PHONE-XR", "iPhone XR",        "Electronics",  599.00,  7},
        {"HEAD-BT", "Wireless Headphones","Electronics",  89.99, 18},
        {"TSH-BLK", "Black T-Shirt M",   "Clothing",      19.99, 31},
        {"BOOK-CPP", "C++ Primer 5th Ed","Books",         54.99,  5},
        {"SHOE-RUN", "Running Shoes 42", "Footwear",     119.50,  6},
    };

    // ────────────────────────────────────────────────
    // Most typical real-life use: frequency counting
    // Key = product_id, Value = total quantity sold
    // ────────────────────────────────────────────────
    unordered_map<string, int> quantity_sold;

    // Also keep name & price for nice output (another common pattern)
    unordered_map<string, pair<string, double>> product_info;

    // Process all sales
    for (const auto& s : sales) {
        // Count sold quantity
        quantity_sold[s.product_id] += s.quantity;

        // Store / update product info (only once per product usually)
        if (product_info.find(s.product_id) == product_info.end()) {
            product_info[s.product_id] = {s.product_name, s.price};
        }
    }

    cout << "=== Daily Sales Summary ===\n\n";

    // 1. Show how many of each product was sold
    cout << "Product sales (by quantity):\n";
    cout << string(50, '-') << "\n";
    for (const auto& [id, qty] : quantity_sold) {
        auto [name, price] = product_info[id];
        double revenue = qty * price;
        cout << left << setw(20) << name
             << "  sold: " << setw(4) << qty
             << " pcs   revenue: $" << fixed << setprecision(2) << revenue
             << "\n";
    }
    cout << "\n";

    // 2. Find top 3 best-selling products (by quantity)
    vector<pair<string, int>> top_sellers(quantity_sold.begin(), quantity_sold.end());

    // Sort by quantity descending
    sort(top_sellers.begin(), top_sellers.end(),
         [](const auto& a, const auto& b) { return a.second > b.second; });

    cout << "Top 3 best-selling products:\n";
    cout << string(50, '-') << "\n";
    for (size_t i = 0; i < min<size_t>(3, top_sellers.size()); ++i) {
        const auto& [id, qty] = top_sellers[i];
        auto [name, price] = product_info[id];
        cout << (i+1) << ". " << name << "  (" << qty << " sold)\n";
    }
    cout << "\n";

    // 3. Quick lookup example – typical real-time query
    string lookup_id = "PHONE-XR";
    if (quantity_sold.count(lookup_id)) {
        auto [name, price] = product_info[lookup_id];
        cout << "Quick lookup: " << name << " was sold "
             << quantity_sold[lookup_id] << " times "
             << "(revenue: $" << fixed << setprecision(2)
             << quantity_sold[lookup_id] * price << ")\n";
    } else {
        cout << "Product " << lookup_id << " not sold today.\n";
    }

    return 0;
}