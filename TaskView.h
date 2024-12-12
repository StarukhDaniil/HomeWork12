#pragma once

#include "Task.h"
#include "TaskManager.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <functional>

class TaskView {
private:
	std::time_t getDatePrivate(const std::string& prompt = "",
		std::function<bool(const int&)> compareValueFilter = [](const int& compareValue) {
			return !(compareValue < 1);
		}) const;
public:
	void displayTasks(const std::vector<Task>& tasks) const;
	std::string getInput(const std::string& prompt) const;
	int getIntegerInput(const std::string& prompt,
		std::function<bool(const int&)> inputFilter = [] (const int&) { return true; }) const;
	std::time_t getDate() const;
	std::function<bool(const Task& task)> getFilter() const;
};