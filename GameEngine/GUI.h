#pragma once
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>
#include <glm/glm.hpp>
#include <SDL/SDL_events.h>

namespace GameEngine {
	class GUI
	{
	public:
		void init(const std::string& resourceDirectory);
		void draw();
		void destroy();
		void setFont(const std::string& fontFile);
		void onSDLEvent(SDL_Event& evnt);
		void loadScheme(const std::string& schemeFile);
		CEGUI::Window* createWidget(const std::string& type, const glm::vec4& destRectPerc, const glm::vec4& destRectPix, const std::string& name = "");
		static void setWidgetDestRect(CEGUI::Window* widget, const glm::vec4& destRectPerc, const glm::vec4& destRectPix);

		static CEGUI::OpenGL3Renderer* getRenderer() { return m_renderer; }
		const CEGUI::GUIContext* getContext() { return m_context; }

	private:
		static CEGUI::OpenGL3Renderer* m_renderer;
		CEGUI::GUIContext* m_context = nullptr;
		CEGUI::Window* m_root = nullptr;
	};
}

