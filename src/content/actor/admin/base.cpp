#include <nebula/define.hpp>

#include <nebula/content/scene/admin/base.hpp>
#include <nebula/content/actor/physics/base.hpp>
#include <nebula/content/actor/renderer/base.hpp>

#include <nebula/content/actor/admin/base.hpp>

n34100::base::base()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;
	
	
	//pose_ = bnu::identity_matrix<float>( 4, 4 );
	//velocity_ = bnu::zero_vector<float>( 3 );
}
n34100::base::~base()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

}
n34100::base::base( const n34100::base& act )
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

}
n34100::base&	n34100::base::operator=( const n34100::base& act )
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

	return *this;
}
void	n34100::base::init( jess::shared_ptr<n32100::base> parent )
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

	parent_ = parent;
}
void	n34100::base::shutdown()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;
}
void	n34100::base::update()
{
	//FR_COM_IComm::Update();
}
void	n34100::base::render( jess::shared_ptr<n23000::base> rnd )
{
	jess::clog << NEB_FUNCSIG << std::endl;
}
void	n34100::base::step( float dt )
{
	jess::clog << NEB_FUNCSIG << std::endl;

	physics_->step( dt );
	renderer_->step( dt );
}
void	n34100::base::create_shapes()
{
	
}
physx::PxMat44	n34100::base::get_pose()
{
	return pose_;
}
void	n34100::base::set_pose( physx::PxMat44 pose )
{
	pose_ = pose;
}
jess::shared_ptr<n34200::material>	n34100::base::create_physics_material()
{
	return parent_.lock()->request_physics_material();
}












