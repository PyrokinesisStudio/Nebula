#ifndef __GLUTPP_NETWORK_ACTOR_UPDATE_HPP__
#define __GLUTPP_NETWORK_ACTOR_UPDATE_HPP__

#include <boost/serialization/vector.hpp>
#include <boost/serialization/shared_ptr.hpp>

#include <Nebula/Scene/Types.hpp>

#include <Nebula/config.hpp> // gru/config.hpp.in
//#include <Nebula/master.hpp>
//#include <Nebula/Scene/desc.hpp>
//#include <Nebula/Actor/desc.hpp>
#include <Nebula/Actor/Util/Address.hpp>
//#include <Nebula/Actor/event.hpp>
#include <Nebula/Actor/Base.hpp>

#include <Nebula/Scene/scene.hpp>

#include <Nebula/Message/Base.hpp>

namespace Neb {
	namespace Message {
		namespace Actor {
			struct Update {
				
				Update(): count_(0) {}
				
				/** @brief Default load/save operator.
				 * All other types are simply passed to the archive
				 */
				//template<typename T> Update&		operator&(T const & t) {
			//		msg_->ar_ & t;
			//	}
				
				int				count_;
				std::stringstream::pos_type	pos_count_;
				
			};
			struct OUpdate: Neb::Message::OBase, Update{

				/** @brief Save %Actor. */
				Update&		operator<<(Neb::Actor::Base_s actor);
				/** */
				template<typename T> Update&		operator&(T const & t) {
					msg_->ar_ & t;
					return *this;
				}
				

				/** @brief Before saving.
				 * Implement the virtual savePre function.
				 * Record the position of the count data.
				 * Doing so enables @c this to load and save arrays whose length
				 * is unknown until all data is saved.
				 * This function is called by the initialization of an omessage object
				*/
				virtual void		pre() {
					// save the position of count
					pos_count_ = msg_->ss_.tellp();
					
					// allocate space for count
					msg_->ar_ << count_;
				}
				/** @brief After saving.
				 * Implement the virtual savePost function. Overwrite the count data.
				*/
				virtual void		post() {
					auto pos = msg_->ss_.tellp();
					
					msg_->ss_.seekp(pos_count_);
					/** @todo determine if I count just say "ar << count" here */
					msg_->ss_.write((char*)&count_, sizeof(count_));
					
					msg_->ss_.seekp(pos);
				}
			};
			struct IUpdate: Neb::Message::IBase, Update {
				/** @brief Load */
				Update&		operator>>(Neb::Scene::Base_s);
				/** */
				template<typename T> Update&		operator&(T const & t) {
					msg_->ar_ & t;
					return *this;
				}
			};
			
		}
	}
}

#endif



