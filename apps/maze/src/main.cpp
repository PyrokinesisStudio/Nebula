
/*


#include <glm/gtc/matrix_transform.hpp>

#include <gal/console/base.hpp>

#include <gal/etc/stopwatch.hpp>

#include <neb/core/util/cast.hpp>
#include <neb/core/app/Base.hpp>
#include <neb/core/core/actor/base.hpp>
#include <neb/core/util/wrapper.hpp>
#include <neb/core/core/light/base.hpp>
#include <neb/core/core/scene/base.hpp>
#include <neb/core/core/shape/base.hpp>
#include <neb/core/core/shape/cuboid/desc.hpp>
#include <neb/core/core/actor/base.hpp>
#include <neb/core/core/actor/rigidbody/desc.hpp>

#include <neb/gfx/core/light/util/decl.hpp>
#include <neb/gfx/core/light/directional.hpp>
#include <neb/gfx/core/light/point.hpp>
#include <neb/gfx/core/light/spot.hpp>
#include <neb/gfx/context/Window.hpp>
#include <neb/gfx/context/fbo.hpp>
#include <neb/gfx/context/fbo_multi.hpp>
#include <neb/gfx/environ/two.hpp>
#include <neb/gfx/environ/shadow/point.hpp>
#include <neb/gfx/environ/shadow/directional.hpp>
#include <neb/gfx/environ/SceneDefault.hpp>
#include <neb/gfx/environ/vis_depth.hpp>
#include <neb/gfx/gui/object/terminal.hh>
#include <neb/gfx/camera/view/ridealong.hh>
#include <neb/gfx/camera/view/shadow/point.hpp>
#include <neb/gfx/camera/proj/perspective.hpp>

#include <neb/core/game/map/base.hpp>
#include <neb/core/game/trigger/ActorEx1.hpp>
#include <neb/core/game/game/desc.hpp>
//#include <neb/ext/maze/game/map/maze2.hpp>

#include <neb/phx/app/base.hpp>
#include <neb/phx/core/scene/base.hpp>
#include <neb/core/game/weapon/SimpleProjectile.hpp>
#include <neb/phx/core/actor/control/rigidbody/base.hpp>
#include <neb/phx/test.hpp>

//#include <neb/ext/maze/game/map/maze2.hpp>

#include <neb/fin/gfx_phx/core/scene/base.hpp>
#include <neb/fin/gfx_phx/core/actor/rigiddynamic/base.hpp>
#include <neb/fin/gfx_phx/core/actor/rigidstatic/base.hpp>
#include <neb/fin/gfx_phx/core/shape/box.hpp>

template<typename B, typename D> void	makeDefaultFunc()
{

	gal::itf::shared::register_type(std::type_index(typeid(B)));
	gal::itf::shared::register_type(std::type_index(typeid(D)));


	std::function< std::shared_ptr<B>() > f(
			[]() { return std::shared_ptr<D>(new D(), gal::stl::deleter<D>()); }
			);

	gal::stl::factory<B>::default_factory_->add(typeid(D).hash_code(), f);
}
template<typename T> std::shared_ptr<T>		loadXML(std::string filename)
{
	std::ifstream ifs;
	ifs.open(filename);
	if(!ifs.is_open())
	{
		std::cout << "file error: " << filename << std::endl;
		abort();
	}

	gal::stl::wrapper<T> w;

	boost::archive::polymorphic_xml_iarchive ar(ifs);

	w.load(ar,0);

	return w.ptr_;
}

void	create_enemy();


typedef std::shared_ptr<neb::gfx::window::base> window_shared;
typedef neb::gfx::core::light::point		light_type;
typedef neb::game::game::base			game_t;

typedef neb::fin::gfx_phx::core::scene::base	map_type;
//typedef neb::ext::maze::game::map::maze2	map_type;

typedef std::shared_ptr<neb::fin::gfx_phx::core::scene::base>	scene_s;

typedef neb::fin::gfx_phx::core::actor::rigiddynamic::base actor_dyn_t;

std::shared_ptr<game_t>			game;

std::shared_ptr<neb::fin::gfx_phx::core::actor::base>	enemy;

std::shared_ptr<neb::fin::gfx_phx::app::base>		app;
window_shared						window0;
std::shared_ptr<neb::gfx::context::window>		context1;
std::shared_ptr<neb::gfx::environ::SceneDefault>	environ1;
std::shared_ptr<neb::gfx::context::window>		context2;

window_shared						window1;
std::shared_ptr<neb::gfx::context::window>		context1_0;


std::shared_ptr<neb::fin::gfx_phx::core::scene::base>			scene;
//std::shared_ptr<neb::fnd::core::scene::base>			scene;


std::shared_ptr<neb::fin::gfx_phx::core::actor::rigiddynamic::base>	actor_player;
//std::shared_ptr<neb::fnd::core::actor::base>	actor_player;
std::shared_ptr<neb::fnd::core::actor::base>				actor_light;

shared_ptr<neb::gfx::gui::layout::base>	create_layout()
{

	assert(window0);
	
	auto app = neb::fin::gfx_phx::app::base::global();
	
	auto layout = app->createLayout().lock();

	layout->connect(window0);

	layout->createObjectTerminal();

	return layout;
}

weak_ptr<neb::fin::gfx_phx::core::actor::rigiddynamic::base>		create_actor_ai(
		std::shared_ptr<neb::fin::gfx_phx::core::scene::base> scene) {

	assert(scene);

	auto a = scene->createActorRigidDynamicCuboid(
			neb::fnd::core::actor::rigidbody::desc(neb::fnd::pose(glm::vec3(20, 0, 0))),
			neb::fnd::core::shape::cuboid::desc(glm::vec3(1.0))
			).lock();

	auto actor = std::dynamic_pointer_cast<neb::fin::gfx_phx::core::actor::rigiddynamic::base>(a);

	actor->flag_.set(neb::fnd::core::actor::util::flag::DESTRUCTIBLE);
	
	
	
	//actor->init();
	
	// shape	
	//auto shape = actor->createShapeCube(neb::fnd::pose(), 1.0);
	//actor->setupFiltering();
	//actor->setGlobalPosition(vec3(0,0,5));

	auto pxrd = actor->px_actor_->isRigidDynamic();

	pxrd->setLinearDamping(10.0);
	pxrd->setAngularDamping(4.0);
	
	actor->createControlPD();
	
	return actor;	
}
shared_ptr<neb::fin::gfx_phx::core::scene::base>			create_scene(
		shared_ptr<neb::gfx::window::base> window,
		shared_ptr<neb::gfx::context::window> context,
		shared_ptr<neb::fin::gfx_phx::core::actor::base>& enemy)
{

	assert(app);
	

	scene = app->createScene().lock();

	// actors

	auto actor1 = scene->createActorRigidDynamicCuboid(
			neb::fnd::core::actor::rigidbody::desc(neb::fnd::pose(glm::vec3(-5, 0, 0))),
			neb::fnd::core::shape::cuboid::desc(glm::vec3(1.0))
			).lock();

	auto shape1 = std::dynamic_pointer_cast<neb::fin::gfx_phx::core::shape::box>(actor1->neb::fnd::core::shape::util::parent::map_.front());
	if(shape1) {
		auto mesh1 = shape1->mesh_;
		if(mesh1) {
			mesh1->texture_ = neb::gfx::texture::makePNG("crab.png");
			mesh1->material_front_.raw_.diffuse_ = neb::fnd::color::color(1,1,1,1);
		}
	}

	auto actor2 = scene->createActorRigidDynamicCuboid(
			neb::fnd::core::actor::rigidbody::desc(neb::fnd::pose(glm::vec3(5, 0, 0))),
			neb::fnd::core::shape::cuboid::desc(glm::vec3(1.0))
			).lock();
	auto shape2 = std::dynamic_pointer_cast<neb::fin::gfx_phx::core::shape::box>(actor2->neb::fnd::core::shape::util::parent::map_.front());
	if(shape2) if(shape2->mesh_) shape2->mesh_->normal_map_ = neb::gfx::texture::makePNG("norm.png");

	scene->createActorRigidDynamicCuboid(
			neb::fnd::core::actor::rigidbody::desc(neb::fnd::pose(glm::vec3(0, -5, 0))),
			neb::fnd::core::shape::cuboid::desc(glm::vec3(1.0))
			);
	scene->createActorRigidDynamicCuboid(
			neb::fnd::core::actor::rigidbody::desc(neb::fnd::pose(glm::vec3(0, 5, 0))),
			neb::fnd::core::shape::cuboid::desc(glm::vec3(1.0))
			);

	auto static_cube5 = scene->createActorRigidStaticCube(neb::fnd::pose(vec3( 0, 0,-5)), 1.0).lock();


	//scene->createActorRigidStaticCube(neb::fnd::pose(vec3( 0, 0, 5)), 1.0);

	// player's actor
	actor_player = std::dynamic_pointer_cast<neb::fin::gfx_phx::core::actor::rigiddynamic::base>(
			scene->createActorRigidDynamicCuboid(
				neb::fnd::core::actor::rigidbody::desc(),
				neb::fnd::core::shape::cuboid::desc(glm::vec3(1.0))
				).lock()
			);


	// weapon
	auto weap = actor_player->createWeaponSimpleProjectile(window, 0.2, 10.0, 5.0);

	// lights
	actor_light = scene->createActorLightPoint(vec3()).lock();
	//scene->createActorLightPoint(vec3(10,0,0));

	context->setDrawable(scene);

	// connect actor

	actor_player->createControlManual(window);

	neb::is<neb::gfx::environ::base, neb::gfx::environ::SceneDefault>(context->environ_)->createViewridealong(actor_player);
	
	// enemy
	create_enemy();

	return scene;
}
void							create_enemy() {
	assert(actor_player);
	assert(game);

	// ai
	enemy = dynamic_pointer_cast<neb::fin::gfx_phx::core::actor::base>(
			create_actor_ai(scene).lock()
			);

	// weapon
	enemy->createWeaponSimpleProjectile(window0, 0.2, 10.0, 5.0);

	auto ai(sp::make_shared<neb::game::ai::base>());
	
	
	game->neb::game::ai::util::parent::insert(ai);

	ai->actor_ = enemy;
	ai->target_ = actor_player;

}
scene_s		create_maze()
{
	//assert(window0);
	//assert(context1);

	auto app = neb::fin::gfx_phx::app::base::global();

	// create map
	
	//auto map = app->createSceneDll("../../components/ext/maze/libnebula_ext_maze_0_so_db.so").lock();
	auto map = app->createSceneDll("../../components/ext/hf/libnebula_ext_hf_0_so_db.so").lock();
	
	scene = map;

	// player's actor
	actor_player = std::dynamic_pointer_cast<actor_dyn_t>(loadXML<neb::fnd::core::actor::base>("actor_player.xml"));
	scene->addActor(actor_player);



	// weapon
	if(window0)
	{
		auto weap = actor_player->createWeaponSimpleProjectile(window0, 0.2, 10.0, 5.0);

		// lights
		//auto actor4 = map->createActorLightDirectional(glm::vec3(0,1,-1)).lock();
		//actor_light = map->createActorLightPoint(glm::vec3(0,0,10)).lock();


		//	auto shape4 = actor_light->neb::fnd::core::shape::util::parent::map_.front();
		//	assert(shape4);
		//	auto light = std::dynamic_pointer_cast<light_type>(shape4->neb::fnd::core::light::util::parent::map_.front());
		//	assert(light);


		// give scene to context


		// camera

		actor_player->createControlManual(window0);

		environ1 = neb::is<neb::gfx::environ::base, neb::gfx::environ::SceneDefault>(context1->environ_);

		environ1->createViewridealong(actor_player);
	}	
	//	light->initShadow(environ1);

	//create_enemy();


	return map;
}
void		setup_game()
{

	neb::game::game::desc gameDesc;

	game = app->createGame(gameDesc);

	// scene

	//auto scene = create_scene(window, context, enemy);
	scene = std::dynamic_pointer_cast<neb::fin::gfx_phx::core::scene::base>(
			create_maze()
			);
	assert(scene);

	game->scene_ = scene;

	// trigger
	if(enemy) {
		auto trig(make_shared<neb::game::trigger::ActorEx1>(game));
		game->neb::game::trigger::util::parent::insert(trig);
		trig->connect(enemy);
	}

}
void				createWindowTexVis(std::shared_ptr<neb::gfx::texture> tex)
{
	auto window1 = app->createWindow().lock();
	auto context4 = window1->createContextTwo().lock();
	context4->setDrawable(tex);
}
void				createWindow0() {

	assert(app);

	window0 = app->createWindow().lock();

	context1 = window0->createContextThree().lock();
	context2 = window0->createContextTwo().lock();

	auto layout = create_layout();

	context2->setDrawable(layout);

}
*/
/*void				createWindow1()
  {
  assert(app);
  assert(scene);

  window1 = app->createWindow().lock();

  context1_0 = window1->createContextWindow().lock();

  auto environ = context1_0->createEnvironVisDepth().lock();

  environ->light_ = light0;

  context1_0->setDrawable(scene);
  }*/

