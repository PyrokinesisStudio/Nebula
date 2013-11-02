#ifndef __NEBULA_CONTENT_ACTOR_RENDERER_RIGID_STATIC_HPP__
#define __NEBULA_CONTENT_ACTOR_RENDERER_RIGID_STATIC_HPP__


#include <nebula/content/actor/renderer/rigid_actor.hpp>


namespace nebula
{
	namespace content
	{
		namespace actor
		{
			namespace renderer
			{
				/// rigid static
				class rigid_static:
					public n34300::rigid_actor
				{
				public:
					/// ctor
					rigid_static( std::shared_ptr<n34100::base> );
					/// dtor
					~rigid_static();

					/// Initialize
					virtual	void						init();
					/// ShutDown
					virtual	void						shutdown();
					/// Update
					virtual	void						update();
					/// Render
					virtual	void						render( std::shared_ptr<n23000::base> );
					/// Step
					virtual	void						step( float );
				};
			}
		}
	}
}


#endif





