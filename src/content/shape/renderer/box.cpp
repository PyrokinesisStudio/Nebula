#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>

#include <jess/free.hpp>

#include <nebula/content/actor/admin/rigid_actor.hpp>
#include <nebula/content/shape/admin/box.hpp>


#include <nebula/platform/renderer/base.hpp>


#include <nebula/content/shape/renderer/box.hpp>

namespace bnu = boost::numeric::ublas;

namespace nca = nebula::content::actor;
namespace ncs = nebula::content::shape;
namespace ncsr = ncs::renderer;


#ifndef TEST_1
#error "header error!"
#endif

ncsr::box::box()
{

}
ncsr::box::~box()
{

}
void	ncsr::box::init(const boost::shared_ptr<ncs::admin::box>& parent)
{
	parent_ = parent;
}
void	ncsr::box::shutdown()
{
	
}
void	ncsr::box::render(const boost::shared_ptr<nebula::platform::renderer::base>& rnd)
{
	boost::shared_ptr<ncs::admin::box> parent = boost::dynamic_pointer_cast<ncs::admin::box>( parent_.lock() );
	
	jess::assertion( bool(rnd) ); // throw Except("renderer is null");
	
	
	jess::assertion( bool(parent) ); // throw Except("m_co_sh_ad_box is null");


	boost::shared_ptr<nca::admin::rigid_actor> grandparent = parent->parent_.lock();
	
	jess::assertion( bool(grandparent) ); // throw Except("m_co_sh_ad_box->Get_ncaa::rigid_actor() is null");
	
	// store transform
	bnu::matrix<FLOAT> pose = grandparent->get_pose();
	
	
	rnd->push_matrix();
	rnd->mult_matrix( pose );
	rnd->scale( parent->get_scale() );
	rnd->draw_cube();
	rnd->pop_matrix();
}










