#include "Inspector.h"
#include "../Widgets/IInspectable.h"
#include "../Widgets/Title.h"

namespace ofxCvGui {
	using namespace Widgets;

	namespace Panels {
		//---------
		Inspector::Inspector() {
			Inspector::makeNewSelection.addListener([this] (IInspectable & object) {
				this->clear();
				object.populateInspector(this->elements);
				this->arrange();
			}, this);

			Inspector::makeNoSelection.addListener([this] (IInspectable & object) {
				this->clear();
			}, this);

			Inspector::addWidgetEvent.addListener([this] (ElementPtr & widget) {
				this->add(widget);
				this->arrange();
			}, this);

			this->clear();
		}

		//---------
		Inspector::~Inspector() {
			//not sure if this gets deleted last?
			//Inspector::makeNewSelection.removeListeners(this);
			//Inspector::makeNoSelection.removeListeners(this);
			//Inspector::addWidgetEvent.removeListeners(this);
		}

		//---------
		void Inspector::clear() {
			Inspector::selection.clear();
			this->elements->clear();
			this->elements->add(shared_ptr<Title>(new Title("Inspector", Title::Level::H1)));
			this->onClear(this->elements);
			this->arrange();
		}

		//---------
		void Inspector::select(IInspectable & object) {
			if (Inspector::isSelected(object)) {
				Inspector::makeNoSelection(object);
				Inspector::selection.clear();
			} else {
				Inspector::makeNewSelection(object);
				Inspector::selection.insert(&object);
			}
		}

		//---------
		void Inspector::setSelection(IInspectable & object) {
			Inspector::makeNewSelection(object);
			Inspector::selection.insert(&object);
		}

		//---------
		bool Inspector::isSelected(Widgets::IInspectable & object) {
			return Inspector::selection.count(&object) > 0;
		}

		//---------
		const set<Widgets::IInspectable *> Inspector::getSelection() {
			return Inspector::selection;
		}

		//---------
		void Inspector::addWidget(ElementPtr widget) {
			Inspector::addWidgetEvent(widget);
		}
		
		//---------
		void Inspector::refresh() {
			auto selection = Inspector::getSelection();
			if (selection.empty()) {
				Inspector::makeNoSelection(**selection.begin()); // call dummy function with invalid
				Inspector::selection.clear();
			} else {
				Inspector::makeNewSelection(**selection.begin()); // only add first, no multiple selection
				Inspector::selection.insert(*selection.begin());
			}
		}

		//---------
		ofxLiquidEvent<ElementGroupPtr> Inspector::onClear = ofxLiquidEvent<ElementGroupPtr>();

		//---------
		ofxLiquidEvent<IInspectable> Inspector::makeNewSelection = ofxLiquidEvent<IInspectable>();
		ofxLiquidEvent<IInspectable> Inspector::makeNoSelection = ofxLiquidEvent<IInspectable>();

		//---------
		ofxLiquidEvent<ElementPtr> Inspector::addWidgetEvent = ofxLiquidEvent<ElementPtr>();

		//---------
		set<Widgets::IInspectable *> Inspector::selection = set<Widgets::IInspectable *>();
	}
}
