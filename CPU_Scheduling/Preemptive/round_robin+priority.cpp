#include <bits/stdc++.h>
using namespace std;

struct Process {
    string id;
    int arrival, burst, priority, remaining, finish = 0;
};

int main() {
    int n, q;
    cout << "Enter number of processes and time quantum: ";
    cin >> n >> q;

    vector<Process> p(n);
    cout << "Enter process ID, arrival time, burst time, and priority:\n";
    for (auto &pr : p) {
        cin >> pr.id >> pr.arrival >> pr.burst >> pr.priority;
        pr.remaining = pr.burst;
    }

    int time = 0, completed = 0;
    vector<pair<string, int>> timeline;

    sort(p.begin(), p.end(), [](auto &a, auto &b) {
        return a.arrival < b.arrival;
    });

    queue<int> ready;
    int idx = 0;
    int curr = -1, used = 0;

    while (completed < n) {
        // Add newly arrived processes
        while (idx < n && p[idx].arrival <= time)
            ready.push(idx++);

        // Preempt if higher priority exists
        vector<int> temp;
        while (!ready.empty()) {
            int i = ready.front(); ready.pop();
            if (curr == -1 || p[i].priority < p[curr].priority)
                temp.push_back(curr), curr = i;
            else
                temp.push_back(i);
        }
        for (int i : temp)
            if (i != -1) ready.push(i);

        if (curr == -1) { time++; continue; }

        // Timeline
        if (timeline.empty() || timeline.back().first != p[curr].id)
            timeline.push_back({p[curr].id, time + 1});
        else
            timeline.back().second = time + 1;

        p[curr].remaining--;
        time++; used++;

        // Check if done or quantum up
        if (p[curr].remaining == 0) {
            p[curr].finish = time;
            completed++;
            curr = -1;
            used = 0;
        } else if (used == q) {
            ready.push(curr);
            curr = -1;
            used = 0;
        }
    }

    // Output
    cout << "\nGantt Chart:\n|";
    for (auto &t : timeline) cout << " " << t.first << " |";
    cout << "\n0"; for (auto &t : timeline) cout << "   " << t.second;

    double total_wait = 0, total_turn = 0;
    cout << "\n\nProcess\tWaiting\tTurnaround\n";
    for (auto &pr : p) {
        int turn = pr.finish - pr.arrival;
        int wait = turn - pr.burst;
        total_wait += wait;
        total_turn += turn;
        cout << pr.id << "\t" << wait << "\t" << turn << "\n";
    }

    cout << "\nAverage Waiting Time: " << total_wait / n;
    cout << "\nAverage Turnaround Time: " << total_turn / n << "\n";
    return 0;
}
