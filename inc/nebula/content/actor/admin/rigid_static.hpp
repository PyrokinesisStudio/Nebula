#ifndef __NEBULA_CONTENT_ACTOR_ADMIN_RIGID_STATIC_HPP__
#define __NEBULA_CONTENT_ACTOR_ADMIN_RIGID_STATIC_HPP__


#include <nebula/content/actor/admin/rigid_actor.hpp>


namespace nebula
{
	namespace content
	{
		namespace actor
		{
			namespace admin
			{
				/// rigid static
				class rigid_static:
					public nebula::content::actor::admin::rigid_actor
				{
				public:
					/// ctor
					rigid_static();
					/// dtor
					~rigid_static();

					/// Initialize
					virtual	void						init( jess::shared_ptr<n32100::base> );
					/// ShutDown
					virtual	void						shutdown();
					/// Update
					virtual	void						update();
					/// Render
					virtual	void						render( jess::shared_ptr<nebula::platform::renderer::base> );
					/// Step
					virtual	void						step(float);
					



					/// Create Shapes
					virtual	void						VCreateShape();


				};
			}
		}
	}
}


#endif





