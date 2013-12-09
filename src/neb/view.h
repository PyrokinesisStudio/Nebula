#ifndef __NEB_VIEW_H__
#define __NEB_VIEW_H__

#include <memory>

#include <glutpp/gui/layout.h>

#include <glutpp/window.h>

namespace neb
{
	class view
	{
		public:
			View();
			void				delete_scene();
			void				Display();
			
			
			std::shared_ptr<NEB::Scene>	scene_;
			std::shared_ptr<GUL::layout>	layout_;

	};
}

#endif