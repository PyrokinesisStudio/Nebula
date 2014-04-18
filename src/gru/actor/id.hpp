#ifndef __NEBULA_ACTOR_ID_H__
#define __NEBULA_ACTOR_ID_H__

#include <math/transform.h>
#include <math/raw/raw.h>

#include <gal/network/serial.h>

#include <gru/actor/id.hpp>
#include <gru/shape/desc.hpp>

namespace glutpp {
	namespace actor {
		class id: public gal::network::serial<id, gal::network::base>
		{
			public:
				int i_;
		};
	}
}

#endif