/*
void				setupWindow0()
{
	assert(scene);
	assert(context1);
	context1->setDrawable(scene);
}
*/

/*
void queryproj()
{

	// test
	assert(actor_light);
	auto shape = actor_light->neb::fnd::core::shape::util::parent::map_.front(); assert(shape);
	auto light = shape->neb::fnd::core::light::util::parent::map_.front();	assert(light);
	auto l = neb::is<neb::fnd::light::__base, neb::gfx::core::light::point>(light);
	auto e0 = neb::is<neb::gfx::environ::base, neb::gfx::environ::SceneDefault>(context1->environ_);
	auto e1 = neb::is<neb::gfx::environ::base, neb::gfx::environ::shadow::point>(l->shadow_environ_);

	physx::PxConvexMeshGeometry* g0 = neb::frustrum_geometry(e0->proj_->proj());
	physx::PxConvexMeshGeometry* g1 = neb::frustrum_geometry(e1->proj_->proj());

	bool res;

	gal::etc::stopwatch sw;

	int hits = 0;
*/
	/*	for(int i = 0; i < 1000; i++) {
		sw.start(glfwGetTime());
		if(query(g0, e0->view_->view(), g1, e1->view_[0]->view())) hits++;
		if(query(g0, e0->view_->view(), g1, e1->view_[1]->view())) hits++;
		if(query(g0, e0->view_->view(), g1, e1->view_[2]->view())) hits++;
		if(query(g0, e0->view_->view(), g1, e1->view_[3]->view())) hits++;
		if(query(g0, e0->view_->view(), g1, e1->view_[4]->view())) hits++;
		if(query(g0, e0->view_->view(), g1, e1->view_[5]->view())) hits++;
		sw.stop(glfwGetTime());
		}*/
