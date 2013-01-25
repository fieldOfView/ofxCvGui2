#include "ofxCvGui/Panels/Node.h"

namespace ofxCvGui {
	namespace Panels {
		//----------
		Node::Node(ofNode & node) {
			this->push(node);
			this->gridColor = ofColor(90, 50, 50);
			this->gridEnabled = true;
			this->gridLabelsEnabled = true;
		}

		//----------
		void Node::drawContent(DrawArguments& arguments) {
			this->camera.begin(this->getBounds());

			if (this->gridEnabled) {
				ofPushStyle();
				ofSetColor(this->gridColor);
				ofDrawGrid(gridScale, 5.0f, this->gridLabelsEnabled);
				ofPopStyle();
			}

			vector<ofNode*>::iterator it;
			for (it = this->nodes.begin(); it != this->nodes.end(); it++)
				(**it).draw();

			this->camera.end();
		}

		//----------
		void Node::setGridEnabled(bool gridEnabled) {
			this->gridEnabled = gridEnabled;
		}
		
		//----------
		void Node::setGridColor(const ofColor & gridColor) {
			this->gridColor = gridColor;
		}
		
		//----------
		void Node::setGridScale(const float gridScale) {
			this->gridScale = gridScale;
		}

		//----------
		void Node::setGridLabelsEnabled(bool gridLabelsEnabled) {
			this->gridLabelsEnabled = gridLabelsEnabled;
		}

		//----------
		void Node::push(ofNode & node) {
			this->nodes.push_back(&node);
		}
	}
}