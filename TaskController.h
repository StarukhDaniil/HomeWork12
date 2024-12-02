#pragma once

#include "TaskManager.h"
#include "Task.h"
#include "TaskView.h"
#include <iostream>
#include <functional>

class TaskController {
private:
	TaskManager& manager;
	TaskView& view;
public:
	void addTask();
	void showTasks(std::function<bool(const Task&)> filter) const;
	void sortTasks();

	TaskController(TaskManager& taskManager, TaskView& taskView);
};