/*
 res = neb::query(*g0, e0->view_->view(), *g1, e1->view_[0]->view());std::cout << "query " << res << std::endl;
	res = neb::query(*g0, e0->view_->view(), *g1, e1->view_[1]->view());std::cout << "query " << res << std::endl;
	res = neb::query(*g0, e0->view_->view(), *g1, e1->view_[2]->view());std::cout << "query " << res << std::endl;
	res = neb::query(*g0, e0->view_->view(), *g1, e1->view_[3]->view());std::cout << "query " << res << std::endl;
	res = neb::query(*g0, e0->view_->view(), *g1, e1->view_[4]->view());std::cout << "query " << res << std::endl;
	res = neb::query(*g0, e0->view_->view(), *g1, e1->view_[5]->view());std::cout << "query " << res << std::endl;

	std::cout << hits << " " << sw.getAvg() << std::endl;


}
*/

#include <neb/fin/app/base.hpp>


int			main(int ac, char** av)
{
/*
	makeDefaultFunc<neb::fnd::core::actor::desc, neb::fnd::core::actor::desc>();
	makeDefaultFunc<neb::fnd::core::actor::desc, neb::fnd::core::actor::rigidbody::desc>();
	makeDefaultFunc<neb::fnd::core::actor::base, neb::fin::gfx_phx::core::actor::rigiddynamic::base>();
	makeDefaultFunc<neb::fnd::core::shape::base, neb::fin::gfx_phx::core::shape::base>();
	makeDefaultFunc<neb::fnd::core::shape::base, neb::fin::gfx_phx::core::shape::box>();
	makeDefaultFunc<neb::fnd::light::__base, neb::gfx::core::light::spot>();
*/



	auto app = neb::fin::app::base::s_init(ac, av);

	// game

	// create drawables
	//shared_ptr<neb::fin::gfx_phx::core::actor::base> enemy;

	auto scene = app->createSceneDLL("maze/build/libnebula_ext_maze.so");

	//setup_game();

	//setupWindow0();

	//createWindow1();
	//createWindowTexVis(scene->tex_shadow_map_);
	//queryproj();




	app->loop();


}




