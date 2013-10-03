#include <nebula/platform/renderer/base.hpp>

#include <nebula/content/actor/admin/base.hpp>





#include <nebula/content/animation/frame.hpp>


void	nebula::content::animation::frame::step(FLOAT dt)
{
	auto it = m_children.begin();
	for ( ; it != m_children.end(); it++ )
	{
		(*it)->step(dt);
	}
}
void	nebula::content::animation::frame::AddChild(nebula::content::animation::frame* f)
{
	m_children.push_back(f);
}
void	nebula::content::animation::frame::AddActor(nebula::content::actor::admin::base* a)
{
	m_actors.push_back(a);
}


nebula::content::animation::translation::translation(boost::numeric::ublas::vector<FLOAT>& v)
{
	m_rate = v;
}
void	nebula::content::animation::translation::step(FLOAT dt)
{
	//m_pose.p += m_rate * dt;

	nebula::content::animation::frame::step(dt);
}





