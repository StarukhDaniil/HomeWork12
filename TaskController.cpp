#include "TaskController.h"
#include <functional>

void TaskController::addTask() {
	const std::string title = view.getInput("Enter title: ");
	const std::string description = view.getInput("Enter description: ");
	const int priority = view.getIntegerInput("Enter priority: ");
	const std::chrono::system_clock::time_point deadline = view.getDate();

	system("cls");
	manager.addTask(Task(title, description, priority, deadline));
}

void TaskController::showTasks(std::function<bool(const Task&)> filter =
	[] (const Task&) { return true; }) const {
	std::vector<Task> tasks = manager.filterTasks(filter);
	view.displayTasks(tasks);
}

void TaskController::sortTasks() {
	manager.sortTasks([] (const Task& lhs, const Task& rhs) {
		return lhs.getPriority() < rhs.getPriority();
	});
}

TaskController::TaskController(TaskManager& taskManager, TaskView& taskView) :
	manager(taskManager),
	view(taskView) {
}