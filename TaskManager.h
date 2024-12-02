#pragma once

#include "Task.h"
#include <iostream>
#include <vector>
#include <functional>

class TaskManager {
private:
	std::vector<Task> tasks;
public:
	void addTask(const Task& task);
	std::vector<Task> getTasks() const;
	std::vector<Task> filterTasks(std::function<bool(const Task&)> filter) const;
	void sortTasks(std::function<bool(const Task&, const Task&)> comparator);
};