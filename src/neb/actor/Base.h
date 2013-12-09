#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_BASE_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_BASE_HPP__

#include <GL/glut.h>

//#include <tinyxml/tinyxml.h>

#include <math/transform.h>

#include <PxPhysicsAPI.h>

namespace neb
{
	namespace actor
	{
		class Base
		{
			public:
				Base();
				virtual void		init() = 0;

				math::transform		pose_;
				
				GLuint			list_;
		};
	}
}


#endif







