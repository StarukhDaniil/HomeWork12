#include <iostream>
#include <vector>

#include "TaskController.h"

int main() {
	TaskManager manager;
	TaskView view;
	TaskController controller(manager, view);
	while (true) {
		controller.menu();
	}
	return 0;
}