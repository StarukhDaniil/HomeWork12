#include "TaskView.h"
#include "Task.h"
#include <algorithm>
#include <ctime>
#include <iomanip>

#pragma warning(disable: 4996)

void TaskView::displayTasks(const std::vector<Task>& tasks) const {
	std::time_t time;
	std::cout << "Tasks: " << std::endl;
	std::cout << std::endl;

	std::for_each(tasks.begin(), tasks.end(), [&time](const Task& task) {
		std::cout << "Title: " << task.getTitle() << std::endl;
		std::cout << "Description: " << task.getDescription() << std::endl;
		std::cout << "Priority: " << task.getPriority() << std::endl;
		time = task.getDeadline();
		std::cout << "Deadline: " << std::put_time(std::localtime(&time), "%d-%m-%Y") << std::endl;
		std::cout << "Status: " << (task.done() ? "is done" : "is not done") << std::endl;
		time = task.getCreatedAt();
		std::cout << "Created at: " << std::put_time(std::localtime(&time), "%d-%m-%Y") << std::endl;
		std::cout << std::endl;
	});

	std::cout << std::endl;
}

std::string TaskView::getInput(const std::string& prompt) const {
	std::cout << prompt << " ";
	std::string input;
	std::cin >> input;
	return input;
}

int TaskView::getIntegerInput(const std::string& prompt,
	std::function<bool(const int&)> inputFilter) const {

	int input;
	std::cout << prompt << " ";

	while (true) {
		std::cin >> input;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(32767, '\n');
			std::cout << "You entered something incorrect, try again: ";
		}
		else if (!inputFilter(input)) {
			std::cout << "You entered something incorrect, try again: ";
		}
		else {
			return input;
		}
	}
}

std::time_t TaskView::getDatePrivate(const std::string& prompt, std::function<bool(const int&)> compareValueFilter) const {
	std::istringstream streamPrompt("Day: Month: Year:");
	std::string partStreamPrompt;
	std::stringstream input;
	int partInput;

	if (prompt != "")
		std::cout << prompt << std::endl;

	std::cout << "Enter deadline: " << std::endl;
	while (streamPrompt >> partStreamPrompt) {
		partInput = getIntegerInput(partStreamPrompt, compareValueFilter);
		if (partInput == 0)
			return 0;
		input << partInput << "-";
	}

	std::tm tm {};
	input >> std::get_time(&tm, "%d-%m-%Y");
	std::time_t time = mktime(&tm);
	return time;
}

std::time_t TaskView::getDate() const {
	std::istringstream streamPrompt("Day: Month: Year:");
	std::string partStreamPrompt;
	std::stringstream input;
	int partInput;
	std::cout << "Enter deadline: " << std::endl;
	while (streamPrompt >> partStreamPrompt) {
		partInput = getIntegerInput(partStreamPrompt, [](const int& compareValue) {
			return compareValue < 1;
		});
		if (partInput == 0)
			return 0;
		input << partInput << "-";
	}

	std::tm tm{};
	input >> std::get_time(&tm, "%d-%m-%Y");
	std::time_t time = mktime(&tm);
	return time;
}

std::function<bool(const Task& task)> TaskView::getFilter() const {
	int maxPriority = getIntegerInput("Enter priority filter(if you don`t want any enter 0): ",
		[](const int& compareValue) {
			return compareValue < 0;
		});
	auto priorityFilter = (maxPriority == 0) ? ([maxPriority](const Task& task) {return task.getPriority() < maxPriority; }) :
		([maxPriority]() {return true; });

	std::time_t maxDeadline = getDatePrivate("Enter deadline filter(if you don`t want any enter 0): ");
	auto deadlineFilter = [maxDeadline](const Task& task) {return task.getDeadline() < maxDeadline; };
}