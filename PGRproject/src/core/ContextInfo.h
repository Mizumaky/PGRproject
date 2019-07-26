#pragma once
#include <gl/freeglut.h>

namespace core {

	struct ContextInfo {
		int majorVersion;
		int minorVersion;
		bool isCoreContext;
		int flags;

		ContextInfo();
		ContextInfo(int majorVersion, int minorVersion,
			bool isCoreContext, bool isForwardCompatible, bool debugEnabled);
		ContextInfo(const ContextInfo& other); //copy
		ContextInfo& operator=(const ContextInfo& other); //assign
	};

	inline ContextInfo::ContextInfo() {
		majorVersion = 3;
		minorVersion = 1;
		isCoreContext = true;
		flags = GLUT_DEBUG;
	}

	inline ContextInfo::ContextInfo(int majorVersion, int minorVersion,
		bool isCoreContext, bool isForwardCompatible, bool debugEnabled) {
		this->majorVersion = majorVersion;
		this->minorVersion = minorVersion;
		this->isCoreContext = isCoreContext;
		flags = 0x0000;
		if (isForwardCompatible)
			flags |= GLUT_FORWARD_COMPATIBLE;
		if (debugEnabled)
			flags |= GLUT_DEBUG;
	}

	inline ContextInfo::ContextInfo(const ContextInfo& other) {
		majorVersion = other.majorVersion;
		minorVersion = other.minorVersion;
		isCoreContext = other.isCoreContext;
		flags = other.flags;
	}

	inline ContextInfo& ContextInfo::operator=(const ContextInfo& other) {
		if (this == &other)
			return *this;
		majorVersion = other.majorVersion;
		minorVersion = other.minorVersion;
		isCoreContext = other.isCoreContext;
		flags = other.flags;
		return *this;
	}
}
