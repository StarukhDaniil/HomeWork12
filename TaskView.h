#pragma once

#include "Task.h"
#include "TaskManager.h"
#include "TaskController.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <functional>

namespace ViewOptions {
	constexpr bool clearConsoleWithoutPressingEnter = false;
	constexpr bool clearConsoleWithPressingEnter = true;
}

enum class TaskActions {
	AddTask = 1,
	ShowTasks = 2,
	EditTasks = 3,
	DeleteTask = 4,
	MarkTaskAsDone = 5,
	SetSorterFunction = 6,
	Exit = 7
};

enum class EditActions {
	cancel = 0x00,
	editTitle = 0x01,
	editDescription = 0x02,
	editPriority = 0x04,
	editDeadline = 0x08
};

class TaskView {
private:
	using clearConsoleWithoutPressingEnter = bool;
	std::time_t getDatePrivate(const std::string& prompt,
		std::function<bool(const int&)> compareValueFilter) const;
public:
	TaskActions menu() const;
	void displayTasks(const std::vector<Task>& tasks) const;
	std::string getInput(const std::string& prompt, std::function<bool(std::string)> filter =
		[](const std::string) {return true; }) const;
	int getIntegerInput(const std::string& prompt,
		std::function<bool(const int&)> inputFilter = [] (const int&) { return true; }) const;
	std::time_t getDate() const;
	std::function<bool(const Task& task)> getFilter() const;
	std::function<bool(const Task& lhs, const Task& rhs)> getSorter() const;
	std::string getTaskTitle() const;
	std::function<void(Task&)> getEditAction() const;
	void clearConsole(const clearConsoleWithoutPressingEnter& option,
		const std::string& prompt = "Press enter to continue:\n") const;
	void message(const std::string& message) const;
};