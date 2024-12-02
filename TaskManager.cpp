#include "TaskManager.h"
#include <algorithm>

void TaskManager::addTask(const Task& task) {
	tasks.push_back(task);
}

std::vector<Task> TaskManager::getTasks() const {
	return tasks;
}

std::vector<Task> TaskManager::filterTasks(std::function<bool(const Task&)> filter) const {
	std::vector<Task> filteredTasks;
	std::for_each(tasks.begin(), tasks.end(), [&filteredTasks, &filter](const Task& task) {
		if (filter(task)) {
			filteredTasks.push_back(task);
		}
	});
	return filteredTasks;
}

void TaskManager::sortTasks(std::function<bool(const Task& lhs, const Task& rhs)> comparator) {
	std::sort(tasks.begin(), tasks.end(), comparator);
}