#ifndef __NEBULA_CONTENT_SCENE_PHYSICS_PHYSX_BASE_HPP__
#define __NEBULA_CONTENT_SCENE_PHYSICS_PHYSX_BASE_HPP__

#include <boost/shared_ptr.hpp>

#include <PxPhysicsAPI.h>

#include <nebula/utilities/types/content/actor/types.hpp>

#include <nebula/ns.hpp>

namespace nebula
{
	namespace content
	{
		namespace scene
		{
			namespace physics
			{
				namespace physx
				{
					class base
					{
					public:
						base();
						virtual ~base();
						base(const base&);
						base&									operator=(const base&);
						void									init(const boost::shared_ptr<nc_sc_a::base>&);
						void									shutdown();
						void									step(FLOAT);


						void									customize_scene_desc(::physx::PxSceneDesc&);
						void									add_actor(const boost::shared_ptr<ncaa::actor>& act);
						
						
						::physx::PxScene*							px_scene_;

					};
				}
			}
		}
	}
}

#endif