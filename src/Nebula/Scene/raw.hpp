#ifndef __GLUTPP_SCENE_RAW_H__
#define __GLUTPP_SCENE_RAW_H__

#include <tinyxml2.h>

//#include <galaxy/network/message.hpp>
//#include <galaxy/network/serial.hpp>

#include <boost/serialization/nvp.hpp>

#include <PxPhysicsAPI.h>

//#include <math/vec3.hpp>

#include <Nebula/Types.hpp>
#include <Nebula/config.hpp> // Nebula/config.hpp.in
//#include <Nebula/actor/desc.hpp>

namespace Neb {
	namespace Scene {
		namespace Util {
			class Raw {
				public:
					Raw();
					//void					load(tinyxml2::XMLElement*);
					void					load(Neb::Scene::Base_w scene);

					template <class Archive> void		serialize(Archive & ar, unsigned int const & version) {
						ar & boost::serialization::make_nvp("flag",flag_);
						ar & boost::serialization::make_nvp("gravity",gravity_);
					}

					unsigned int		flag_;
					physx::PxVec3		gravity_;
			};
		}
	}
}

#endif






