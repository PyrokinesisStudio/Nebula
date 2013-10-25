#include <nebula/define.hpp>

#include <jess/ostream.hpp>

#include <nebula/platform/key.hpp>
#include <nebula/platform/renderer/base.hpp>

#include <nebula/ui/object/textview.hpp>

n52000::textview::textview():
	label_pos_(0)
{
}
void	n52000::textview::clear_label()
{
	delete[] label_;
	
	label_ = new char[16];
	
	memset( (void *)label_, '\0', 16 );
	
	label_pos_ = 0;
}
void	n52000::textview::render( jess::shared_ptr<n23000::base> rnd )
{
	jess::clog << NEB_FUNCSIG << std::endl;

	rnd->draw_text( x_, y_, label_ );
}
bool	n52000::textview::on_key_down( int k )
{
	if ( k == n20000::key::backspace )
	{
		if ( label_pos_ > 0 )
		{
			--label_pos_;
			memset( (void *)( label_ + label_pos_ ), '\0', 1 );
		}
		return true;
	}
	else if ( ( k >= n20000::key::a ) && ( k <= n20000::key::z ) )
	{
		if ( label_pos_ < label_length_ )
		{
			++label_pos_;
			memset( (void *)( label_ + label_pos_ ), k, 1 );
		}
		return true;
	}
	else if ( k == n20000::key::linefeed )
	{
		on_linefeed_();
		return true;
	}

	return false;
}
bool	n52000::textview::on_key_up( int k )
{
	return false;
} 
bool	n52000::textview::on_linefeed()
{	
	if ( on_linefeed_ )
	{
		return on_linefeed_();
	}
	
	return false;
}

