#pragma once
#include "ContextInfo.h"
#include "FrameBufferInfo.h"
#include "WindowInfo.h"
#include "IListener.h"

namespace core {

	class FreeGlutHandler {
	public:
		static void init(
			const WindowInfo& windowInfo,
			const ContextInfo& contextInfo,
			const FrameBufferInfo& frameBufferInfo
		);
		static void setListener(IListener*& iListener);
		static void run();
		static void close();

		static void enterFullscreen(); //wasnt static in tutotrial
		static void exitFullscreen(); //wasnt static in tutotrial

		static void printOpenglInfo(const ContextInfo& contextInfo);

	private:
		static IListener* sp_listener;
		static WindowInfo s_windowInfo;
		static void idleCallback();
		static void displayCallback();
		static void reshapeCallback(int width, int height);
		static void closeCallback();
	};

}
