#ifndef NEBULA_MESSAGE_TYPES
#define NEBULA_MESSAGE_TYPES

namespace neb {
	/** @brief %Message */
	namespace Message {

		class Base;
		class IBase;
		class OBase;

		/** @brief %Actor */
		namespace actor {

			class Create;
			class ICreate;
			class OCreate;

			class Update;
			class IUpdate;
			class OUpdate;


			/** @brief %Control */
			namespace Control {
				/** @brief %rigidbody */
				namespace RigidBody {
					class Create;
					class ICreate;
					class OCreate;

					class Update;
					class IUpdate;
					class OUpdate;

				}
			}
		}
	}
}

#endif

