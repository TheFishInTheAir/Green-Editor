#pragma once
#include <glm/glm.hpp>
#include <ge/phys/2d/AABB2D.h>
#include <ge/graphics/meshes/TriangleMesh.h>
#include <string>
#include <queue>
#include <list>
#include <unordered_map>
#include <functional>

namespace ge
{
	namespace GELly 
	{
		const std::string LOG_TAG = "GELly";

		///Window Flags
		const long GELLY_WINDOW_NO_TITLE = 1 << 0; //TODO: make reverse Id Est GELLY_WINDOW_TITLE instead of removing title
		const long GELLY_WINDOW_NO_BACKGROUND = 1 << 1;
		const long GELLY_WINDOW_NOT_RESIZABLE = 1 << 2;


		const std::string U_MODE = "rmode";      //required by: all
		const std::string U_POS = "pos";        //required by: all
		const std::string U_DIM = "dim";        //required by: all
		const std::string U_DEPTH = "depth";      //required by: all
		const std::string U_BG_Colour = "bg_colour";  //required by: rect,
		const std::string U_FG_Colour = "fg_colour";  //required by: text,

		const std::string U_ATLAS = "atlas";      //required by: text,
		const std::string U_ATLAS_LOC = "atlas_loc";  //required by: text,


		const int MODE_RECT = 0;
		const int MODE_TEXT = 1;

		const int FONT_ATLAS_POS = 0;


		struct GELlyContext
		{
			struct _style;
			struct _intractable;
			struct _window;

			_style style();

			std::unordered_map<std::string, _window*>* windows = new std::unordered_map<std::string, _window*>();
			bool inWindow = false;

			_window* currentWindow; //NOTE: not thread safe

			bool isRendering = false;

			TriangleMesh* mesh;

			//Bounding
			//std::queue<std::pair<_intractable, ScreenInput.EventType>>* eventInteractionBuffer = new std::queue<std::pair<_intractable, ScreenInput.EventType>>();
			std::list<_intractable>* interactables = new std::list<_intractable>();
		};

		struct _style 
		{
			//Default Style Settings

			//Font   font = LoadFont.loadFromBDF(Resources.get("GELly/default_font/knxt/knxt.bdf"));
			glm::vec4 WINDOW_BACKGROUND = glm::vec4(((float)0x39) / 255, ((float)0x3E) / 255, ((float)0x41) / 255, 1);
			glm::vec4 WINDOW_BODY_TEXT = glm::vec4(((float)0xD3) / 255, ((float)0xD0) / 255, ((float)0xCB) / 255, 1);
			glm::vec4 WINDOW_TITLE_TEXT = glm::vec4(((float)0xE7) / 255, ((float)0xE5) / 255, ((float)0xDF) / 255, 1);

			glm::vec4 WINDOW_BUTTON_TOGGLE_BG = glm::vec4(0x1181d);

			glm::vec4 WINDOW_HIGHLIGHT = glm::vec4(((float)0x44) / 255, ((float)0xBB) / 255, ((float)0xA4) / 255, 1);
			glm::vec4 WINDOW_HIGHLIGHT_2 = glm::vec4(((float)0xDB) / 255, ((float)0xD0) / 255, ((float)0x53) / 255, 1);

			int  WINDOW_TITLE_HEIGHT = 18; //pixels
			int  WINDOW_RESIZE_PAD_DIM = 8;
			int  WINDOW_ELEMENT_PADDING = 5; //pixels

			glm::vec2 WINDOW_MINIMUM_SIZE = glm::vec2(50, WINDOW_TITLE_HEIGHT + WINDOW_ELEMENT_PADDING + 10);


			int  LABEL_HEIGHT = 14; //pixels
		};

		struct _component
		{
			std::string label;
			bool hasDrewn;
			GELlyContext* ctx;

			virtual void destroy() = 0;
		};

		struct _intractable
		{
			AABB2D aabb;

			float depth = 0;

			/*Consumer<ScreenInput.EventType> eventlistiner = null;
			Consumer<ScreenInput.EventType> interactionListiner;*/
		};

		struct _button : public _component
		{
			bool hasBeenClicked = false;

			_intractable intractable;


			void destroy()
			{
				ctx->interactables.remove(intractable);
			}
		};

		struct _toggle_button : public _component
		{
			bool clickState = false;

			_intractable intractable;


			void destroy()
			{
				ctx->interactables.remove(intractable);
			}
		};

		struct _window
		{
			bool hasInit = false;

			GELlyContext ctx;

			bool hasDrewn = false;

			std::string label;

			float depthPos = 0.0f; //between 0 and 1 TODO: implement

			long flags = 0;
			glm::vec2 pos(0);
			glm::vec2 dim(0);

			int elementY = 0;

			std::unordered_map<std::string, _component*>* components = new std::unordered_map<std::string, _component*>();

			//AABB
			_intractable* label_i = nullptr;
			_intractable* resize_i = nullptr;

			void destroy() //TODO: put into src
			{
				if (label_i != nullptr)
					ctx.interactables.remove(label_i);

				if (resize_i != nullptr)
					ctx.interactables.remove(resize_i);
			}

		};

		//Static Funcs
		GELlyContext* createContext();
		void destroyContext(GELlyContext*);

		void startRender(GELlyContext*);
		void stopRender(GELlyContext*);

		void startWindow(GELlyContext*, std::string, int x, int y, int width, int height, long flags);
		void endWindow(GELlyContext*);

		void drawLabel(GELlyContext*, std::string text);//TODO: Add more params and Finish
		bool drawButton(GELlyContext*, std::string label, glm::vec4 colour);
		bool drawToggleButton(GELlyContext*, std::string label);



}