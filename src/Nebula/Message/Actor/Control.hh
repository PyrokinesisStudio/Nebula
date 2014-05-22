#ifndef NEBULA_MESSAGE_ACTOR_CONTROL_HPP
#define NEBULA_MESSAGE_ACTOR_CONTROL_HPP

#include <Nebula/Util/WrapperTyped.hh>

#include <Nebula/Message/Actor/Base.hh>

namespace Neb {
	namespace Message {
		namespace Actor {
			namespace Control {
				namespace RigidBody {
					/** @brief %Create. */
					class Create: public Neb::Message::Actor::Base {
						public:
							/** @brief derived serialize. */
							virtual void					serializeDerived(
									boost::archive::polymorphic_oarchive & ar,
									unsigned int const & version);
							/** @brief derived serialize. */
							virtual void					serializeDerived(
									boost::archive::polymorphic_iarchive & ar,
									unsigned int const & version);


							Neb::WrapperTyped<Neb::Actor::Control::RigidBody::Base>		control_;
					};
					
					
					/** @brief %Update. */
					class Update {
						public:
							virtual ~Update() = 0;
							Neb::WrapperTyped<Neb::Actor::Control::RigidBody::Base>		control_;
					};
					/** @brief %Update. */
					class IUpdate:
						public Neb::Message::Actor::IBase,
						public Neb::Message::Actor::Control::RigidBody::Update
					{
						public:
							/** @brief derived serialize. */
							virtual void					serialize(
									boost::archive::polymorphic_iarchive & ar,
									unsigned int const & version);
					};
					/** @brief %Update. */
					class OUpdate:
						public Neb::Message::Actor::OBase,
						public Neb::Message::Actor::Control::RigidBody::Update
					{
						public:
							virtual void					pre();
							virtual void					post();

							/** @brief derived serialize. */
							virtual void					serialize(
									boost::archive::polymorphic_oarchive & ar,
									unsigned int const & version);
					};
				}
			}
		}
	}
}

#endif




