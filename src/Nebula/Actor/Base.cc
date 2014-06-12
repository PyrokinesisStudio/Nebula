

#include <Nebula/debug.hh>

//#include <Nebula/Util/Typed.hh>

#include <Nebula/Types.hh>
#include <Nebula/config.hh> // Nebula/config.hpp.in
#include <Nebula/timer/Actor/Base.hpp>
//#include <Nebula/App/Base.hh>
#include <Nebula/Scene/Base.hh>
#include <Nebula/Signals.hh>

#include <Nebula/Actor/Base.hh>
#include <Nebula/Actor/RigidActor/Base.hh>
#include <Nebula/Actor/RigidBody/Base.hh>
#include <Nebula/Actor/Empty/Empty.hpp>
#include <Nebula/Actor/Util/Types.hh>

#include <Nebula/Filter.hh>
#include <Nebula/Graphics/Window/Base.hh>
#include <Nebula/Graphics/Types.hh>

/** @file Base
 */

neb::core::actor::Base::Base() {
}
neb::core::actor::Base::Base(sp::shared_ptr<neb::core::actor::Util::Parent> parent): parent_(parent) {
	NEBULA_ACTOR_BASE_FUNC;
}
neb::core::actor::Base::~Base() {
	NEBULA_ACTOR_BASE_FUNC;
}
void		neb::core::actor::Base::init() {
}
sp::shared_ptr<neb::core::actor::Util::Parent>	neb::core::actor::Base::getParent() {
	return parent_;
}
mat4				neb::core::actor::Base::getPose() {
	return pose_;
}
mat4				neb::core::actor::Base::getPoseGlobal() {
	NEBULA_ACTOR_BASE_FUNC;
	
	mat4 m;

	if(!parent_) {
		m = parent_->getPoseGlobal() * getPose();
	} else {
		m = getPose();
	}

	return m;
}
void		neb::core::actor::Base::setPose(mat4 pose) {
	pose_ = pose;
	
	flag_.set(neb::core::actor::Util::Flag::E::SHOULD_UPDATE);
}
void		neb::core::actor::Base::load_lights(int& i, mat4 space) {
	NEBULA_ACTOR_BASE_FUNC;

	space = space * pose_;
	
	typedef neb::core::actor::Util::Parent A;
	typedef neb::Shape::Util::Parent S;

	auto lambda_a = [&] (A::map_type::iterator<0> it) {
		
		auto actor = sp::dynamic_pointer_cast<neb::core::actor::Base>(it->ptr_);
		if(!actor) {
			::std::cout << "ptr   = " << it->ptr_ << " type= " << typeid(*it->ptr_).name() << ::std::endl;
			::std::cout << "actor = " << actor << ::std::endl;
			abort();
		}
		actor->load_lights(i, space);
	};

	auto lambda_s = [&]  (S::map_type::iterator<0> it) {
		auto shape = sp::dynamic_pointer_cast<neb::Shape::Base>(it->ptr_);
		assert(shape);
		shape->load_lights(i, space);
	};
	
	A::map_.for_each<0>(lambda_a);
	
	S::map_.for_each<0>(lambda_s);
}
void		neb::core::actor::Base::draw(sp::shared_ptr<neb::gfx::Context::Base> context, mat4 space) {
	NEBULA_ACTOR_BASE_FUNC;

	space = space * pose_;

	typedef neb::core::actor::Util::Parent A;
	typedef neb::Shape::Util::Parent S;

	A::map_.for_each<0>([&] (A::map_type::iterator<0> it) {
			auto actor = sp::dynamic_pointer_cast<neb::core::actor::Base>(it->ptr_);
			assert(actor);
			actor->draw(context, space);
			});

	S::map_.for_each<0>([&] (S::map_type::iterator<0> it) {
			auto shape = sp::dynamic_pointer_cast<neb::Shape::Base>(it->ptr_);
			assert(shape);
			shape->draw(context, space);
			});


}
/*void neb::core::actor::Base::init(neb::core::actor::desc_w desc) {
  NEBULA_ACTOR_BASE_FUNC;

  raw_.reset();
  raw_.swap(desc->raw_wrapper_.ptr_);


  create_physics();
  create_children(desc);
  create_shapes(desc);
  init_physics();
  }*/
void		neb::core::actor::Base::release() {

	neb::core::actor::Util::Parent::clear();
	neb::Shape::Util::Parent::clear();

	//conn_.key_fun_.disconnect();
}
void		neb::core::actor::Base::step(neb::core::TimeStep const & ts) {
	NEBULA_ACTOR_BASE_FUNC;

	typedef neb::core::actor::Util::Parent A;
	typedef neb::Shape::Util::Parent S;

	A::map_.for_each<0>([&] (A::map_type::iterator<0> it) {
			it->ptr_->step(ts);
			});

	S::map_.for_each<0>([&] (S::map_type::iterator<0> it) {
			it->ptr_->step(ts);
			});

}
void		neb::core::actor::Base::connect(sp::shared_ptr<neb::gfx::Window::Base> window) {

	//window_ = window;

	//auto me = std::dynamic_pointer_cast<neb::core::actor::Base>(shared_from_this());
	auto me = isActorBase();

	//auto shared = sharedBase();

	//conn_.key_fun_.reset(new neb::weak_function<int,int,int,int,int>(&neb::core::actor::Base::key_fun));

	assert(window);

	auto c = window->sig_.key_fun_.connect(
			neb::Signals::KeyFun::slot_type(
				&neb::core::actor::Base::key_fun,
				me.get(),
				_1,
				_2,
				_3,
				_4,
				_5
				).track_foreign(me)
			);

}
int neb::core::actor::Base::key_fun(sp::shared_ptr<neb::gfx::Window::Base> window, int key, int scancode, int action, int mods) {

	switch(action) {
		case GLFW_PRESS:
			switch(key) {
				case GLFW_KEY_SPACE:
					//fire();
					return 1;
				case GLFW_KEY_ESCAPE:
					parent_->erase(i_);
					return 1;
				default:
					return 0;
			}
		case GLFW_RELEASE:
			switch(key) {
				default:
					return 0;
			}
	}

	return 0;
}




