/*
  ==============================================================================

    PolygonSliderComponent.cpp
    Created: 29 Apr 2016 5:24:00pm
    Author:  Chris

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "PolygonSliderComponent.h"

//==============================================================================
PolygonSliderComponent::PolygonSliderComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

PolygonSliderComponent::~PolygonSliderComponent()
{
}

void PolygonSliderComponent::paint (Graphics& g)
{
	//g.fillAll(Colours::white);
	g.setColour(Colours::grey);
	g.drawRect(getLocalBounds(), 1);
	g.setColour(Colours::lightblue);
	g.setFont(14.0f);

	int numVertices = idToValue.size();
	if (numVertices == 0) {
		g.drawText("Add some sounds!", getLocalBounds(), Justification::centred, true);
	}
	else if (numVertices == 1) {
		g.drawText("Add more sounds!", getLocalBounds(), Justification::centred, true);
	}
	else {
		float width = static_cast<float>(getWidth());
		float height = static_cast<float>(getHeight());
		float r = width > height ? width / 2.0f : height / 2.0f;
	}
}

void PolygonSliderComponent::mouseDrag(const MouseEvent &event) {
	sendChangeMessage();
}

void PolygonSliderComponent::addVertex(int id, String name) {
	idToName.set(id, name);
	idToValue.set(id, 1.0f);
}

void PolygonSliderComponent::removeVertex(int id) {
	idToName.remove(id);
	idToValue.remove(id);
}

const HashMap<int, float>& PolygonSliderComponent::getValues() {
	return idToValue;
}