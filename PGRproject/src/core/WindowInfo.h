#pragma once
#include <string>
#include <utility>

namespace core {

	struct WindowInfo {
		std::string name;
		int width, height;
		int positionX, positionY;
		bool isReshapable;

		WindowInfo();
		WindowInfo(std::string name, int width, int height, int startPositionX, int startPositionY, bool isReshapable);
		WindowInfo(const WindowInfo& windowInfo); //copy constructor
		WindowInfo& operator=(const WindowInfo& windowInfo); //assignment operator
	};

	inline WindowInfo::WindowInfo() {
		name = "Steampunk Theater";
		width = 800;
		height = 600;
		positionX = 300;
		positionY = 300;
		isReshapable = true;
	}

	inline WindowInfo::WindowInfo(std::string name, int width, int height, int startPositionX, int startPositionY, bool isReshapable) {
		this->name = std::move(name);
		this->width = width;
		this->height = height;
		this->positionX = startPositionX;
		this->positionY = startPositionY;
		this->isReshapable = isReshapable;
	}

	inline WindowInfo::WindowInfo(const WindowInfo& windowInfo) {
		name = windowInfo.name;
		width = windowInfo.width;
		height = windowInfo.height;
		positionX = windowInfo.positionX;
		positionY = windowInfo.positionY;
		isReshapable = windowInfo.isReshapable;
	}

	inline WindowInfo& WindowInfo::operator=(const WindowInfo& windowInfo) {
		if (this == &windowInfo)
			return *this;
		name = windowInfo.name;
		width = windowInfo.width;
		height = windowInfo.height;
		positionX = windowInfo.positionX;
		positionY = windowInfo.positionY;
		isReshapable = windowInfo.isReshapable;
		return *this;
	}

}
