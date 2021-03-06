#include "ofxCvGui/Types.h"
namespace ofxCvGui {
#pragma mark DrawArguments
	//----------
	DrawArguments::DrawArguments(const ofRectangle& parentBounds, const ofRectangle& globalBounds, bool chromeEnabled) :
		parentBounds(parentBounds),
		globalBounds(globalBounds),
		chromeEnabled(chromeEnabled),
		localBounds(0, 0, parentBounds.width, parentBounds.height)
	{ }

#pragma mark MouseArguments
	//----------
	MouseArguments::MouseArguments(const ofMouseEventArgs& mouseArgs, Action action, const ofRectangle& rectangle, const shared_ptr<void>& currentPanel, const ofVec2f& cached) :
		action(action),
		button(mouseArgs.button),
		global(mouseArgs.x, mouseArgs.y),
		local(mouseArgs.x - rectangle.x, mouseArgs.y - rectangle.y),
		localNormalised(local / ofVec2f(rectangle.width, rectangle.height)),
        movement(action == Dragged ? global - cached : ofVec2f()),
		taken(false),
        InputArguments(currentPanel)
	{ }

	//----------
	MouseArguments::MouseArguments(const MouseArguments& parentArguments, const ofRectangle& childBounds) :
        action(parentArguments.action),
        button(parentArguments.button),
        global(parentArguments.global),
        local(parentArguments.local - ofVec2f(childBounds.x, childBounds.y)),
        localNormalised(local / ofVec2f(childBounds.width, childBounds.height)),
        movement(parentArguments.movement),
		taken(false),
        InputArguments(parentArguments.currentPanel)
	{ }

	//----------
	bool MouseArguments::isLocal() const {
		ofRectangle testBounds(0, 0, 1, 1);
		return testBounds.inside(localNormalised);
	}

	//----------
	bool MouseArguments::isLocalPressed() const {
		return action == Pressed && isLocal();
	}

	//----------
	bool MouseArguments::isTaken() const {
		return this->taken;
	}

	//----------
	void MouseArguments::take() {
		this->taken = true;
	}

	//----------
	ostream& operator<<(ostream& os, const MouseArguments & args) {
		os << "[MouseAction : " << args.action << ", " << args.button << ", " << args.global << ", " << args.local << ", " << args.localNormalised << ", " << args.movement << "]";
		return os;
	}

#pragma mark KeyboardArguments
	//----------
	KeyboardArguments::KeyboardArguments(const ofKeyEventArgs& keyboardArgs, Action action, shared_ptr<void> currentPanel) :
		action(action),
		key(keyboardArgs.key),
        InputArguments(currentPanel)
	{ }
	
#pragma mark BoundsChangeArguments
	//----------
	BoundsChangeArguments::BoundsChangeArguments(const ofRectangle & bounds) :
		bounds(bounds),
		localBounds(0.0f, 0.0f, bounds.width, bounds.height)
	{ }

#pragma mark FilesDraggedArguments
	//----------
	FilesDraggedArguments::FilesDraggedArguments(const ofVec2f & localPosition, const ofVec2f & globalPosition, const vector<string> & files) :
		localPosition(localPosition), globalPosition(globalPosition), files(files)
	{ }
}