#include <math/transform.h>

#include <gal/network/server.h>

#include <neb/config.h>
#include <neb/app.h>
#include <neb/physics.h>
#include <neb/simulation_callback.h>
#include <neb/packet/packet.h>
#include <neb/actor/rigid_body/rigid_body.h>
#include <neb/actor/rigid_body/control.h>

neb::actor::rigid_body::rigid_body::rigid_body(
		std::shared_ptr<neb::scene::scene> scene,
		std::shared_ptr<neb::actor::Base> actor):
	neb::actor::Rigid_Actor(scene, actor),
	force_(0.0,0.0,0.0),
	torque_(0.0,0.0,0.0)
{}
void	neb::actor::rigid_body::rigid_body::init(glutpp::actor::desc_s desc) {
	NEBULA_DEBUG_0_FUNCTION;
	
	neb::actor::Rigid_Actor::init(desc);

}
void neb::actor::rigid_body::rigid_body::add_force(double time) {
	NEBULA_DEBUG_1_FUNCTION;
	
	math::vec3 f(force_);
	math::vec3 t(torque_);

	if(control_) {
		f += control_->f();
		t += control_->t(time);
	}

	math::transform pose = raw_.pose_;

	f = pose.q.rotate(f);
	t = pose.q.rotate(t);

	//printf("f = ");
	//f.print();
	//t.print();

	assert(px_actor_);
	physx::PxRigidBody* pxrigidbody = px_actor_->isRigidBody();
	assert(pxrigidbody);
	
	//printf("mass = %f\n", pxrigidbody->getMass());
	
	pxrigidbody->addForce(f);
	pxrigidbody->addTorque(t);

	print_info();
}
void	neb::actor::rigid_body::rigid_body::step_remote(double) {

	neb::packet::packet p;
	/*
	   p.type_ = neb::packet::ACTOR_FORCE;
	   p.af.i_ = i_;
	   p.af.f_[0] = force_.x;
	   p.af.f_[1] = force_.y;
	   p.af.f_[2] = force_.z;
	   p.af.t_[0] = torque_.x;
	   p.af.t_[1] = torque_.y;
	   p.af.t_[2] = torque_.z;
	 */
	gal::network::message::shared_t msg(new gal::network::message);

	msg->set(&p, sizeof(neb::packet::packet));

	get_app()->client_->write(msg);
}
glutpp::actor::desc_s neb::actor::rigid_body::rigid_body::get_projectile() {
	NEBULA_DEBUG_0_FUNCTION;

	glutpp::actor::desc_s desc(new glutpp::actor::desc);

	desc->get_raw()->type_ = glutpp::actor::RIGID_DYNAMIC;

	math::transform pose(raw_.pose_);

	math::vec3 velocity(0.0, 0.0, -10.0);
	velocity = pose.q.rotate(velocity);
	velocity += raw_.velocity_;

	desc->get_raw()->velocity_ = velocity;

	math::vec3 offset(0.0, 0.0, -2.0);
	offset = pose.q.rotate(offset);

	pose.p += offset;

	desc->get_raw()->pose_ = pose;


	desc->get_raw()->density_ = 1000.0;

	desc->get_raw()->filter_data_.simulation_.word0 = glutpp::filter::type::DYNAMIC;
	desc->get_raw()->filter_data_.simulation_.word1 = glutpp::filter::RIGID_AGAINST;
	desc->get_raw()->filter_data_.simulation_.word2 = glutpp::filter::type::PROJECTILE;
	desc->get_raw()->filter_data_.simulation_.word3 = glutpp::filter::PROJECTILE_AGAINST;

	// shape
	glutpp::shape::desc_s sd(new glutpp::shape::desc);

	sd->get_raw()->box(math::vec3(0.1,0.1,0.1));

	// material
	sd->get_raw()->front_.reset();
	sd->get_raw()->front_.ambient_.from_math(math::black);

	sd->get_raw()->front_.diffuse_.from_math(math::color::rand());

	sd->get_raw()->front_.emission_.from_math(math::black);

	desc->get_shapes()->vec_.push_back(std::make_tuple(sd));

	// light
	glutpp::light::desc_s ld(new glutpp::light::desc);

	ld->raw_.pos_.from_math(math::vec4(0.0, 0.0, 0.0, 1.0));
	ld->raw_.ambient_.from_math(math::black);
	ld->raw_.atten_linear_ = 2.0;

	sd->get_lights()->vec_.push_back(std::make_tuple(ld));

	//scene->create_light(ld, actor);

	return desc;
}
void neb::actor::rigid_body::rigid_body::print_info() {
	//NEBULA_DEBUG_0_FUNCTION;	
	
	neb::actor::Rigid_Actor::print_info();
	
	auto pxrb = px_actor_->isRigidBody();
	
	//math::transform pose		= pxrb->getCMassLocalPose();
	float mass			= pxrb->getMass();
	math::vec3 inertia		= pxrb->getMassSpaceInertiaTensor();
	math::vec3 linear_velocity	= pxrb->getLinearVelocity();
	math::vec3 angular_velocity	= pxrb->getAngularVelocity();
	
	
	printf("mass             = %f\n", mass);
	printf("interia          = "); inertia.print();
	printf("linear velocity  = "); linear_velocity.print();
	printf("angular velocity = "); angular_velocity.print();
	
}






