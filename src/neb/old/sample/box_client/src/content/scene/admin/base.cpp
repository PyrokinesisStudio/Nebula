#include <nebula/content/view/admin/human/base.hpp>
#include <nebula/content/actor/admin/rigid_dynamic_box.hpp>
#include <nebula/content/actor/admin/rigid_static_plane.hpp>
#include <nebula/content/actor/admin/controller.hpp>
#include <nebula/content/camera.hpp>

#include <box_client/content/view/admin/base.hpp>

#include <box_client/content/scene/admin/base.hpp>

bc32100::base::base():
	n32100::base()
{
	NEB_LOG_FUNC;	
}
bc32100::base::~base()
{
	
}
void	bc32100::base::init()
{
	jess::clog << NEB_FUNCSIG << std::endl;

	n32100::base::init();


	//rigid_dyn_box_ = create_rigid_dynamic_box();



	//rigid_sta_pln_ = create_rigid_static_plane();



	//ctrlr_ = create_controller();
	
	
	// done in main now...
	//view_ = create_view<bc33100::base>();

	std::shared_ptr<ker::module::desc> desc_view( new ker::module::desc() );
	
	desc_view->type_		= ker::module::type( box_client::kernel::module::type::BC33100_BASE );
	desc_view->mode_		= ker::module::mode::CREATE;
	desc_view->desc_parent_		= shared_from_this();
	
	view_ = std::dynamic_pointer_cast<bc33100::base>( k->request_module( desc_view ) );



	// connect controller to view
	//connect_controller_to_view( ctrlr_, view_ );

}

