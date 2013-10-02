#include <nebula/platform/renderer/gl/glx/base.hpp>

void	nprgg::base::init( const boost::shared_ptr<npw::base>&  )
{
	//PRINTSIG;
	
	att = new GLint[5];
	att[0] = GLX_RGBA;
	att[1] = GLX_DEPTH_SIZE;
	att[2] = 24;
	att[3] = GLX_DOUBLEBUFFER;
	att[4] = None;



	m_vi = glXChooseVisual( m_xdisplay, 0, att );
	
	if(m_vi == NULL)
	{
		throw Except("glXChooseVisual: no appropriate visual found\n");
		
	} 
	else
	{
		printf("glXChooseVisual: visual %p selected\n", (void *)m_vi->visualid); // %p creates hexadecimal output like in glxinfo
	}
	
	m_cmap = XCreateColormap( m_xdisplay, m_root_xwindow, m_vi->visual, AllocNone );
	
	m_swa.colormap = m_cmap;
	m_swa.event_mask = ExposureMask | KeyPressMask;
	
	m_glc = glXCreateContext( m_xdisplay, m_vi, NULL, GL_TRUE );
	
	glXMakeCurrent( m_xdisplay, m_xwindow, m_glc );
	
	if ( glXGetCurrentContext() == NULL ) throw Except("context not created");

	nprg::base::init( data );

}
void	nprgg::base::shutdown()
{
	PRINTSIG;
	
	glXMakeCurrent( m_xdisplay, None, NULL );
	glXDestroyContext( m_xdisplay, m_glc );
}
void	nprgg::base::viewport( int a, int b, int c, int d )
{
	glViewport( a, b, c, d );
}
void	nprgg::base::update()
{
	
}
void	nprgg::base::begin_render()
{
	nprg::base::begin_render();
}
void	nprgg::base::end_render()
{
	nprg::base::end_render();
}
void	nprgg::base::swap()
{
	glXSwapBuffers( m_xdisplay, m_xwindow );
}
void	nprgg::base::look_at( bnu::vector<float> eye, bnu::vector<float> center, bnu::vector<float> up )
{
	//GLdouble eyeX, GLdouble eyeY,GLdouble eyeZ,GLdouble centerX,GLdouble centerY,GLdouble centerZ,GLdouble upX,GLdouble upY,GLdouble upZ);
	nprg::base::look_at( eye, center, up );
}




//	double eyeX, double eyeY,double eyeZ,double centerX,double centerY,double centerZ,double upX,double upY,double upZ







