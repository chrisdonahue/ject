/*
  ==============================================================================

    PolygonSliderComponent.h
    Created: 29 Apr 2016 5:24:00pm
    Author:  Chris

  ==============================================================================
*/

#ifndef POLYGONSLIDERCOMPONENT_H_INCLUDED
#define POLYGONSLIDERCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class PolygonSliderComponent    : public Component, public MouseListener, public ChangeBroadcaster
{
public:
    PolygonSliderComponent();
    ~PolygonSliderComponent();

	void paint(Graphics&) override;

	void mouseDrag(const MouseEvent &event) override;

	void addVertex(int id, String name);
	void removeVertex(int id);
	const HashMap<int, float>& getValues();

private:
	HashMap<int, String> idToName;
	HashMap<int, float> idToValue;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PolygonSliderComponent)
};


#endif  // POLYGONSLIDERCOMPONENT_H_INCLUDED
