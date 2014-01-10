#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_BODY_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_BODY_HPP__

#include <neb/actor/Rigid_Actor.h>

namespace neb
{
	namespace actor
	{
		class Rigid_Body:
			public neb::actor::Rigid_Actor
		{
			public:
				Rigid_Body(
						std::shared_ptr<neb::scene::scene>,
						neb::actor::Base_shared = neb::actor::Base_shared());
				
				virtual void			init(glutpp::actor::desc_shared);
				virtual void			add_force();
				virtual int			key_fun(int,int,int,int);

				virtual glutpp::actor::desc_shared	get_projectile();
				virtual glutpp::actor::desc_shared	get_desc();

				virtual void			step_remote(double);



				virtual void			create_physics() {abort();}
				
				
				float				density_;
				math::vec3			velocity_;
				math::vec3			force_;
				math::vec3			torque_;
		};
	}
}

#endif








