#include "light.h"

static float ratio = 40.0f;

b2Vec2 b2Scale(b2Vec2 vector, float scale ) {
	return b2Vec2(vector.x *  scale, vector.y * scale);
}

namespace GameEngine {
	Light::Light(World* _world, int _x, int _y, float _r, float _g, float _b, int _windowWidth, int _windowHeight, GLuint _shader) {
		world = _world;

		x = _x;
		y = _y;

		r = _r;
		g = _g;
		b = _b;

		windowWidth = _windowWidth;
		windowHeight = _windowHeight;

		shader = _shader;
	}

	/*
	I feel like I should explain what I am doing in this function.
	Light::render does not do what you would expect it to do

	it renders lights. You probably didn't guess that. Ik, pretty mysterious.
	All the way up to b2Vec2 vertex = poly->GetVertex(i); is just getting the vertices of the shapes of the fixture of the object.
	First we loop over every fixture, we get the shape, and we make sure it is a polygon.
	Then we loop over every vertex.
	Credits to https://github.com/jacobbrunson/BasicLighting/blob/master/src/Main.java#L32-L73
	for shadow algo. Credits to that one youtube video for the lighting shader.
	*/

	void Light::render() {
		glEnable(GL_BLEND);
		glEnable(GL_STENCIL_TEST);
		
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glColorMask(false, false, false, false);
		glStencilFunc(GL_ALWAYS, 1, 1);
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		//glStencilMask(1);
		
		std::vector<DynamicObject*> dynamicObjects = *world->getRenderList()->getDynamicObjects();
		std::vector<StaticObject*> staticObjects = *world->getRenderList()->getStaticObjects();
	
		DynamicObject* dynObj;
		StaticObject* statObj;
		
		b2Body* body;
		b2Shape* shape;
		b2Vec2 lightLoc = b2Vec2(x, y);
		
		for (unsigned int i = 0; i < dynamicObjects.size(); i++) {
			dynObj = dynamicObjects[i];
			body = dynObj->getBody();
			
			for(b2Fixture* f = body->GetFixtureList(); f; f = f->GetNext()) {
				shape = f->GetShape();
				if(shape->GetType() == b2Shape::e_polygon) {
					b2PolygonShape* poly = (b2PolygonShape*)shape;
					int count = poly->GetVertexCount();
					for(int i = 0; i < count; i++) {
						b2Vec2 vertex = poly->GetVertex(i);
						vertex = b2Vec2(vertex.x * ratio, vertex.y * ratio);
						b2Vec2 nextvertex = poly->GetVertex((i + 1) % count);
						nextvertex = b2Vec2(nextvertex.x * ratio, nextvertex.y * ratio);
						b2Vec2 edge = nextvertex - vertex;
						b2Vec2 normal = b2Vec2(edge.y, -edge.x);
						b2Vec2 lightToCurrent = vertex - lightLoc;
						if(b2Dot(normal, lightToCurrent) > 0.0f) {
							b2Vec2 point1 = vertex + b2Scale(lightToCurrent, 800.0f);
							b2Vec2 point2 = vertex + b2Scale(nextvertex - lightLoc, 800.0f);
							glColor4f(0.0f, 0.0f, 0.0f, 0.5f);
							glBegin(GL_QUADS); {
								glVertex2f(vertex.x, vertex.y);
								glVertex2f(point1.x, point1.y);
								glVertex2f(point2.x, point2.y);
								glVertex2f(nextvertex.x, nextvertex.y);
							} glEnd();
						}
					}
				}	
			}
		}
		for (unsigned int i = 0; i < staticObjects.size(); i++) {
			statObj = staticObjects[i];
			body = statObj->getBody();
			for(b2Fixture* f = body->GetFixtureList(); f; f = f->GetNext()) {
				shape = f->GetShape();
				if(shape->GetType() == b2Shape::e_polygon) {
					b2PolygonShape* poly = (b2PolygonShape*)shape;
					int count = poly->GetVertexCount();

					for(int i = 0; i < count; i++) {
						b2Vec2 vertex = poly->GetVertex(i);
						vertex = b2Vec2(vertex.x * ratio, vertex.y * ratio);
						
						b2Vec2 nextvertex = poly->GetVertex((i + 1) % count);
						nextvertex = b2Vec2(nextvertex.x * ratio, nextvertex.y * ratio);
						
						b2Vec2 edge = nextvertex - vertex;
						b2Vec2 normal = b2Vec2(edge.y, -edge.x);
						b2Vec2 lightToCurrent = vertex - lightLoc;

						if(b2Dot(normal, lightToCurrent) > 0.0f) {
							
							b2Vec2 point1 = vertex + b2Scale(lightToCurrent, 80.0f);
							b2Vec2 point2 = vertex + b2Scale(nextvertex - lightLoc, 80.0f);
							
							float offsetX = body->GetPosition().x * ratio;
							float offsetY = body->GetPosition().y * ratio;
						
							glBegin(GL_QUADS); {
							
								glVertex2f(vertex.x + offsetX, vertex.y + offsetY);
								glVertex2f(point1.x + offsetX, point1.y + offsetY);
								glVertex2f(point2.x + offsetX, point2.y + offsetY);
								glVertex2f(nextvertex.x + offsetX, nextvertex.y + offsetY);
						
							} glEnd();
						}
					}
				}	
			}
		}

		glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
		glStencilFunc(GL_EQUAL, 0, 1);
		glColorMask(true, true, true, true);

		glUseProgram(shader);
		glUniform2f(glGetUniformLocation(shader,"lightpos"), x, y);
		glUniform3f(glGetUniformLocation(shader,"lightColor"), 1.0, 0.0, 1.0);
		glUniform1f(glGetUniformLocation(shader,"screenHeight"), windowHeight);
		glUniform1f(glGetUniformLocation(shader,"radius"), 10);


		glBegin(GL_QUADS); {
			glVertex2f(0, 0);
			glVertex2f(0, windowHeight);
			glVertex2f(windowWidth, windowHeight);
			glVertex2f(windowWidth, 0);
		} glEnd();

		

		glUseProgram(0);
		glClear(GL_STENCIL_BUFFER_BIT);
		glDisable(GL_STENCIL_TEST);
		glDisable(GL_BLEND);
	}

	void Light::clean() {
		
	}
}