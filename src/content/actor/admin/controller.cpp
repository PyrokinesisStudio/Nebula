#include <boost/numeric/ublas/io.hpp>

#include <nebula/define.hpp>

#include <nebula/utilities/free.hpp>

#include <nebula/platform/renderer/base.hpp>
#include <nebula/platform/key.hpp>
#include <nebula/platform/window/base.hpp>

#include <nebula/content/actor/physics/controller.hpp>
#include <nebula/content/actor/renderer/controller.hpp>


#include <nebula/content/actor/admin/controller.hpp>

n34100::controller::controller()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;
}
n34100::controller::~controller()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;
}
n34100::controller::controller( n34100::controller const & act )
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;
}
void	n34100::controller::init( jess::shared_ptr<n32100::base> parent )
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;
	
	// init parent
	n34100::base::init( parent );
	
	flag_ = 0;
	
	yaw_ = 0;
	pitch_ = 0;
	
	pos_ = physx::PxVec3(0,10,2);
	
	key_flag_[nebula::platform::key::w] = flag::eNORTH;
	key_flag_[nebula::platform::key::s] = flag::eSOUTH;
	key_flag_[nebula::platform::key::a] = flag::eWEST;
	key_flag_[nebula::platform::key::d] = flag::eEAST;
	
	key_down_event_[nebula::platform::key::r] = event::eRESET_VIEW_ANGLES;

	jess::shared_ptr<n34100::base> this_ptr( shared_from_this() );
	
	//jess::cout << "not reached" << std::endl;
	
	// physics
	physics_.reset( new n34200::controller );
	physics_->init( this_ptr );
	
	// renderer
	renderer_.reset( new n34300::controller );
	renderer_->init( this_ptr );	
}
void	n34100::controller::shutdown()
{
	jess::clog << NEB_FUNCSIG << std::endl;
}
void	n34100::controller::update()
{
	n34100::base::update();
}
void	n34100::controller::step( float dt )
{
	n34100::base::step( dt );
}
void	n34100::controller::render( jess::shared_ptr<n23000::base> rnd )
{
}
void	n34100::controller::create_shapes()
{

}
void	n34100::controller::look_at( jess::shared_ptr<n23000::base> rnd )
{
	jess::clog << NEB_FUNCSIG << std::endl;

	physx::PxQuat rot( yaw_, physx::PxVec3(0,1,0) );
	
	//jess::clog << pitch_ << " " << yaw_ << std::endl;
	//std::cout << "rot=" << rot << std::endl;
	
	//std::cout << "rot=" << rot << std::endl;

	rot *= physx::PxQuat( pitch_ , physx::PxVec3(1,0,0) );

	//std::cout << "rot=" << rot << std::endl;
	
	//rnd->mult_matrix( pose_ );
	
	//bnu::  math::quaternion rot(0,0,0,1);
	
	//boost::math::quaternion	yaw( 0, 1, 0, yaw_ );
	//boost::math::quaternion pitch( 1, 0, 0, pitch_ );
	
	//rot *= pitch;
	//rot *= yaw;
	
	up_ = physx::PxVec3(0,1,0);
	look_ = physx::PxVec3(0,0,-1);
	
	//jess::clog << up_ << std::endl;
	//jess::clog << look_ << std::endl;
	
	up_ = rot.rotate( up_ );
	look_ = rot.rotate( look_ );
	
	//jess::clog << up_ << std::endl;
	//jess::clog << look_ << std::endl;
	//jess::clog << pos_ + look_ << std::endl;
	
	rnd->look_at( pos_, pos_ + look_, up_ );
}
void	n34100::controller::process_event( int evnt )
{
	switch ( evnt )
	{
	case event::eRESET_VIEW_ANGLES:
		printf("reset viewing angles\n");
		yaw_ = 0;
		pitch_ = 0;
		break;
	}
}
void	n34100::controller::handle_key_up(int k, int window_no)
{

	jess::clog << NEB_FUNCSIG << std::endl;

	// unset flag
	UINT f = key_flag_[k];
	flag_ &= ~( f );
	
	// trigger event
	int evnt = key_up_event_[k];
	process_event(evnt);

}
void	n34100::controller::handle_key_down(int k, int window_no)
{

	jess::clog << NEB_FUNCSIG << std::endl;
	
	// set flag
	UINT f = key_flag_[k];
	flag_ |= f;
	
	// trigger event
	int evnt = key_down_event_[k];
	process_event(evnt);
}
void	n34100::controller::handle_pointer_motion( int x, int y )
{
	jess::clog << NEB_FUNCSIG << std::endl;
	
	yaw_ -= x * 0.001;
	pitch_ -= y * 0.001;
}

























