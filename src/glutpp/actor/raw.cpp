#include <math/free.h>

#include <glutpp/actor/raw.h>

glutpp::actor::raw::raw():
	type_(glutpp::actor::type::NONE),
	mode_create_(glutpp::actor::mode_create::e::NOW),
	flag_(0),
	density_(200)
{
	memset(name_, 0, max_name_length + 1);
}
void glutpp::actor::raw::load(tinyxml2::XMLElement* element) {
	GLUTPP_DEBUG_0_FUNCTION;
	
	// xml
	assert(element);
	
	// type
	const char* buf = element->Attribute("type");
	assert(buf);
	if( strcmp(buf, "rigid_dynamic") == 0)
	{
		type_ = glutpp::actor::RIGID_DYNAMIC;
	}
	else if( strcmp(buf, "rigid_static") == 0)
	{
		type_ = glutpp::actor::RIGID_STATIC;
	}	
	else if( strcmp(buf, "plane") == 0)
	{
		type_ = glutpp::actor::PLANE;
	}	
	else if(strcmp(buf, "controller") == 0)
	{
		type_ = glutpp::actor::CONTROLLER;
	}
	else if(strcmp(buf, "empty") == 0)
	{
		type_ = glutpp::actor::EMPTY;
	}
	else
	{
		printf("unknown actor type\n");
		abort();
	}
	
	// mode create
	buf = element->Attribute("mode_create");
	if(buf != NULL)
	{
		if(strcmp(buf, "deferred") == 0)
		{
			printf("DEFERRED\n");
			mode_create_ = glutpp::actor::mode_create::e::DEFERRED;
		}
		else if(strcmp(buf, "now") == 0)
		{
			printf("NOW\n");
			mode_create_ = glutpp::actor::mode_create::e::NOW;
		}
		else
		{
			printf("invalid mode\n");
			abort();
		}
	}
	
	// name
	buf = element->Attribute("name");
	if(buf != NULL)
	{
		int len = std::min(strlen(buf), (size_t)max_name_length);
		
		memcpy(name_, buf, len);
		name_[len] = 0;
	}
	
	// pose
	pose_ = math::xml_parse_transform(
			element->FirstChildElement("pose"),
			math::transform(math::vec3(0,0,0), math::quat(0.0, math::vec3(1.0,0.0,0.0))));
	
	// velocity
	velocity_ = math::xml_parse_vec3(element->FirstChildElement("velocity"), velocity_);
	
	// filtering
	parse_filtering(element);
}
void glutpp::actor::raw::parse_filtering(tinyxml2::XMLElement* element) {

	tinyxml2::XMLElement* fd = element->FirstChildElement("fd");
	tinyxml2::XMLElement* sim = NULL;
	tinyxml2::XMLElement* qry = NULL;
	
	if(fd)
	{
		sim = fd->FirstChildElement("sim");
		if(sim)
		{
			filter_data_.simulation_.word0 = parse_filter(sim->FirstChildElement("w0"), 0);
			filter_data_.simulation_.word1 = parse_filter(sim->FirstChildElement("w1"), 0);
			filter_data_.simulation_.word2 = parse_filter(sim->FirstChildElement("w2"), 0);
			filter_data_.simulation_.word3 = parse_filter(sim->FirstChildElement("w3"), 0);
		}
		
		qry = fd->FirstChildElement("qry");
		if(sim)
		{
			filter_data_.scene_query_.word0 = parse_filter(sim->FirstChildElement("w0"), 0);
			filter_data_.scene_query_.word1 = parse_filter(sim->FirstChildElement("w1"), 0);
			filter_data_.scene_query_.word2 = parse_filter(sim->FirstChildElement("w2"), 0);
			filter_data_.scene_query_.word3 = parse_filter(sim->FirstChildElement("w3"), 0);
		}
	}


}
unsigned int glutpp::actor::raw::parse_filter(tinyxml2::XMLElement* element, unsigned int i) {

	if(element == NULL) return i;

	char const * buf = element->GetText();

	if(strcmp(buf, "STATIC") == 0)
	{
		return glutpp::filter::type::STATIC;
	}
	else if(strcmp(buf, "DYNAMIC") == 0)
	{
		return glutpp::filter::type::DYNAMIC;
	}
	else if(strcmp(buf, "RIGID_AGAINST") == 0)
	{
		return glutpp::filter::RIGID_AGAINST;
	}
	else if(strcmp(buf, "PROJECTILE") == 0)
	{
		return glutpp::filter::type::PROJECTILE;
	}
	else if(strcmp(buf, "PROJECTILE_AGAINST") == 0)
	{
		return glutpp::filter::PROJECTILE_AGAINST;
	}
	
	
	
	abort();
}
void glutpp::actor::raw::plane(tinyxml2::XMLElement* element) {

	printf("%s\n", __PRETTY_FUNCTION__);


	// xml
	math::vec3 n = math::xml_parse_vec3(element->FirstChildElement("n"), math::vec3(0,1,0));
	n.normalize();

	float d = math::xml_parse_float(element->FirstChildElement("d"));


	math::quat q(3.14f, math::vec3(1,0,0));

	math::transform pose(n * -1.0f * d, q);

	n_ = n;
	d_ = d;

	pose_ = pose;
}
void glutpp::actor::raw::controller(tinyxml2::XMLElement* element) {

	printf("%s\n",__FUNCTION__);

	pose_.p = math::xml_parse_vec3(element->FirstChildElement("p"), math::vec3(0,0,0));
}



