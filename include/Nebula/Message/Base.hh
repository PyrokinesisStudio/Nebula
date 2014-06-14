#ifndef NEBULA_MESSAGE_BASE_HPP
#define NEBULA_MESSAGE_BASE_HPP

#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>

#include <Galaxy-Network/message.hpp>

#include <Nebula/Util/shared.hpp>

#include <Nebula/Message/Types.hh>

namespace neb {
	namespace message {
		/** \brief %Base
		 *
		 * 
		 */
		class Base:
			virtual public neb::std::shared
		{
			protected:
				Base();
				virtual ~Base() {}
		};
		class OBase:
			virtual public neb::message::Base
		{
			public:
				OBase();
				virtual void			serialize(
						boost::archive::polymorphic_oarchive & ar,
						unsigned int const & version) = 0;			
			public:
				sp::shared_ptr<gal::net::omessage>	msg_;
		};
		class IBase:
			virtual public neb::message::Base
		{
			public:
				IBase();
				virtual void			serialize(boost::archive::polymorphic_iarchive & ar, unsigned int const & version) = 0;
			public:
				sp::shared_ptr<gal::net::omessage>	msg_;
		};
	}
}

#endif

/** \example Nebula/Message/example.cc
 * Example.
 */


