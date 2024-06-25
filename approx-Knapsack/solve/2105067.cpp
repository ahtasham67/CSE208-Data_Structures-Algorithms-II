#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <bits/stdc++.h>
#include <iomanip>

using namespace std;

vector<int> knapsack_items; // Global variable to store selected items
long double maxval, usedweight, originalVal;

long double knapsack_OPT(vector<long double> &values, vector<long double> &weights, long double W)
{
    long double n = values.size();

    vector<vector<long double> > dp(n + 1, vector<long double>(n * maxval, INT_MAX));
    for (long double i = 0; i < n; ++i)
    {
        for (long double v = 0; v < n * maxval; ++v)
        {
            if (v <= 0)
            {
                dp[i][v] = 0;
            }
            else if (i == 0 && v > 0)
            {
                dp[i][v] = INT_MAX;
            }
            else
            {
                dp[i][v] = min(dp[i - 1][v], weights[i] + dp[i - 1][v - values[i]]);
            }
        }
    }

    long double max_v = 0;
    for (long double v = 0; v < n * maxval; ++v)
    {
        if (dp[n - 1][v] < W)
        {
            max_v = v;
        }
    }

    usedweight = dp[n - 1][max_v];
    originalVal = max_v;

    // Backtrack to find selected items
    long double w = usedweight;
    long double v = originalVal;
    for (long double i = n - 1; i >= 0 && w > 0; --i)
    {
        if (dp[i][v] != dp[i - 1][v])
        {
            knapsack_items.push_back(i);
            w -= weights[i];
            v -= values[i];
        }
    }
    reverse(knapsack_items.begin(), knapsack_items.end()); // Reverse the indices
    return max_v;
}

int main()
{
    freopen("in.txt", "r", stdin);
    long double n, W;
    cin >> n >> W;
    vector<long double> values(n);
    vector<long double> weights(n);

    // Input values and weights
    for (long double i = 0; i < n; ++i)
    {
        cin >> values[i] >> weights[i];
        if (values[i] > maxval)
            maxval = values[i];
    }

    long double result = knapsack_OPT(values, weights, W);
    long double storeoriginalVal = originalVal;
    cout << "Original Instance:" << endl;
    cout << "Used Weight: " << usedweight << endl;
    cout << "Original Value: " << originalVal << endl;
    cout << "Indices: ";
    for (int idx : knapsack_items)
    {
        cout << idx + 1 << " ";
    }
    cout << endl;
    knapsack_items.clear();

    /*0 < ε ≤ 1 = precision parameter.
    vmax = largest value in original instance.
    ・θ = scaling factor = ε vmax / 2n. */
    // for epsilon = 0.5
    cout << endl;
    cout << "Rounded Instance with Eps: 0.5" << endl;
    long double epsilon = 0.5;
    long double theta = epsilon * maxval / (2.0 * n);
    cout << "Theta: " << setprecision(15) << theta << endl;
    vector<long double> scaled_values(n);
    for (int i = 0; i < n; i++)
    {
        scaled_values[i] = (long double)(ceil(values[i] / theta));
    }
    long double ans = knapsack_OPT(scaled_values, weights, W);
    cout << "Answer of reduced instance: " << setprecision(15) << ans << endl;

    long double reduced_instance_value = ans * theta;
    cout << "Answer of reduced instance multiplied by theta: " << reduced_instance_value << endl;
    cout << "Indices: ";
    for (int idx : knapsack_items)
    {
        cout << idx + 1 << " ";
    }
    cout << endl;
    long double sum = 0;
    for (int idx : knapsack_items)
    {
        sum += values[idx];
    }
    cout << "Answer of original instance (rounded up): " << sum << endl;
    cout << "Used Weight: " << usedweight << endl;
    long double ratio = storeoriginalVal / sum;
    cout << "Ratio: " << ratio << endl;
    knapsack_items.clear();
    scaled_values.clear();

    // for epsilon = 0.2
    cout << endl;
    cout << "Rounded Instance with Eps: 0.2" << endl;
    epsilon = 0.2;
    theta = epsilon * maxval / (2.0 * n);
    cout << "Theta: " << setprecision(15) << theta << endl;
    vector<long double> scaled_values1(n);
    for (int i = 0; i < n; i++)
    {
        scaled_values1[i] = (long double)(ceil(values[i] / theta));
    }
    ans = knapsack_OPT(scaled_values1, weights, W);
    cout << "Answer of reduced instance: " << setprecision(15) << ans << endl;

    reduced_instance_value = ans * theta;
    cout << "Answer of reduced instance multiplied by theta: " << reduced_instance_value << endl;
    cout << "Indices: ";
    for (int idx : knapsack_items)
    {
        cout << idx + 1 << " ";
    }
    cout << endl;
    sum = 0;
    for (int idx : knapsack_items)
    {
        sum += values[idx];
    }
    cout << "Answer of original instance (rounded up): " << sum << endl;
    cout << "Used Weight: " << usedweight << endl;
    ratio = storeoriginalVal / sum;
    cout << "Ratio: " << ratio << endl;
    knapsack_items.clear();

    // for epsilon = 0.1
    cout << endl;
    cout << "Rounded Instance with Eps: 0.1" << endl;
    epsilon = 0.1;
    theta = epsilon * maxval / (2.0 * n);
    cout << "Theta: " << setprecision(15) << theta << endl;
    vector<long double> scaled_values2(n);
    for (int i = 0; i < n; i++)
    {
        scaled_values2[i] = (long double)(ceil(values[i] / theta));
    }
    ans = knapsack_OPT(scaled_values2, weights, W);
    cout << "Answer of reduced instance: " << setprecision(15) << ans << endl;

    reduced_instance_value = ans * theta;
    cout << "Answer of reduced instance multiplied by theta: " << reduced_instance_value << endl;
    cout << "Indices: ";
    for (int idx : knapsack_items)
    {
        cout << idx + 1 << " ";
    }
    cout << endl;
    sum = 0;
    for (int idx : knapsack_items)
    {
        sum += values[idx];
    }
    cout << "Answer of original instance (rounded up): " << sum << endl;
    cout << "Used Weight: " << usedweight << endl;
    ratio = storeoriginalVal / sum;
    cout << "Ratio: " << ratio << endl;
    knapsack_items.clear();

    // for epsilon = 0.05
    cout << endl;
    cout << "Rounded Instance with Eps: 0.05" << endl;
    epsilon = 0.05;
    theta = epsilon * maxval / (2.0 * n);
    cout << "Theta: " << setprecision(15) << theta << endl;
    vector<long double> scaled_values3(n);
    for (int i = 0; i < n; i++)
    {
        scaled_values3[i] = (long double)(ceil(values[i] / theta));
    }
    ans = knapsack_OPT(scaled_values3, weights, W);
    cout << "Answer of reduced instance: " << setprecision(15) << ans << endl;

    reduced_instance_value = ans * theta;
    cout << "Answer of reduced instance multiplied by theta: " << reduced_instance_value << endl;
    cout << "Indices: ";
    for (int idx : knapsack_items)
    {
        cout << idx + 1 << " ";
    }
    cout << endl;
    sum = 0;
    for (int idx : knapsack_items)
    {
        sum += values[idx];
    }
    cout << "Answer of original instance (rounded up): " << sum << endl;
    cout << "Used Weight: " << usedweight << endl;
    ratio = storeoriginalVal / sum;
    cout << "Ratio: " << ratio << endl;
    knapsack_items.clear();
    return 0;
}
