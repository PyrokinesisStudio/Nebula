#include <neb/actor/rigid_body/control.h>

neb::actor::rigid_body::control::control():
	q_target_(math::quat(0.0 * M_PI,math::vec3(1.0,0.0,0.0)))
{

}
int neb::actor::rigid_body::control::key_fun(int key, int scancode, int action, int mods) {
	NEBULA_DEBUG_0_FUNCTION;


	switch(type_) {
		case neb::actor::rigid_body::control_type::T0:
			return key_fun0(key, action);
		case neb::actor::rigid_body::control_type::T1:
			return key_fun1(key, action);
		default:
			break;
	}

	return 0;
}
int neb::actor::rigid_body::control::key_fun0(int key, int action) {
	NEBULA_DEBUG_0_FUNCTION;

	float force_scale = 100000.0;
	float torque_scale = 5.0;


	math::vec3 x(1.0,0.0,0.0);
	math::vec3 y(0.0,1.0,0.0);
	math::vec3 z(0.0,0.0,1.0);

	switch(action)
	{
		case GLFW_PRESS:
			switch(key)
			{
				case GLFW_KEY_D:
					force_ += x * force_scale;
					return 1;
				case GLFW_KEY_A:
					force_ -= x * force_scale;
					return 1;
				case GLFW_KEY_E:
					force_ += y * force_scale;
					return 1;
				case GLFW_KEY_Q:
					force_ -= y * force_scale;
					return 1;
				case GLFW_KEY_W:
					force_ -= z * force_scale;
					return 1;
				case GLFW_KEY_S:
					force_ += z * force_scale;
					return 1;
				case GLFW_KEY_I:
					torque_ += x * torque_scale;
					return 1;
				case GLFW_KEY_K:
					torque_ -= x * torque_scale;
					return 1;
				case GLFW_KEY_L:
					torque_ -= y * torque_scale;
					return 1;
				case GLFW_KEY_J:
					torque_ += y * torque_scale;
					return 1;
				case GLFW_KEY_O:
					torque_ -= z * torque_scale;
					return 1;
				case GLFW_KEY_U:
					torque_ += z * torque_scale;
					return 1;
				default:
					return 0;
			}
		case GLFW_RELEASE:
			switch(key)
			{
				case GLFW_KEY_D:
					force_ -= x * force_scale;
					return 1;
				case GLFW_KEY_A:
					force_ += x * force_scale;
					return 1;
				case GLFW_KEY_E:
					force_ -= y * force_scale;
					return 1;
				case GLFW_KEY_Q:
					force_ += y * force_scale;
					return 1;
				case GLFW_KEY_W:
					force_ += z * force_scale;
					return 1;
				case GLFW_KEY_S:
					force_ -= z * force_scale;
					return 1;
				case GLFW_KEY_I:
					torque_ -= x * torque_scale;
					return 1;
				case GLFW_KEY_K:
					torque_ += x * torque_scale;
					return 1;
				case GLFW_KEY_L:
					torque_ += y * torque_scale;
					return 1;
				case GLFW_KEY_J:
					torque_ -= y * torque_scale;
					return 1;
				case GLFW_KEY_O:
					torque_ += z * torque_scale;
					return 1;
				case GLFW_KEY_U:
					torque_ -= z * torque_scale;
					return 1;
				default:
					return 0;
			}
	}


	return 0;
}
int neb::actor::rigid_body::control::key_fun1(int key, int action) {
	NEBULA_DEBUG_0_FUNCTION;

	math::vec3 dp;
	math::vec3 dq;

	float p_scale = 1.0;
	float q_scale = 0.5;

	math::vec3 x(1.0,0.0,0.0);
	math::vec3 y(0.0,1.0,0.0);
	math::vec3 z(0.0,0.0,1.0);
	
	//printf("%i %i\n", key, action);
	
	switch(action)
	{
		case GLFW_PRESS:
			switch(key)
			{
				case GLFW_KEY_D:
					dp += x;
					break;
				case GLFW_KEY_A:
					dp -= x;
					break;
				case GLFW_KEY_E:
					dp += y;
					break;
				case GLFW_KEY_Q:
					dp -= y;
					break;
				case GLFW_KEY_W:
					dp -= z;
					break;
				case GLFW_KEY_S:
					dp += z;
					break;
				case GLFW_KEY_I:
					dq += x;
					break;
				case GLFW_KEY_K:
					dq -= x;
					break;
				case GLFW_KEY_L:
					dq -= y;
					break;
				case GLFW_KEY_J:
					dq += y;
					break;
				case GLFW_KEY_O:
					dq -= z;
					break;
				case GLFW_KEY_U:
					dq += z;
					break;
				default:
					return 0;
			}
			break;
		case GLFW_RELEASE:
			switch(key)
			{
				case GLFW_KEY_D:
					dp -= x;
					break;
				case GLFW_KEY_A:
					dp += x;
					break;
				case GLFW_KEY_E:
					dp -= y;
					break;
				case GLFW_KEY_Q:
					dp += y;
					break;
				case GLFW_KEY_W:
					dp += z;
					break;
				case GLFW_KEY_S:
					dp -= z;
					break;
				case GLFW_KEY_I:
					dq -= x;
					break;
				case GLFW_KEY_K:
					dq += x;
					break;
				case GLFW_KEY_L:
					dq += y;
					break;
				case GLFW_KEY_J:
					dq -= y;
					break;
				case GLFW_KEY_O:
					dq += z;
					break;
				case GLFW_KEY_U:
					dq -= z;
					break;
				default:
					return 0;
			}
			break;
		default:
			return 0;
	}

	//printf("dq=\n");
	//dq.print();

	if(dq.magnitude() == 0.0f)
	{
		//printf("no key\n");
	}
	else
	{
		math::quat rot(q_scale, dq);

		q_target_ *= rot;

		printf("q_target_=\n");
		q_target_.print();


		p_target_ += dq * p_scale;


		//printf("p_target_=\n");
		//p_target_.print();
	}

	return 0;
}
math::vec3 neb::actor::rigid_body::control::f() {
	printf("force_ =\n");
	force_.print();
	return force_;
}
math::vec3 neb::actor::rigid_body::control::t(double time) {
	NEBULA_DEBUG_0_FUNCTION;

	switch(type_) {
		case neb::actor::rigid_body::control_type::T0:
			return t0();
		case neb::actor::rigid_body::control_type::T1:
			return t1(time);
		default:
			break;
	}

	return math::vec3();
}
math::vec3 neb::actor::rigid_body::control::t0() {
	NEBULA_DEBUG_1_FUNCTION;

	return torque_;
}
math::vec3 neb::actor::rigid_body::control::t1(double time) {
	NEBULA_DEBUG_1_FUNCTION;
	
	assert(!actor_.expired());
	auto actor = std::dynamic_pointer_cast<neb::actor::Actor>(actor_.lock());
	
	auto pxrigidbody = actor->px_actor_->isRigidBody();
	
	math::vec3 I = pxrigidbody->getMassSpaceInertiaTensor();
	
	// todo: make m dependent on direction of rotation
	float m = I.dot(math::vec3(1.0,0.0,0.0));
	
	float k = 10.0;
	float c = -2.0f * sqrt(m * k);
	pid_.coeff_p_ = k;
	pid_.coeff_d_ = c;
	
	
	
	
	
	math::quat q = actor->raw_.pose_.q;

	math::quat rot = q * q_target_.getConjugate();
	if(rot.magnitude() > 0)
	{
		float theta = -2.0 * acos(rot.w);
		
		theta = (theta > M_PI) ? (theta - 360.f) : theta;
		
		math::vec3 t(rot.x, rot.y, rot.z);
		t.normalize();

		// make sure getlinearvelocity is in actor-space
		math::vec3 vel = pxrigidbody->getAngularVelocity();
		float v = vel.dot(t);
		
		
				
		//q.print();
		//q_target_.print();


		//apply extra damping torque in all directions
		math::vec3 te = vel * 1.f * c;
		
		
		float fs = pid_.f(theta, v);
		t *= fs;
		
		//printf("theta = %f v = %f fs = %f\n", theta, v, fs);
		
		//printf("torque=\n");
		//t.print();
		
		return t + te;
	}

	return math::vec3();
}











