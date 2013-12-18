#ifndef __GLUTPP_MASTER_H__
#define __GLUTPP_MASTER_H__

#include <map>
#include <memory>

#include <gal/sig/signal.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <GLFW/glfw3.h>

typedef std::shared_ptr<gal::sig::connection<int,int,int> >	mouse_button_fun_c;
typedef std::shared_ptr<gal::sig::connection<double,double> >	cursor_pos_fun_c;
typedef std::shared_ptr<gal::sig::connection<int> >		cursor_enter_fun_c;
typedef std::shared_ptr<gal::sig::connection<double,double> >	scroll_fun_c;
typedef std::shared_ptr<gal::sig::connection<int,int,int,int> >	key_fun_c;
typedef std::shared_ptr<gal::sig::connection<unsigned int> >	char_fun_c;

namespace glutpp
{
	struct program_name
	{
		enum e
		{
			NONE = 0,
			TEXT,
			QUAD,
			LIGHT
		};
	};
	struct attrib_name
	{
		enum e
		{
			NONE = 0,
			POSITION,
			NORMAL,
			TEXCOOR,
			COOR
		};
	};
	struct uniform_name
	{
		enum e
		{
			UNIFORM_NONE = 0,
			COLOR,
			TEX,
			LIGHT_COUNT,
			MODEL,
			VIEW,
			PROJ,
			IMAGE,
			LIGHT_POSITION,
			LIGHT_AMBIENT,
			LIGHT_DIFFUSE,
			LIGHT_SPECULAR,
			LIGHT_SPOT_DIRECTION,
			LIGHT_SPOT_CUTOFF,
			LIGHT_SPOT_EXPONENT,
			LIGHT_SPOT_LIGHT_COS_CUTOFF,
			LIGHT_ATTEN_CONST,
			LIGHT_ATTEN_LINEAR,
			LIGHT_ATTEN_QUAD,
			FRONT_AMBIENT,
			FRONT_DIFFUSE,
			FRONT_SPECULAR,
			FRONT_EMISSION,
			FRONT_SHININESS,
		};
	};

	namespace glsl
	{
		class program;
	}
	class window;
	class master
	{
		private:

			static void static_window_pos_fun(GLFWwindow*,int,int);
			static void static_window_size_fun(GLFWwindow*,int,int);
			static void static_window_close_fun(GLFWwindow*);
			static void static_window_refresh_fun(GLFWwindow*);
			//static void static_window_focus_fun(GLFWwindow*,int);
			//static void static_window_iconify_fun(GLFWwindow*,int);
			//static void static_window_buffer_size_fun(GLFWwindow*,int,int);

			static void static_mouse_button_fun(GLFWwindow*,int,int,int);
			static void static_key_fun(GLFWwindow*,int,int,int,int);


		public:
			std::shared_ptr<glutpp::glsl::program>		use_program(glutpp::program_name::e);
			std::shared_ptr<glutpp::glsl::program>		get_program(glutpp::program_name::e);
			std::shared_ptr<glutpp::glsl::program>		current_program();
			int						create_programs();



		public:

			master();
			~master();

			glutpp::window*	get_window(GLFWwindow*);
			void		reg(glutpp::window*);



			//void  CallGlutCreateWindow(char * setTitle, glutpp::window * glutWindow);
			//void  CallGlutMainLoop(void);

			//void  DisableIdleFunction(void);
			//void  EnableIdleFunction(void);
			//int   IdleFunctionEnabled(void);

			//int   IdleSetToCurrentWindow(void);
			//void  SetIdleToCurrentWindow(void);
			FT_Library				ft_;

		private:
			GLFWwindow*				currentIdleWindow_;
			std::map<GLFWwindow*,glutpp::window*>	windows_;


			std::map<int, std::shared_ptr<glutpp::glsl::program> >	programs_;
			std::shared_ptr<glutpp::glsl::program>			current_;
	};

	extern "C" master __master;
}


#endif




