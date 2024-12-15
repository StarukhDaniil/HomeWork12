#include "TaskManager.h"
#include <algorithm>

void TaskManager::addTask(const Task& task) {
	tasks.push_back(task);
}

std::vector<Task>& TaskManager::getTasks() {
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

void TaskManager::setSorter(std::function<bool(const Task& lhs, const Task& rhs)> comparator) {
	sorter = comparator;
}

void TaskManager::sortTasks() {
	std::sort(tasks.begin(), tasks.end(), sorter);
}

const std::function<bool(const Task& lhs, const Task& rhs)>& TaskManager::getSorter() const {
	return sorter;
}

const std::vector<Task>& TaskManager::getTasks() const {
	return tasks;
}

void TaskManager::deleteTask(const std::vector<Task>::iterator& task) {
	tasks.erase(task);
}

void TaskManager::markAsDone(const std::vector<Task>::iterator& task) {
	task->markAsDone();
}

TaskManager::TaskManager() {
	sorter = [](const Task& lhs, const Task& rhs) {
		return lhs.getTitle() < rhs.getTitle();
		};
}

TaskManager::TaskManager(const TaskManager& other) :
	tasks(other.getTasks()),
	sorter(other.getSorter()) {
}

TaskManager& TaskManager::operator=(const TaskManager& other) {
	this->tasks = other.tasks;
	this->sorter = other.getSorter();
	return *this;
}