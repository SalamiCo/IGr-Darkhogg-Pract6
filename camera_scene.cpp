#include "camera_scene.hpp"

#define BIG_SPHERE 64
#define SMALL_SPHERE 24

void igr::camera_scene::on_begin () {
  // Light0
  glEnable(GL_LIGHT0);
  GLfloat lgtd[]={1.f, 1.f, 1.f, 1.f};
  glLightfv(GL_LIGHT0, GL_DIFFUSE, lgtd);
  GLfloat lgta[]={0.3f, 0.3f, 0.3f, 1.f};
  glLightfv(GL_LIGHT0, GL_AMBIENT, lgta);
  GLfloat lgtp[]={25.f, 25.f, 0.f, 1.f};
  glLightfv(GL_LIGHT0, GL_POSITION, lgtp);

  spheres[0] = mesh::make_aligned_box({1.f, 1.f, 1.f});//mesh::make_aligned_sphere({1.f, 1.f, 1.f}, BIG_SPHERE, BIG_SPHERE);

  spheres[1] = mesh::make_aligned_sphere({1.f, 0.f, 0.f}, SMALL_SPHERE, SMALL_SPHERE);
  spheres[1].transform(matr<double>::make_scalation({0.3, 0.3, 0.3}));
  spheres[1].transform(matr<double>::make_translation({0.75, 0.0, 0.0}));

  spheres[2] = mesh::make_aligned_sphere({0.f, 1.f, 0.f}, SMALL_SPHERE, SMALL_SPHERE);
  spheres[2].transform(matr<double>::make_scalation({0.3, 0.3, 0.3}));
  spheres[2].transform(matr<double>::make_translation({0.0, 0.75, 0.0}));

  spheres[3] = mesh::make_aligned_sphere({0.f, 0.f, 1.f}, SMALL_SPHERE, SMALL_SPHERE);
  spheres[3].transform(matr<double>::make_scalation({0.3, 0.3, 0.3}));
  spheres[3].transform(matr<double>::make_translation({0.0, 0.0, 0.75}));
}

bool igr::camera_scene::on_event (event_t event) {
  return false;
}

void igr::camera_scene::on_update (float delta) {
  double rotX = 0.0;
  double rotY = 0.0;
  double rotZ = 0.0;

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
    rotX += delta * 3.0;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
    rotX -= delta * 3.0;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
    rotY += delta * 3.0;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
    rotY -= delta * 3.0;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)) {
    rotZ += delta * 3.0;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X)) {
    rotZ -= delta * 3.0;
  }

  auto oldUp = cam.up;
  cam.transform(matr<double>::make_rotation_x(rotX));
  cam.transform(matr<double>::make_rotation_y(rotY));
  cam.transform(matr<double>::make_rotation_z(rotZ));
  cam.up = oldUp;
  //cam.normalize();

  double yaw   = 0.0;
  double pitch = 0.0;
  double roll  = 0.0;

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)) {
    yaw += delta * 3.0;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) {
    yaw -= delta * 3.0;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
    pitch += delta * 3.0;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F)) {
    pitch -= delta * 3.0;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C)) {
    roll += delta * 3.0;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::V)) {
    roll -= delta * 3.0;
  }

  cam.yaw(yaw);
  cam.pitch(pitch);
  cam.roll(roll);
  

  double mX = 0.0;
  double mY = 0.0;
  double mZ = 0.0;

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::T)) {
    mX += delta * 3.0;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Y)) {
    mX -= delta * 3.0;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::G)) {
    mY += delta * 3.0;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::H)) {
    mY -= delta * 3.0;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::B)) {
    mZ += delta * 3.0;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::N)) {
    mZ -= delta * 3.0;
  }

  cam.eye  = cam.eye + vec<double>{mX, mY, mZ, category::vector};
  //cam.look = cam.look + vec<double>{mX, mY, mZ, category::vector};


  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1)) {
    proj = projection::orthogonal;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2)) {
    proj = projection::perspective;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3)) {
    proj = projection::oblique;
  }


  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
    cam.eye  = {3.0, 3.0, 3.0};
    cam.look = {0.0, 0.0, 0.0};
    cam.up   = {0.0, 1.0, 0.0};
    //cam.normalize();
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num4)) {
    cam.eye  = {3.0, 0.0, 0.0};
    cam.look = {0.0, 0.0, 0.0};
    cam.up   = {0.0, 1.0, 0.0};
    //cam.normalize();
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num5)) {
    cam.eye  = {0.0, 3.0, 0.0001};
    cam.look = {0.0, 0.0, 0.0};
    cam.up   = {0.0, 1.0, 0.0};
    //cam.normalize();
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num6)) {
    cam.eye  = {0.0, 0.0, 3.0};
    cam.look = {0.0, 0.0, 0.0};
    cam.up   = {0.0, 1.0, 0.0};
    //cam.normalize();
  }
}

void igr::camera_scene::on_draw () {
  /* Clear the scene */
  glClearColor(0.15f, 0.175f, 0.2f, 1.f);
  glClearDepth(1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  /* Set up lighting */
  glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
  glEnable(GL_LIGHTING);
  glShadeModel(GL_SMOOTH);

  glEnable(GL_COLOR_MATERIAL);
  glMaterialf(GL_FRONT, GL_SHININESS, 0.1f);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  //glEnable(GL_CULL_FACE);
  //glCullFace(GL_FRONT);

  glEnable(GL_MULTISAMPLE);

  glEnable(GL_DEPTH_TEST);
  glDepthMask(GL_TRUE);
  glDepthFunc(GL_LEQUAL);
  glDepthRange(0.0f, 1.0f);

  /* Update the projection */
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();


  auto aspect = (float) window.getSize().x / (float) window.getSize().y;

  switch (proj) {
    case projection::orthogonal: {
      glOrtho(-aspect, aspect, -1.0, 1.0, 0.1, 1000.0);

      break;
    }

    case projection::perspective: {
      gluPerspective(45.0, aspect, 0.1, 1000.0);

      break;
    }

    case projection::oblique: {
      vec<double> oblique_vector {0.1, 0.1, 1, category::vector};
      auto d = oblique_vector.normalized();

      double N = 1;
      float m[] = { // COLUMN MAJOR!!
                    1.f,               0.f,   0.f,   0.f,
                    0.f,               1.f,   0.f,   0.f,
            - d.x / d.z,       - d.y / d.z,   1.f,   0.f,
        - N * d.x / d.z,   - N * d.y / d.z,   0.f,   1.f
      };

      glOrtho(-aspect, aspect, -1.0, 1.0, 0.1, 1000.0);
      glMultMatrixf(m);

      break;
    }
  }

  /* Update the camera */
  cam.gl_update();

  /* Draw axis */
  glBegin(GL_LINES);
    glColor3f(1.f, 0.f, 0.f);
    glVertex3f(-100.f, 0.f, 0.f);
    glVertex3f(+100.f, 0.f, 0.f);

    glColor3f(0.f, 0.8f, 0.f);
    glVertex3f(0.f, -100.f, 0.f);
    glVertex3f(0.f, +100.f, 0.f);

    glColor3f(0.f, 0.5f, 1.f);
    glVertex3f(0.f, 0.f, -100.f);
    glVertex3f(0.f, 0.f, +100.f);
  glEnd();

  /* Draw box */
  for (auto sphere : spheres) {
    sphere.gl_draw_immediate();
  }
}

void igr::camera_scene::on_end () {

}



/** Main method */
int main () {
  igr::camera_scene{}.run();
}