#pragma once

#include "Random.h"
#include "Vector2.h"
#include "Transform.h"
#include "MathUtils.h"

// Systems
#include "Renderer.h"
#include "Input.h"
#include "GameTime.h"

#include "Actor.h"
#include "Scene.h"

#include <iostream>
#include <vector>

namespace nu {
	class Engine {

	public:
		static Engine& Get() { static Engine engine; return engine; }

		bool Initialize();
		void Shutdown();

		void Update();

		Input& GetInput() { return m_input; }
		Renderer& GetRenderer() { return m_renderer; }
		Time& GetTime() { return m_time; }

	private:
		Engine() = default;


	private:
		Input m_input;
		Renderer m_renderer;

		Time m_time;
	};

}