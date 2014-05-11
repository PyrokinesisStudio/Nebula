#ifndef NEBULA_MESSAGE_TYPES
#define NEBULA_MESSAGE_TYPES

namespace Neb {
	/** @brief %Message */
	namespace Message {

		class Base;
		typedef std::shared_ptr<Base>		Base_s;

		/** @brief %Actor */
		namespace Actor {
			/** @brief %Control */
			namespace Control {
				namespace RigidBody {
					class Create;
					class Update;

					typedef std::shared_ptr<Create>		Create_s;
					typedef std::shared_ptr<Update>		Update_s;

				}
			}
		}
	}
}

#endif

