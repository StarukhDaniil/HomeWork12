#include "Task.h"

std::string& Task::getTitle() {
	return title;
}

std::string& Task::getDescription() {
	return description;
}

int& Task::getPriority() {
	return priority;
}

std::chrono::system_clock::time_point& Task::getDeadline() {
	return deadline;
}

void Task::makeDone() {
	isDone = true;
}

const std::chrono::system_clock::time_point& Task::getCreatedAt() const {
	return createdAt;
}

const std::string& Task::getTitle() const {
	return title;
}

const std::string& Task::getDescription() const {
	return description;
}

const int& Task::getPriority() const {
	return priority;
}

const std::chrono::system_clock::time_point& Task::getDeadline() const {
	return deadline;
}

const bool& Task::done() const {
	return isDone;
}

Task::Task(const std::string& title, const std::string& desription, const int& priority,
	std::chrono::system_clock::time_point deadline) :
	title(title),
	description(description),
	priority(priority),
	deadline(deadline) {
	createdAt = std::chrono::system_clock::now();
	isDone = false;
}