#include "dynamic_object.h"
#include "static_object.h"
#include <vector>
namespace GameEngine {
	class RenderList {
		private:
			std::vector<DynamicObject*> dynamicObjectList;
			std::vector<StaticObject*> staticObjectList;
	
		public:
			RenderList();
			void add(DynamicObject* obj);
			void add(StaticObject* obj);

			std::vector<DynamicObject*>* getDynamicObjects() { return &dynamicObjectList; };
			std::vector<StaticObject*>* getStaticObjects() { return &staticObjectList; };
	
			void render();
			void clean();
	};
}