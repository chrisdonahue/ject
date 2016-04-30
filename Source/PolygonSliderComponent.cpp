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
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (Colours::white);   // clear the background

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (Colours::lightblue);
    g.setFont (14.0f);
    g.drawText ("PolygonSliderComponent", getLocalBounds(),
                Justification::centred, true);   // draw some placeholder text
}

void PolygonSliderComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
