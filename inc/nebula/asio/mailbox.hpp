#ifndef __NEBULA_ASIO_MAILBOX_HPP__
#define __NEBULA_ASIO_MAILBOX_HPP__

#include <deque>

#include <jess/shared_ptr.hpp>

#include <nebula/ns.hpp>

namespace nebula
{
	namespace asio
	{
		class mailbox
		{
		public:
			virtual void									update();
			virtual void									push_back( jess::shared_ptr<n40000::message> );
			jess::shared_ptr<n40000::message>						pop_front();
			virtual void									process_message( jess::shared_ptr<n40000::message> ) = 0;
			
			std::deque< jess::shared_ptr<n40000::message> >					messages_;
		};
	}
}

#endif
