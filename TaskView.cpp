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
		time = std::chrono::system_clock::to_time_t(task.getDeadline());
		std::cout << "Deadline: " << std::put_time(std::localtime(&time), "%d-%m-%Y") << std::endl;
		std::cout << "Status: " << (task.done() ? "is done" : "is not done") << std::endl;
		time = std::chrono::system_clock::to_time_t(task.getCreatedAt());
		std::cout << "Created at: " << std::put_time(std::localtime(&time), "%d-%m-%Y");
		std::cout << std::endl;
		});

	std::cout << std::endl;
}

std::string TaskView::getInput(const std::string& prompt) const {
	std::cout << prompt;
	std::string input;
	std::cin >> input;
	return input;
}

int TaskView::getIntegerInput(const std::string& prompt) const {
	int input;
	std::cout << prompt;

	while (true) {
		std::cin >> input;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(32767, '\n');
			std::cout << "You entered something incorrect, try again: ";
		}
		else {
			return input;
		}
	}
}