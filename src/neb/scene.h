#ifndef _NEBULA_CONTENT_SCENE_PHYSICS_BASE_HPP__
#define _NEBULA_CONTENT_SCENE_PHYSICS_BASE_HPP__

#include <memory>
#include <vector>

#include <PxPhysicsAPI.h>

#include <gal/map.h>

#include <glutpp/scene.h>

#include <neb/actor/Rigid_Dynamic.h>
#include <neb/actor/Rigid_Static.h>
#include <neb/actor/Controller.h>
#include <neb/actor/Light.h>

#include <tinyxml/tinyxml.h>

int		parse_shape_type(char const * str);
neb::shape*	xml_parse_geo(TiXmlElement* element);

namespace neb
{
	namespace actor
	{
		struct desc;
	}
	class view;
	class scene: public glutpp::scene
	{
		public:
			enum
			{
				NONE = 0,
				LOCAL,
				REMOTE
			};
			scene();
			void		Create_Actors(TiXmlElement*);
			void		Create_Actor(TiXmlElement*);


			std::shared_ptr<neb::actor::Rigid_Dynamic>	Create_Rigid_Dynamic(TiXmlElement*);
			std::shared_ptr<neb::actor::Rigid_Static>	Create_Rigid_Static(TiXmlElement*);
			std::shared_ptr<neb::actor::Rigid_Static>	Create_Rigid_Static_Plane(TiXmlElement*);
			std::shared_ptr<neb::actor::Rigid_Dynamic>	Create_Rigid_Dynamic(neb::actor::desc);
			std::shared_ptr<neb::actor::Rigid_Static>	Create_Rigid_Static(neb::actor::desc);

			std::shared_ptr<neb::actor::Controller>		Create_Controller(TiXmlElement*);
			std::shared_ptr<neb::actor::Light>		Create_Light(TiXmlElement*);

			void						draw();

			void						step(double);
			void						step_local(double);
			void						step_remote(double);


			int						user_type_;

			physx::PxSimulationFilterShader			px_filter_shader_;
			
			//gal::map<neb::actor::Base>			actors_;
			//std::vector<neb::actor::Light*>			lights_;
			
			physx::PxScene*					px_scene_;
			
			std::weak_ptr<neb::app>				app_;
			std::weak_ptr<neb::view>			view_;
			double						last_;
	};
}

#endif



