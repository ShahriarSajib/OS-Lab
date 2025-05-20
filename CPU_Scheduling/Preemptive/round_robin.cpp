#include <bits/stdc++.h>
using namespace std;

struct process {
    string id;
    int arrival, burst, remaining, waiting = 0, turnaround = 0, finish = 0;
};

int main() {
    int n, quantum;
    cin >> n >> quantum;

    vector<process> p(n);
    for (auto &x : p) {
        cin >> x.id >> x.arrival >> x.burst;
        x.remaining = x.burst;
    }

    sort(p.begin(), p.end(), [](process &a, process &b) {
        return a.arrival < b.arrival;
    });

    queue<int> ready;
    vector<pair<string, int>> gantt;
    int time = 0, done = 0, i = 0;

    while (done < n) {
        // Add newly arrived processes
        while (i < n && p[i].arrival <= time) {
            ready.push(i++);
        }

        if (ready.empty()) {
            time++;
            continue;
        }

        int idx = ready.front(); ready.pop();
        int run_time = min(quantum, p[idx].remaining);

        // Run the process for 'run_time' units
        for (int j = 0; j < run_time; j++) {
            time++;

            if (gantt.empty() || gantt.back().first != p[idx].id)
                gantt.push_back({p[idx].id, time});
            else
                gantt.back().second = time;

            // Check for any newly arrived process during execution
            while (i < n && p[i].arrival <= time) {
                ready.push(i++);
            }
        }

        p[idx].remaining -= run_time;

        if (p[idx].remaining == 0) {
            p[idx].finish = time;
            p[idx].turnaround = p[idx].finish - p[idx].arrival;
            p[idx].waiting = p[idx].turnaround - p[idx].burst;
            done++;
        } else {
            ready.push(idx); // Not finished, put back in queue
        }
    }

    // Print Gantt Chart
    cout << "Gantt Chart:\n|";
    for (auto &x : gantt) cout << " " << x.first << " |";
    cout << "\n" << p[0].arrival;
    for (auto &x : gantt) cout << setw(5) << x.second;

    // Average times
    double total_wait = 0, total_turn = 0;
    for (auto &x : p) {
        total_wait += x.waiting;
        total_turn += x.turnaround;
    }

    cout << "\n\nAvg waiting time = " << total_wait / n;
    cout << "\nAvg turnaround time = " << total_turn / n;

    // Final Table
    cout << "\n\nProcess\tWaiting\tTurnaround\n";
    for (auto &x : p)
        cout << x.id << "\t" << x.waiting << "\t" << x.turnaround << "\n";

    return 0;
}
