#ifndef __GLUTPP_LIGHT_H__
#define __GLUTPP_LIGHT_H__

#include <GL/glew.h>
#include <GLFW/glfw3.h>


//#include <galaxy/flag.hpp>

#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>

//#include <neb/config.hh>
#include <neb/util/decl.hpp>


#include <neb/math/Serialization/GLM.hpp>

#include <neb/core/light/__base.hpp>
#include <neb/core/light/Util/Flag.hh>
#include <neb/core/light/Util/Types.hh>
#include <neb/core/light/Util/light_count.hpp>

#include <neb/typedef.hpp>

#include <neb/gfx/Color/Color.hh>

namespace neb {
	namespace Light {
		class base: virtual public neb::core::light::__base {
			public:
				base(sp::shared_ptr<neb::Light::util::parent> parent, ::std::string);
				
				void				init();
				
				virtual void			release();
				virtual void			cleanup();
				virtual void			step(gal::std::timestep const & ts);

				neb::core::pose			getPose();
				vec4				getPos();
			private:
				template<class Archive> void		serializeTemplate(Archive & ar, unsigned int const & version) {
					ar & boost::serialization::make_nvp("i",i_);
					ar & boost::serialization::make_nvp("flag",flag_);
					ar & boost::serialization::make_nvp("pos",pos_);
/*					ar & boost::serialization::make_nvp("atten_const",atten_const_);
					ar & boost::serialization::make_nvp("atten_linear",atten_linear_);
					ar & boost::serialization::make_nvp("atten_quad",atten_quad_);*/
				}
			public:
				virtual void				serialize(boost::archive::polymorphic_iarchive & ar, unsigned int const & version) {
					serializeTemplate(ar, version);
				}
				virtual void				serialize(boost::archive::polymorphic_oarchive & ar, unsigned int const & version) {
					serializeTemplate(ar, version);
				}
			public:
			
			
				sp::weak_ptr<neb::Light::util::parent>		parent_;

				sp::shared_ptr<neb::gfx::core::light::base>	light_gfx_;

				neb::Light::util::Flag				flag_;

				// position
				glm::vec3					pos_;


		};
	}
}

#endif
