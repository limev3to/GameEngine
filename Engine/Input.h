#pragma once
#include "Vector2.h"
#include <vector>

namespace nu {
	class Input {
	public: 
		enum MouseButton {
			Left = 1,
			Middle,
			Right
		};


		bool Initialize();
		void Shutdown();

		void Update();

		bool GetKeyDown(int key) { return m_keyStates[key]; }
		bool GetPrevKeyDown(int key) { return m_prevKeyStates[key]; }
		bool GetKeyPressed(int key) { return !m_prevKeyStates[key] && m_keyStates[key]; }
		bool GetKeyReleased(int key) { return m_prevKeyStates[key] && m_keyStates[key]; }

		bool GetMouseDown(MouseButton button) const { return false; }

		Vector2 GetMousePosition() { return m_mousePosition; }

	private:
		// keyboard
		std::vector<bool> m_keyStates;
		std::vector<bool> m_prevKeyStates;

		// mouse 
		uint32_t m_buttonStates = 0;
		uint32_t m_prevButtonStates = 0;

		Vector2 m_mousePosition{0, 0};
	};
}