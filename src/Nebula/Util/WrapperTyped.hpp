#ifndef NEBULA_UTIL_WRAPPERTYPED_HH
#define NEBULA_UTIL_WRAPPERTYPED_HH

#include <map>

//#include <boost/function.hpp>
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

#include <Nebula/Util/Typed.hpp>
#include <Nebula/Util/Factory.hpp>

namespace Neb {
	/** @brief WrapperTyped
	 * class T must be derived from and registered with Neb::Util::Typed or exceptions will be thrown
	 */
	template<class T> class WrapperTyped {
		public:
			typedef std::weak_ptr< Neb::Factory<T> >		factory_weak;
			typedef std::shared_ptr<T>				shared;
			/** */
			WrapperTyped(factory_weak factory): factory_(factory) {
			}
			/** */
			WrapperTyped(factory_weak factory, shared s): factory_(factory) {
				ptr_ = s;
			}
			/** @brief Destructor */
			virtual ~WrapperTyped() {}
			/** @brief %Load */
			template<class Archive> void		load(Archive & ar, unsigned int const & version) {
				// get the code
				long int hash_code;
				ar >> boost::serialization::make_nvp("hash_code", hash_code);
				
				// get the factory
				auto fs = factory_.lock();
				assert(fs);

				// allocate the object
				ptr_.reset((T*)fs->alloc(hash_code));

				// read objcet data
				ar >> boost::serialization::make_nvp("object", *ptr_);
			}
			/** @brief %Save */
			template<class Archive> void		save(Archive & ar, unsigned int const & version) const {
				ar << boost::serialization::make_nvp("hash_code", ptr_->hash_code());
				ar << boost::serialization::make_nvp("object", *ptr_);
			}
			/** */
			void		load(boost::archive::xml_iarchive & ar, unsigned int const & version) {
				// get the code
				std::string name;
				ar >> boost::serialization::make_nvp("name", name);
				Neb::Typed::hash_type hash = Neb::Typed::to_hash_code(name);
				
				// get the factory
				auto fs = factory_.lock();
				assert(fs);

				// allocate the object
				ptr_.reset((T*)fs->alloc(hash));

				// read objcet data
				ar >> boost::serialization::make_nvp("object", *ptr_);
			}
			/** */
			void		save(boost::archive::xml_oarchive & ar, unsigned int const & version) const {
				std::string name = Neb::Typed::to_string(ptr_->hash_code());
				ar << boost::serialization::make_nvp("name", name);
				ar << boost::serialization::make_nvp("object", *ptr_);
			}
			BOOST_SERIALIZATION_SPLIT_MEMBER();
		public:
			/** @brief Pointer */
			shared				ptr_;
			factory_weak			factory_;
	};
}

#endif



