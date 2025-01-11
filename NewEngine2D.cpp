#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "glfw3.lib")

#include "api/include/scene.h"

#include "components/include/sprite.h"
#include "components/include/sprite_renderer.h"
#include "components/include/transform.h"
#include "components/include/box_collider2d.h"
#include "components/include/rigidbody2d.h"
#include "api/include/sprite_batching.h"
#include "components/include/particle_generator.h"

api::window wind;
api::scene mainSc;
api::camera mainCamera;

components::object a("newobj", 0);
components::object b("newobj2", 1);

components::sprite* sp1;
components::sprite_renderer* spr1;
components::sprite* sp2;

components::box_collider2d* bx1;

float angle = 0.f;

components::image2d im1;
components::image2d im2;

api::sprite_batching spb;

void display(void) {
    mainCamera.zoom = 1.f;
    angle += 10 * wind.deltaTime;
    
    a.get_component<components::transform>()->setRotationAngle(angle);
    //std::cout << wind.deltaTime << std::endl;
    mainSc.renderScene();
}

int main(void)
{
    wind.createWindow(1600, 1050, "test", NULL, NULL, 1.f);

    mainCamera = api::camera(glm::vec2(1600, 1050), glm::vec2(0, 0), 1.f);
    mainCamera.init();
    mainSc = api::scene(&wind, &mainCamera);

    //just simple example
    /*
    a.add_component<components::transform>(&mainCamera, 400, 100, glm::vec2(0, 300), components::ObjectType::BASE, glm::vec2(1, 1), angle);
    sp1 = a.add_component<components::sprite>(800, 200);
    sp1->from_png("sprites\\800x200.png");
    im1 = components::gen_img("sprites\\800x200.png");
    im2 = components::gen_img("sprites\\800x200a.png");
    spr1 = a.add_component<components::sprite_renderer>(&mainCamera);
    bx1 = a.add_component<components::box_collider2d>(&mainSc);
    a.add_component<components::rigidbody2d>(&mainSc);
    a.add_component<components::particle_generator>(&mainSc, 30, glm::vec2(80, 20), glm::vec2(500, 500), 0.3f, glm::vec2(150, 1));

    b.add_component<components::transform>(&mainCamera, 1600, 200, glm::vec2(0, -500), components::ObjectType::BASE, glm::vec2(1, 1), angle);
    b.add_component<components::sprite>(800, 200)->from_png("sprites\\800x200.png");
    b.add_component<components::sprite_renderer>(&mainCamera);
    b.add_component<components::box_collider2d>(&mainSc);
    b.add_component<components::rigidbody2d>(&mainSc, components::rigidbodyType::STATIC)->gravity = -9.81f;

    mainSc.addObject(&a);
    mainSc.addObject(&b);
    */
    
    wind.run(display);
    return 0;
}