#include "static_object.h" 
#include <glut.h>
static float ratio = 40.0f;

StaticObject::StaticObject(const char* _imageFile, float _scale, b2Vec2 pos, b2World* world, int wWidth, int wHeight) {
	scale = _scale;
	
	gLoadedTexture = Image(_imageFile);
	imageFile = _imageFile;
	
	width = gLoadedTexture.width * scale;
	height = gLoadedTexture.height * scale;
	
	x = pos.x;
	y = pos.y;

	winWidth = wWidth;
	winHeight = wHeight;

	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(x/ratio, y/ratio);
	vertices[0].Set(0,0);
	vertices[1].Set(0,height/ratio);
	vertices[2].Set(width/ratio, height/ratio);
	vertices[3].Set(width/ratio, 0);
	box.Set(vertices,4);
	body = world->CreateBody(&bodyDef);
	body->SetUserData(this);
	body->CreateFixture(&box, 0.0f);

}

void StaticObject::WindowResize(int wWidth, int wHeight) {
}

void StaticObject::resize(int _width, int _height) { 
	width = _width;
	height = _height;
	box.SetAsBox((_width/2.0f)/ratio, (_height/2.0f)/ratio);
}


void StaticObject::render() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gLoadedTexture.render(x, y, 0.0, scale);
}