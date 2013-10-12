#ifndef __NEBULA_CONTENT_ACTOR_RENDERER_BASE_HPP__
#define __NEBULA_CONTENT_ACTOR_RENDERER_BASE_HPP__

#include <jess/shared_ptr.hpp>

#include <nebula/ns.hpp>

namespace nebula
{
	namespace content
	{
		namespace actor
		{
			namespace renderer
			{
				/// base
				class base
				{
				public:
					///@name ctor and dtor
					///@{
					// Ctor
					base();
					/// Copy Ctor
					base(const base&);
					/// Dtor
					~base();
					///@}

					///@name operator
					///@{
					/// assignment
					base&									operator=(const base&);
					///@}



					/// init
					virtual	void								init( jess::shared_ptr<n34100::base> );
					/// shutdown
					virtual	void								shutdown();
					/// update
					virtual	void								update();
					/// step
					virtual	void								step( float );
					/// render
					virtual	void								render( jess::shared_ptr<n23000::base> );




					/// create shapes
					virtual	void								create_shapes();




					/// parent	
					std::weak_ptr<n34100::base>						parent_;
				};
			}
		}
	}
}

#endif








