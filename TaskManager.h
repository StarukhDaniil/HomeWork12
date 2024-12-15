#pragma once

#include "Task.h"
#include <iostream>
#include <vector>
#include <functional>

class TaskManager {
private:
	std::vector<Task> tasks;
	std::function<bool(const Task& lhs, const Task& rhs)> sorter;
public:
	void addTask(const Task& task);
	std::vector<Task>& getTasks();
	std::vector<Task> filterTasks(std::function<bool(const Task&)> filter) const;
	void setSorter(std::function<bool(const Task& lhs, const Task& rhs)> comparator);
	void sortTasks();
	const std::function<bool(const Task& lhs, const Task& rhs)>& getSorter() const;
	const std::vector<Task>& getTasks() const;
	void deleteTask(const std::vector<Task>::iterator& task);
	void markAsDone(const std::vector<Task>::iterator& task);
	
	TaskManager();
	TaskManager(const TaskManager&);
	TaskManager& operator=(const TaskManager&);
	~TaskManager() = default;
};