#include <Nebula/app/Base.hh>

#include <Nebula/core/actor/RigidBody/Remote.hh>

void		neb::core::actor::rigidbody::remote::step(gal::std::timestep const & ts) {
	neb::core::actor::rigidactor::remote::step(ts);
	neb::core::actor::rigidbody::base::step(ts);
}




