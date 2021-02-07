//Titan Engine, by Atlas X Games 
// Backend.h - header for the class that stores backend data, mostly exists to be able to pass data between application and scene
//might move a bunch of application's stuff here later
#pragma once

//include precompile header
#include "ttn_pch.h"

//include glfw
#include <GLFW/glfw3.h>

namespace Titan {
	//backend static class
	class TTN_Backend {
	public:
		//sets the pointer to the window 
		static void setWindow(GLFWwindow* window) { m_window = window; }

		//gets the window size
		static glm::ivec2 GetWindowSize();

	private:
		//pointer to the window
		static GLFWwindow* m_window;
	};
}