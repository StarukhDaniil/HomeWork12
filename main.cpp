#include <iostream>
#include <vector>

#include "Task.h"
#include "TaskManager.h"
#include "TaskView.h"

int main() {
	Task A("asd", "asd", 2, std::chrono::system_clock::now());
	TaskView B;
	std::vector<Task> tasks;
	tasks.push_back(A);
	B.displayTasks(tasks);
	return 0;
}