#include "Toggle.h"
#include "../../../addons/ofxAssets/src/ofxAssets.h"

using namespace ofxAssets;

namespace ofxCvGui {
	namespace Widgets {
		//----------
		Toggle::Toggle(ofParameter<bool> & parameter) {
			this->setParameter(parameter);
			this->localAllocation = false;
			this->init();
			this->setCaption(this->value->getName());
		}

		//----------
		Toggle::Toggle() {
			this->value = nullptr;
			this->localAllocation = false;
			this->init();
		}

		//----------
		Toggle::Toggle(string caption) {
			this->setParameter(* new ofParameter<bool>(caption, false));
			this->localAllocation = true;
			this->init();
		}

		//----------
		Toggle::~Toggle() {
			if(this->localAllocation) {
				delete this->value;
			}
		}

		//----------
		void Toggle::init() {
			this->setBounds(ofRectangle(5, 0, 100, 40));

			this->onUpdate += [this] (UpdateArguments & args) {
				this->update(args);
			};
			this->onDraw += [this] (DrawArguments & args) {
				this->draw(args);
			};
			this->onMouse += [this] (MouseArguments & args) {
				this->mouseAction(args);
			};
			this->onBoundsChange += [this] (BoundsChangeArguments & args) {
				this->boundsChange(args);
			};
			
			this->isMouseOver = false;
			this->isMouseDown = false;
		}

		//----------
		void Toggle::setParameter(ofParameter<bool> & parameter) {
			this->value = & parameter;
			this->setCaption(this->value->getName());
		}

		//----------
		ofParameter<bool> & Toggle::getParameter() {
			return * this->value;
		}

		//----------
		void Toggle::update(UpdateArguments &) {

		}

		//----------
		void Toggle::draw(DrawArguments & args) {
			if (!this->value) {
				//nothing allocated
				return;
			}

			auto & font = ofxAssets::AssetRegister.getFont(ofxCvGui::defaultTypeface, 12);

			ofPushStyle();
			
			//fill
			ofSetColor(this->value->get() ^ this->isMouseDown ?  80 : 50);
			ofFill();
			const auto radius = 5.0f;
			ofRectRounded(this->buttonBounds, radius, radius, radius, radius);
			
			//outline
			if (this->isMouseOver) {
				ofNoFill();
				ofSetColor(!this->value->get() ?  80 : 50);
				ofRectRounded(this->buttonBounds, radius, radius, radius, radius);
			}

			ofSetColor(255);
			const auto textBounds = font.getStringBoundingBox(this->caption, 0, 0);
			font.drawString(this->caption, (int) ((this->buttonBounds.width - textBounds.width) / 2.0f), (int) ((this->buttonBounds.height + textBounds.height) / 2.0f));
			
			ofPopStyle();

			//draw side marker
			ofPushStyle();
			ofSetLineWidth(1.0f);
			ofLine(this->getWidth(), 0, this->getWidth(), this->buttonBounds.getHeight());
			ofPopStyle();
		}

		//----------
		void Toggle::mouseAction(MouseArguments & args) {
			if (!this->value) {
				//nothing allocated
				return;
			}

			this->isMouseOver = this->buttonBounds.inside(args.local);

			switch(args.action) {
			case MouseArguments::Pressed:
				this->isMouseDown = this->isMouseOver;
				break;
			case MouseArguments::Released:
				if (this->isMouseDown) {
					this->value->set(! this->value->get());
					this->notifyValueChange();
				}
				this->isMouseDown = false;
				break;
			}
		}

		//----------
		void Toggle::boundsChange(BoundsChangeArguments & args) {
			this->buttonBounds = args.localBounds;
			buttonBounds.height -= 10;
			buttonBounds.width -= 10;
		}

		//----------
		void Toggle::notifyValueChange() {
			this->onValueChange.notifyListeners(* this->value);
		}
	}
}