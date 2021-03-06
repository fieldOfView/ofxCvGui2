#pragma once
#include "../Element.h"

namespace ofxCvGui {
	namespace Utils {
		class Button : public Element {
		public:
			Button();
			~Button();
			ofxLiquidEvent<ofVec2f> onHit; ///< returns mouse coords in local normalised
			ofxLiquidEvent<DrawArguments> onDrawUp;
			ofxLiquidEvent<DrawArguments> onDrawDown;
			bool isDown() { return this->down; }
		protected:
			bool down;
		};
	}
}