#include <nebula/framework/app.hpp>

#include <nebula/content/base.hpp>
#include <nebula/content/physics/base.hpp>
#include <nebula/content/actor/admin/rigid_actor.hpp>
#include <nebula/content/shape/admin/box.hpp>

#include <nebula/content/actor/renderer/rigid_actor.hpp>

n34300::rigid_actor::rigid_actor( std::shared_ptr<n34100::base> parent ):
	n34300::base( parent ),
	n34300::actor( parent )
{

}
n34300::rigid_actor::~rigid_actor()
{

}
void	n34300::rigid_actor::init()
{
	n34300::actor::init();
}
void	n34300::rigid_actor::shutdown()
{
}
void	n34300::rigid_actor::update()
{
}
void	n34300::rigid_actor::render( std::shared_ptr<n23000::base> rnd )
{
	std::shared_ptr<n34100::rigid_actor> parent = std::dynamic_pointer_cast<n34100::rigid_actor>( parent_.lock() );

	NEB_ASSERT( parent );

	parent->shapes_.foreach( std::bind( &n35100::base::render, std::placeholders::_1, rnd ) );
}
void	n34300::rigid_actor::step( float dt )
{

}
void	n34300::rigid_actor::create_shapes()
{

}

