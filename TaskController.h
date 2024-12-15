#pragma once

#include "TaskManager.h"
#include "Task.h"
#include "TaskView.h"
#include <iostream>
#include <functional>

class Task;
class TaskManager;
class TaskView;

class TaskController {
private:
	TaskManager& manager;
	TaskView& view;
public:
	const TaskManager& getManager() const;
	const TaskView& getView() const;

	void addTask();
	void showTasks() const;
	void editTask();
	void deleteTask();
	void markAsDone();
	void setSorter();
	void menu();

	TaskController(TaskManager& taskManager, TaskView& taskView);
	TaskController(const TaskController& other);
	TaskController& operator=(const TaskController& other);
	~TaskController() = default;
};