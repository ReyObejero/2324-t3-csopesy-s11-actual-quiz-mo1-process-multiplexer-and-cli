#pragma once

#include "process.h"
#include <queue>
#include <thread>
#include <vector>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <list>

class Scheduler {
public:
    enum SchedulingAlgorithm {
        fcfs,
        sjf,
        rr,
    };

    Scheduler(int cores);
    ~Scheduler();

    void add_process(Process* proc);
    void start();
    void stop();
    void screen_ls();

private:
    std::queue<Process*> process_queue;
    std::vector<std::thread> cpu_threads;
    std::atomic<bool> running;
    std::mutex mtx;
    std::condition_variable cv;
    int num_cores;
    std::list<Process*> running_processes;
    std::list<Process*> finished_processes;

    void cpu_worker(int core_id);
};