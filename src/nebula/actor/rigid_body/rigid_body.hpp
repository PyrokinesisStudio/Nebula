#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_BODY_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_BODY_HPP__


#include <nebula/actor/Rigid_Actor.hpp>

namespace neb {
	namespace Actor {
		namespace RigidBody {
			class RigidBody:
				public neb::Actor::RigidActor
			{
				public:
					RigidBody(boost::shared_ptr<glutpp::actor::parent>);
					
					virtual void			init(boost::shared_ptr<glutpp::actor::desc>);
					
					
					
					virtual boost::shared_ptr<glutpp::actor::desc>	get_projectile();
					
				private:
					virtual void			step_local(double);
					virtual void			step_remote(double);

					virtual void			add_force(double);
				public:
					virtual void			print_info();


					virtual void			create_physics() {abort();}
					
					// control
					virtual void			create_control(
							neb::control::rigid_body::raw_s);
				public:
					neb::control::rigid_body::control_s	control_;
				private:
					physx::PxVec3			force_;
					physx::PxVec3			torque_;
			};
		}
	}
}

#endif







