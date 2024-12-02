#include <iostream>
#include <vector>

#include "Task.h"
#include "TaskManager.h"
#include "TaskView.h"
#include "TaskController.h"

int main() {
	/*Task A("asd", "asd", 2, std::chrono::system_clock::now());
	TaskView B;
	std::vector<Task> tasks;
	tasks.push_back(A);
	B.displayTasks(tasks);*/
	TaskManager manager;
	TaskView view;
	TaskController controller(manager, view);
	controller.addTask();
	controller.addTask();
	controller.addTask();
	controller.sortTasks();
	controller.showTasks([](const Task& task) {
		if (task.getPriority() < 5) {
			return true;
		}
		else {
			return false;
		}
	});

	return 0;
}