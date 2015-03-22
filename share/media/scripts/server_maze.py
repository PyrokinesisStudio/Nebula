app = neb.get_app()


# create game
gd = neb.game.game.Desc()
gd.net_type = 1

game = app.createGame(gd)

m = game.create_map_dll("../mod/maze/build/dynamic/libnebula_ext_maze.so")

scene = m.create_scene()


# server stuff

app.create_server(20002)


#client stuff

windows = app.get_windows()

window = windows[0]

context = window.createContextWindow()

environ = context.create_environ_scene_default()



actor_player = scene.createActorRigidDynamicCuboid()

m.spawn_actor(actor_player);

weap = actor_player.createWeaponSimpleProjectile(window, 0.2, 10.0, 5.0)

control = actor_player.createControlManual(window)





environ.create_view_ridealong(actor_player)

environ.set_drawable(scene);

