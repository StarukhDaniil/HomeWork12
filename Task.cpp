#include "Task.h"

Task::Task(const std::string& title, const std::string& desription, const int& priority,
	std::chrono::system_clock::time_point deadline) :
	title(title),
	description(description),
	priority(priority),
	deadline(deadline) {
	createdAt = std::chrono::system_clock::now();
	isDone = false;
}