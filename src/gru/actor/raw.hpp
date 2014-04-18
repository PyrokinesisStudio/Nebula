#ifndef __GLUTPP_ACTOR_RAW_H__
#define __GLUTPP_ACTOR_RAW_H__

#include <math/transform.h>
#include <math/raw/raw.h>


#include <gal/network/serial.h>
#include <gal/util.h>

#include <gru/config.hpp>
#include <gru/shape/desc.hpp>

template void gal::reset<glutpp::actor::raw>(glutpp::actor::raw_s&);

namespace glutpp {
	namespace actor {
		struct filter_data {
			unsigned int word0;
			unsigned int word1;
			unsigned int word2;
			unsigned int word3;
		};
		class raw: public gal::network::serial<glutpp::actor::raw, gal::network::base> {
			public:
				friend class glutpp::actor::raw_factory;
				friend void gal::reset<glutpp::actor::raw>(std::shared_ptr<raw>&);

				enum
				{
					max_name_length = 31
				};

			protected:
				raw();
			public:
				virtual void		load(tinyxml2::XMLElement*);
				virtual void		load(glutpp::actor::actor_s);
				
				void			plane(tinyxml2::XMLElement*);
				void			controller(tinyxml2::XMLElement*);

				unsigned int		parse_filter(tinyxml2::XMLElement*, unsigned int);
				void			parse_filtering(tinyxml2::XMLElement*);


				glutpp::actor::type::e		type_;
				glutpp::actor::mode_create::e	mode_create_;
				unsigned int			flag_;
				char				name_[32];

				math::transform		pose_;

				math::vec3		n_;
				float			d_;

				math::vec3		velocity_;
				float			density_;

				struct {
					filter_data	simulation_;
					filter_data	scene_query_;
				} filter_data_;
		};
	}
}

#endif








