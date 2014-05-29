#include "render_list.h"
#include <vector>

namespace GameEngine {
	RenderList::RenderList() {
	}

	void RenderList::add(DynamicObject* obj) {
		dynamicObjectList.push_back(obj);
	}
	
	void RenderList::add(StaticObject* obj) {
		staticObjectList.push_back(obj);	
	}	

	void RenderList::render() {
		for (unsigned int i = 0; i < dynamicObjectList.size(); i++) {
			dynamicObjectList[i]->render();
		}
		for (unsigned int i = 0; i < staticObjectList.size(); i++) {
			staticObjectList[i]->render();
		}
	}
	
	void RenderList::clean() {
		for (unsigned int i = 0; i < dynamicObjectList.size(); i++) {
			dynamicObjectList[i]->_clean();
			delete dynamicObjectList[i];
		}
		for (unsigned int i = 0; i < staticObjectList.size(); i++) {
			staticObjectList[i]->_clean();
			delete staticObjectList[i];
		}
	}
}