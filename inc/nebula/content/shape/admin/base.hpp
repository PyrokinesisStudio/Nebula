#ifndef __NEBULA_CONTENT_SHAPE_ADMIN_BASE_HPP__
#define __NEBULA_CONTENT_SHAPE_ADMIN_BASE_HPP__

#include <nebula/define.hpp>
#include <PxPhysicsAPI.h>

#include <jess/shared_ptr.hpp>

#include <nebula/ns.hpp>

namespace nebula
{
	namespace content
	{
		namespace shape
		{
			namespace admin
			{
				/// base	
				class base:
					public jess::enable_shared_from_this<n35100::base>
				{
					public:
						/// ctor	
						base();
						/// dtor					
						virtual ~base();
						/// init
						virtual void							init( jess::shared_ptr<nebula::content::actor::admin::rigid_actor> );
						/// shutdown
						virtual void							shutdown();
						/// render
						virtual void							render( jess::shared_ptr<nebula::platform::renderer::base> );
						/// get scale
						physx::PxVec3							get_scale();
						/// parent
						std::weak_ptr<nebula::content::actor::admin::rigid_actor>	parent_;
						/// renderer
						jess::shared_ptr<nebula::content::shape::renderer::base>	renderer_;
						/// physics
						jess::shared_ptr<nebula::content::shape::physics::base>		physics_;
						/// scale
						physx::PxVec3							scale_;
				};
			}
		}
	}
}


#endif
