#ifndef __NEBULA_PLATFORM_RENDERER_BASE_HPP__
#define __NEBULA_PLATFORM_RENDERER_BASE_HPP__

#include <boost/numeric/ublas/vector.hpp>

#include <nebula/define.hpp>

namespace bnu = boost::numeric::ublas;

namespace nebula
{
	namespace platform
	{
		namespace renderer
		{
			/// base
			class base
			{
			public:
				///@name draw
				///{
				/// cube
				void							draw_cube();
				///}
			
/// push_matrix
virtual void		push_matrix();
/// pop_matrix
virtual void		pop_matrix();
/// swap
virtual void		swap();
/// mult_matrix
virtual void		mult_matrix(const bnu::matrix<FLOAT>&);
/// scale
virtual void		scale(const bnu::vector<FLOAT>&);
/// look at
virtual void		look_at( const bnu::vector<FLOAT>&, const bnu::vector<FLOAT>&, const bnu::vector<FLOAT>& ); 
/// light
virtual void		light();
/// begin render
virtual void		begin_render();
/// end render
virtual void		end_render();
/// draw window quad
virtual void		draw_window_quad( int, int, int, int );
virtual void		unproject( int, int, int, double*, double*, double* );
	
				/// lookat
				void							lookat(bnu::vector<FLOAT>,bnu::vector<FLOAT>,bnu::vector<FLOAT>);
				
				
			};
		}
	}
}


#endif
