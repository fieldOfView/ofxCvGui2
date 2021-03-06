#include "ofxCvGui/Element.h"
namespace ofxCvGui {
	//-----------
	Element::Element() {
		this->enabled = true;
		this->enableScissor = false;
		this->localMouseState = Waiting;
	}

	//-----------
	void Element::update() {
		if (this->enabled) {
			UpdateArguments args;
			onUpdate.notifyListeners(args);
		}
    }
    
    //-----------
	void Element::draw(DrawArguments& arguments) {
		if (this->enabled) {
			ofPushMatrix();
			ofTranslate(bounds.x, bounds.y);
			if (this->enableScissor) {
				ofxCvGui::Utils::pushScissor(arguments.globalBounds);
			}
			this->onDraw(arguments);
			if (this->enableScissor) {
				ofxCvGui::Utils::popScissor();
			}
			ofPopMatrix();
		}
	}
    
    //-----------
    void Element::mouseAction(MouseArguments& args) {
		if (this->enabled) {
			auto localArgs = MouseArguments(args, this->getBounds());
			if(args.action == MouseArguments::Pressed) {
				//special case for pressed, only pass if local
				if (localArgs.isLocal()) {
					this->onMouse(localArgs);
					if (localArgs.isTaken()) {
						args.take(); // if this element took, notify upstream
					}
				}
			} else if (args.action == MouseArguments::Dragged) {
				//special case for dragged, only pass if mouse went down in this element
				if (this->localMouseState == Dragging) {
					this->onMouse(localArgs);
				}
			} else {
				this->onMouse(localArgs);
			}

			if (localArgs.isLocalPressed()) {
				this->localMouseState = Down;
			} else if (localArgs.action == MouseArguments::Dragged) {
				if (this->localMouseState == Down) {
					this->localMouseState = Dragging;
				}
			} else if (localArgs.action == MouseArguments::Released) {
				if (this->localMouseState == Down) {
					this->onMouseReleased(localArgs);
				}
				this->localMouseState = Waiting;
			}
		}
    }
    
    //-----------
    void Element::keyboardAction(KeyboardArguments &arguments) {
		if (this->enabled) {
			this->onKeyboard(arguments);
		}
    }

    //-----------
	void Element::clearMouseState() {
		this->localMouseState = Waiting;
	}

    //-----------
	Element::LocalMouseState Element::getMouseState() {
		return this->localMouseState;
	}

	//-----------
	void Element::setBounds(const ofRectangle& bounds) {
		this->bounds = bounds;
		this->localBounds = bounds;
		this->localBounds.x = 0;
		this->localBounds.y = 0;
        
		auto arguments = BoundsChangeArguments(this->bounds);
		this->onBoundsChange(arguments);
	}

	//-----------
	void Element::arrange() {
		auto arguments = BoundsChangeArguments(this->bounds);
		this->onBoundsChange(arguments);
	}

	//-----------
	void Element::setWidth(float width) {
		auto bounds = this->getBounds();
		bounds.setWidth(width);
		this->setBounds(bounds);
	}

	//-----------
	void Element::setHeight(float height) {
		auto bounds = this->getBounds();
		bounds.setHeight(height);
		this->setBounds(bounds);
	}

	//-----------
	void Element::setPosition(const ofVec2f& position) {
		this->bounds.x = position.x;
		this->bounds.y = position.y;
		auto arguments = BoundsChangeArguments(this->bounds);
		this->onBoundsChange(arguments);
	}

	//-----------
	const ofRectangle& Element::getBounds() const{
		return this->bounds;
	}

	//-----------
	float Element::getWidth() const {
		return this->getBounds().width;;
	}

	//-----------
	float Element::getHeight() const{
		return this->getBounds().height;
	}

	//-----------
	void Element::setCaption(string caption) {
		this->caption = caption;
		this->onCaptionChange(caption);
	}
	
	//-----------
	void Element::setEnabled(bool enabled) {
		this->enabled = enabled;
	}

	//-----------
	bool Element::getEnabled() const {
		return this->enabled;
	}

	//-----------
	void Element::enable() {
		this->enabled = true;
	}

	//-----------
	void Element::disable() {
		this->enabled = false;
	}

	//-----------
	void Element::setScissor(bool enableScissor) {
		this->enableScissor = enableScissor;
	}
}