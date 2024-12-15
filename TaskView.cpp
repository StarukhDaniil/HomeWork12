#include "TaskView.h"
#include "Task.h"
#include <algorithm>
#include <ctime>
#include <iomanip>

#pragma warning(disable: 4996 4715)

TaskActions TaskView::menu() const {
	std::cout << "Add task: 1" << std::endl;
	std::cout << "Show tasks: 2" << std::endl;
	std::cout << "Edit task: 3" << std::endl;
	std::cout << "Delete task: 4" << std::endl;
	std::cout << "Mark the task as done: 5" << std::endl;
	std::cout << "Set sorter function: 6" << std::endl;
	std::cout << "Exit: 7" << std::endl;
	std::cout << "Your choice: ";

	TaskActions input;
	input = static_cast<TaskActions>(getIntegerInput("", [](const int& input) {
		return input > 0 && input < 8;
	}));
	return input;
}

void TaskView::displayTasks(const std::vector<Task>& tasks) const {
	std::cout << "Tasks: " << std::endl;
	std::cout << std::endl;

	std::for_each(tasks.begin(), tasks.end(), [](const Task& task) {
		std::time_t* time;
		std::cout << "Title: " << task.getTitle() << std::endl;
		std::cout << "Description: " << task.getDescription() << std::endl;
		std::cout << "Priority: " << task.getPriority() << std::endl;
		time = const_cast<std::time_t*>(&task.getDeadline());
		std::cout << "Deadline: " << std::put_time(std::localtime(time), "%d-%m-%Y") << std::endl;
		std::cout << "Status: " << (task.done() ? "is done" : "is not done") << std::endl;
		time = const_cast<std::time_t*>(&task.getCreatedAt());
		std::cout << "Created at: " << std::put_time(std::localtime(time), "%d-%m-%Y") << std::endl;
		std::cout << std::endl;
	});

	std::cout << std::endl;
}

std::string TaskView::getInput(const std::string& prompt, std::function<bool(std::string)> filter) const {
	std::cout << prompt << " ";
	std::string input;
	while (true) {
		std::getline(std::cin, input);
		if (!filter(input)) {
			std::cout << "You entered something incorrect, try again: ";
		}
		else {
			return input;
		}
	}
}

int TaskView::getIntegerInput(const std::string& prompt,
	std::function<bool(const int&)> inputFilter) const {

	int input;

	if(prompt != "")
		std::cout << prompt << " ";

	while (true) {
		std::cin >> input;
		std::cin.ignore(32767, '\n');
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

std::time_t TaskView::getDatePrivate(const std::string& prompt,
	std::function<bool(const int&)> compareValueFilter) const {
	std::istringstream streamPrompt("Day: Month: Year:");
	std::string partStreamPrompt;
	std::stringstream input;
	int partInput;

	if (prompt != "")
		std::cout << prompt << std::endl;

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
	using daysMonthYearsMask = uint8_t;

	std::istringstream streamPrompt("Day: Month: Year:");
	std::string partStreamPrompt;
	std::stringstream input;
	int partInput;
	std::cout << "Enter deadline: " << std::endl;

	daysMonthYearsMask mask = 0x01;
	while (streamPrompt >> partStreamPrompt) {
		if(mask == 0x01)
			partInput = getIntegerInput(partStreamPrompt, [](const int& input) {
				return input > 0 && input < 32;
				});
		else if(mask == 0x02)
			partInput = getIntegerInput(partStreamPrompt, [](const int& input) {
			return input > 0 && input < 13;
				});
		else
			partInput = getIntegerInput(partStreamPrompt, [](const int& input) {
			return input > 1969 && input < 2100;
				});

		if (partInput == 0)
			return 0;
		input << partInput << "-";
		mask <<= 1;
	}

	std::tm tm{};
	input >> std::get_time(&tm, "%d-%m-%Y");
	std::time_t time = mktime(&tm);
	return time;
}

std::function<bool(const Task& task)> TaskView::getFilter() const {
	int maxPriority = getIntegerInput("Enter priority filter(if you don`t want any enter 0): ",
		[](const int& compareValue) {
			return compareValue > -1;
		});
	auto priorityFilter = [maxPriority](const Task& task) {return task.getPriority() < maxPriority; };

	std::time_t maxDeadline = getDatePrivate("Enter deadline filter(if you don`t want any enter 0): ",
		[](const int& compareValue) {
			return compareValue > -1;
		});
	auto deadlineFilter = [maxDeadline](const Task& task) {return task.getDeadline() < maxDeadline; };

	if ((maxPriority == 0) && (maxDeadline == 0)) {
		return [](const Task&) {return true; };
	}
	else if (maxPriority == 0) {
		return deadlineFilter;
	}
	else if (maxDeadline == 0) {
		return priorityFilter;
	}
	else {
		auto filter = [priorityFilter, deadlineFilter](const Task& task) {
			return priorityFilter(task) && deadlineFilter(task);
		};
		return filter;
	}
}

std::function<bool(const Task& lhs, const Task& rhs)> TaskView::getSorter() const {
	auto prioritySort = [](const Task& lhs, const Task& rhs) {
		return lhs.getPriority() < rhs.getPriority();
	};
	auto deadlineSort = [](const Task& lhs, const Task& rhs) {
		return lhs.getDeadline() < rhs.getDeadline();
	};
	auto alphabetSort = [](const Task& lhs, const Task& rhs) {
		return lhs.getTitle() < rhs.getTitle();
	};

	int choice = getIntegerInput("Sort by priority: 1\nSort by deadline: 2\nSort by alphabet: 3\nYour choice: ",
		[](const int& input) {
			return input > 0 && input < 4;
		});

	switch (choice) {
	case 1:
		return prioritySort;
	case 2:
		return deadlineSort;
	case 3:
		return alphabetSort;
	}
}

std::string TaskView::getTaskTitle() const {
	return getInput("Enter task title(if you want to cancel, enter 0): ", [](const std::string& input) {
		return input != "\n";
		});
}

std::function<void(Task&)> TaskView::getEditAction() const {
	auto editTitle = [this](Task& task) {
		task.getTitle() = getInput("Enter title: ", [](const std::string& input) {
			return input != "" && input != "0";
		});
	};
	auto editDescription = [this](Task& task) {
		task.getDescription() = getInput("Enter description: ");
	};
	auto editPriority = [this](Task& task) {
		task.getPriority() = getIntegerInput("Enter priority: ", [](const int& input) {
			return input > 0;
		});
	};
	auto editDeadline = [this](Task& task) {
		task.getDeadline() = getDate();
	};

	int action = 0;
	std::cout << "Do you want to change(type 1 or 0):" << std::endl;
	std::istringstream prompt("Title: Description: Priority: Deadline: ");
	std::string partPrompt;
	int counter = 0;
	while (prompt >> partPrompt) {
		action |= getIntegerInput(partPrompt, [](const int& input) {
			return input == 0 || input == 1;
			}) << counter;
		++counter;
	}
	auto edit = [editTitle, editDescription, editPriority, editDeadline, action](Task& task) {
		if (action & 0x01) {
			editTitle(task);
		}
		if (action & 0x02) {
			editDescription(task);
		}
		if (action & 0x04) {
			editPriority(task);
		}
		if (action & 0x08) {
			editDeadline(task);
		}
	};
	return edit;
}

void TaskView::clearConsole(const clearConsoleWithoutPressingEnter& option, const std::string& prompt) const {
	if (prompt != "")
		std::cout << prompt;

	if(option)
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	system("cls");
}

void TaskView::message(const std::string& message) const {
	std::cout << message;
}