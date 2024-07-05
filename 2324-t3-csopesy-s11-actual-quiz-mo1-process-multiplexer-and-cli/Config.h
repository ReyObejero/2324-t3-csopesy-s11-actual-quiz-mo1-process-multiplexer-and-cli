#pragma once

#include "Scheduler.h"

class Config {
public:
	struct ConfigParameters {
		int num_cpu;
		Scheduler::SchedulingAlgorithm scheduler;
		int quantum_cycles;
		int preemptive;
		double batch_process_freq;
		int min_ins;
		int max_ins;
		double delay_per_exec;
	};

	static void Initialize();
	static ConfigParameters GetConfigParameters();

private:
	static ConfigParameters config_parameters_;

};