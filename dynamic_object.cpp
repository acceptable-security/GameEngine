#include <Box2D/Box2D.h>
#include <glut.h>
#include "object.h"
#include "dynamic_object.h"

int PI = 3.14159265f;
static float ratio = 40.0f;

namespace GameEngine {
	DynamicObject::DynamicObject(const char* _imageFile, float _scale, b2Vec2 pos, b2World* world, int wWidth, int wHeight) {
		scale = _scale;
	
		gLoadedTexture = Image(_imageFile);
		imageFile = _imageFile;
	
		x = pos.x;
		y = pos.y;
	
		width = gLoadedTexture.width * scale;
		height = gLoadedTexture.height * scale;	
		
		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set(x/ratio, y/ratio);
	
		body = world->CreateBody(&bodyDef);
		bodyData* data = new bodyData();
		data->type = "dynamic";
		data->object = this;
		body->SetUserData(data);
		b2DataPtr = data;
		vertices[0].Set(0,0);
		vertices[1].Set(0,height/ratio);
		vertices[2].Set(width/ratio, height/ratio);
		vertices[3].Set(width/ratio, 0);
		box.Set(vertices,4);
		
		fixtureDef.shape = &box;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.3f;
	
		body->CreateFixture(&fixtureDef);
	
		winWidth = wWidth;
		winHeight = wHeight;
	}
	
	void DynamicObject::WindowResize(int wWidth, int wHeight) {
	}
	
	void DynamicObject::SetPosition(int _x, int _y) {
		bodyDef.position.Set(_x/ratio,  _y/ratio);
		body->SetTransform(b2Vec2(_x/ratio, _y/ratio), body->GetAngle());
	}
	
	void DynamicObject::resize(int _width, int _height) { 
		width = _width;
		height = _height;
		
		box.SetAsBox((_width/2.0)/ratio, (_height/2.0)/ratio);
	}
	void DynamicObject::render() {
		drawImage();
	}

	void DynamicObject::drawImage() {
		x = body->GetPosition().x*ratio;
		y = body->GetPosition().y*ratio;
		gLoadedTexture.render(x,y, body->GetAngle() * (180.0f / PI), scale);
	}

	void DynamicObject::_clean() {
		delete b2DataPtr;
		clean();
	}

	void DynamicObject::clean() {
	}

	void DynamicObject::startContact() {
	}

	void DynamicObject::endContact() {
	}
}