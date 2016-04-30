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
class PolygonSliderComponent    : public Component
{
public:
    PolygonSliderComponent();
    ~PolygonSliderComponent();

    void paint (Graphics&);
    void resized();

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PolygonSliderComponent)
};


#endif  // POLYGONSLIDERCOMPONENT_H_INCLUDED
