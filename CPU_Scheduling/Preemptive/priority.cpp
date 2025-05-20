#include <bits/stdc++.h>
using namespace std;

struct process {
    string id;
    int arrival, burst, priority;
    int remaining, waiting = 0, turnaround = 0, finish = 0;
};

int main() {
    int n;
    cin >> n;
    vector<process> p(n);
    for (auto &x : p) {
        cin >> x.id >> x.arrival >> x.burst >> x.priority;
        x.remaining = x.burst;
    }

    int time = 0, done = 0;
    double total_waiting = 0, total_turnaround = 0;
    vector<pair<string, int>> gantt;

    string last_id = "";

    while (done < n) {
        int idx = -1;
        for (int i = 0; i < n; ++i) {
            if (p[i].arrival <= time && p[i].remaining > 0) {
                if (idx == -1 || p[i].priority < p[idx].priority) {
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            p[idx].remaining--;

            if (last_id != p[idx].id) {
                gantt.emplace_back(p[idx].id, time);
                last_id = p[idx].id;
            }

            if (p[idx].remaining == 0) {
                done++;
                p[idx].finish = time + 1;
                p[idx].turnaround = p[idx].finish - p[idx].arrival;
                p[idx].waiting = p[idx].turnaround - p[idx].burst;
                total_waiting += p[idx].waiting;
                total_turnaround += p[idx].turnaround;
            }
        }
        time++;
    }

    gantt.emplace_back(last_id, time); // Final entry in Gantt

    // Gantt Chart Output
    cout << "Gantt Chart:\n|";
    for (auto &entry : gantt) cout << " " << entry.first << " |";
    cout << "\n" << gantt[0].second;
    for (int i = 1; i < gantt.size(); ++i)
        cout << setw(4) << gantt[i].second;

    // Results
    cout << fixed << setprecision(2);
    cout << "\n\nAvg waiting time = " << total_waiting / n;
    cout << "\nAvg turnaround time = " << total_turnaround / n;
    cout << "\n\nProcess\tWaiting\tTurnaround\n";
    for (auto &x : p)
        cout << x.id << "\t" << x.waiting << "\t" << x.turnaround << "\n";

    return 0;
}
