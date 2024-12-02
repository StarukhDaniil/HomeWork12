#pragma once

#include "Task.h"
#include "TaskManager.h"
#include <iostream>
#include <vector>

class TaskView {
private:

public:
	void displayTasks(const std::vector<Task>& tasks) const;
	std::string getInput(const std::string& prompt) const;
	int getIntegerInput(const std::string& prompt) const;
};