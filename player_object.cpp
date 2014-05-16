#include <Box2D/Box2D.h>
#include <glut.h>
#include "player_object.h"
//int PI = 3.14159265f;
static float ratio = 40.0f;
PlayerObject::PlayerObject(int _width, int _height, float _x, float _y, float _r, float _g, float _b, b2World* world, int wWidth, int wHeight) {
	state = "idle";
	direction = "right";
	
	bodyDef.type = b2_dynamicBody;
	bodyDef.linearDamping = 1.0f;
	bodyDef.fixedRotation = true;
	bodyDef.position.Set(_x/ratio, _y/ratio);

	body = world->CreateBody(&bodyDef);
	body->SetUserData(this);
	vertices[0].Set(0,0);
	vertices[1].Set(0,_height/ratio);
	vertices[2].Set(_width/ratio, _height/ratio);
	vertices[3].Set(_width/ratio, 0);
	box.Set(vertices,4);
	
	fixtureDef.shape = &box;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 5.0f;

	body->CreateFixture(&fixtureDef);

	r = _r;
	g = _g;
	b = _b;
	
	width = _width;
	height = _height;
	
	x = _x;
	y = _y;

	winWidth = wWidth;
	winHeight = wHeight;

	//termX = body->GetMass() * 1.5f;
}

void PlayerObject::update(bool up, bool down, bool left, bool right) {
	b2Vec2 linVel = body->GetLinearVelocity();
	if(up) {
		if(linVel.y == 0) {
			body->ApplyLinearImpulse( b2Vec2(0, body->GetMass() * 5), body->GetWorldCenter(), true );
		}
	}
	if(left) {
		body->ApplyLinearImpulse( b2Vec2(body->GetMass() * -0.5, 0.0 ), body->GetWorldCenter(), true );
	}
	if(right) { 
		body->ApplyLinearImpulse( b2Vec2(body->GetMass() * 0.5, 0.0 ), body->GetWorldCenter(), true );
	}

	b2Vec2 vel = body->GetLinearVelocity();
	if(vel.y > 1.0f) {
		state = "jump";
	}
	else {
		if(vel.y < -1.0f) {
			state = "fall";
		}
		else {
			state = "idle";
		}
	}

	if(vel.x > 1.0f) {
		state = "move";
		direction = "right";
	}
	if(vel.x < -1.0f) {
		state = "move";
		direction = "left";
	}
	//printf("%s %s\n", state, direction);
}

void PlayerObject::WindowResize(int wWidth, int wHeight) {
}

void PlayerObject::SetPosition(int _x, int _y) {
	bodyDef.position.Set(_x/ratio,  _y/ratio);
	body->SetTransform(b2Vec2(_x/ratio, _y/ratio), body->GetAngle());
}

void PlayerObject::resize(int _width, int _height) { 
	width = _width;
	height = _height;
	
	box.SetAsBox((_width/2.0)/ratio, (_height/2.0)/ratio);
}

void PlayerObject::debug() {
	printf("RECT (%d, %d, %d, %d)\n", x, y, width, height);
}

void PlayerObject::render() {
	x = body->GetPosition().x*ratio;
	y = body->GetPosition().y*ratio;

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glTranslatef(x, y, 0.0f);
	glRotatef(body->GetAngle() * (180.0f / 3.14159265f), 0.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS);
	glColor3f(r, g, b);
	glVertex2f(0.0,0.0);
	glVertex2f(width,0.0);
	glVertex2f(width,height);
	glVertex2f(0.0,height);
	glEnd();
}