#include "TaskController.h"
#include <functional>
#include <algorithm>

const TaskManager& TaskController::getManager() const {
	return manager;
}

const TaskView& TaskController::getView() const {
	return view;
}

void TaskController::addTask() {
	const std::string title = view.getInput("Enter title(except 0):", [this](const std::string& input) {
		if (std::any_of(manager.getTasks().cbegin(), manager.getTasks().cend(), [&input](const Task& task) {
			return input == task.getTitle();
			})) {
			view.message("You entered a title that already exists\n");
			return false;
		}
		return input != "0" && input != "";
	});
	const std::string description = view.getInput("Enter description:");
	const int priority = view.getIntegerInput("Enter priority:");
	const std::time_t deadline = view.getDate();

	view.clearConsole(ViewOptions::clearConsoleWithoutPressingEnter);
	manager.addTask(Task(title, description, priority, deadline));
}

void TaskController::showTasks() const {
	auto filter = view.getFilter();
	manager.sortTasks();
	std::vector<Task> tasks = manager.filterTasks(filter);
	view.displayTasks(tasks);
	view.clearConsole(ViewOptions::clearConsoleWithPressingEnter);
}

void TaskController::editTask() {
	std::string taskTitle = view.getTaskTitle();
	if (taskTitle == "0")
		view.clearConsole(ViewOptions::clearConsoleWithoutPressingEnter, "");
		return;
	auto task = std::find(manager.getTasks().begin(), manager.getTasks().end(), taskTitle);
	if (task == manager.getTasks().end()) {
		view.clearConsole(ViewOptions::clearConsoleWithPressingEnter, "You entered invalid title, press enter to continue\n");
		return;
	}
	else {
		auto edit = view.getEditAction();
		edit(*task);
		view.clearConsole(ViewOptions::clearConsoleWithoutPressingEnter, "");
	}
}

void TaskController::deleteTask() {
	std::string taskTitle = view.getTaskTitle();
	if (taskTitle == "0")
		return;
	auto task = std::find(manager.getTasks().begin(), manager.getTasks().end(), taskTitle);
	if (task == manager.getTasks().end()) {
		view.clearConsole(ViewOptions::clearConsoleWithPressingEnter,
			"You enetered invalid title, to continue press enter\n");
		return;
	}
	manager.deleteTask(task);
	view.clearConsole(ViewOptions::clearConsoleWithoutPressingEnter, "");
}

void TaskController::markAsDone() {
	using title = std::string;
	title taskTitle = view.getInput("Enter task title to mark as done(if you want to cancel, enter 0):");
	auto task = std::find(manager.getTasks().begin(), manager.getTasks().end(), taskTitle);

	if (task == manager.getTasks().end()) {
		view.clearConsole(ViewOptions::clearConsoleWithPressingEnter,
			"You entered invalid title, to continue press enter\n");
		return;
	}
	manager.markAsDone(task);
	view.clearConsole(ViewOptions::clearConsoleWithoutPressingEnter, "");
}

void TaskController::setSorter() {
	std::function<bool(const Task&, const Task&)> sorter = view.getSorter();
	manager.setSorter(sorter);
	view.clearConsole(ViewOptions::clearConsoleWithoutPressingEnter, "");
}

void TaskController::menu() {
	TaskActions action;
	action = view.menu();
	view.clearConsole(ViewOptions::clearConsoleWithoutPressingEnter, "");
	switch (action) {
	case TaskActions::AddTask:
		addTask();
		break;
	case TaskActions::ShowTasks:
		showTasks();
		break;
	case TaskActions::EditTasks:
		editTask();
		break;
	case TaskActions::DeleteTask:
		deleteTask();
		break;
	case TaskActions::MarkTaskAsDone:
		markAsDone();
		break;
	case TaskActions::SetSorterFunction:
		setSorter();
		break;
	case TaskActions::Exit:
		exit(0);
	}

}

TaskController::TaskController(TaskManager& taskManager, TaskView& taskView) :
	manager(taskManager),
	view(taskView) {
}

TaskController::TaskController(const TaskController& other) :
	manager(const_cast<TaskManager&>(other.getManager())),
	view(const_cast<TaskView&>(other.getView())) {
}

TaskController& TaskController::operator=(const TaskController& other) {
	this->manager = other.getManager();
	this->view = other.getView();
	return *this;
}