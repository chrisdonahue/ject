/*
  ==============================================================================

    InputFileList.cpp
    Created: 29 Apr 2016 5:42:23pm
    Author:  Chris

  ==============================================================================
*/

#include "InputFileList.h"

InputFileList::InputFileList() {};

void InputFileList::paintListBoxItem(int row, Graphics& g, int w, int h, bool rowIsSelected) {
	if (rowIsSelected)
		g.fillAll(LookAndFeel::getDefaultLookAndFeel().findColour(TextEditor::highlightColourId));

	const Font f(h * 0.7f);
	g.setColour(Colours::black);
	g.setFont(f);
	g.drawText(tests[row], Rectangle<int>(0, 0, w, h).reduced(2),
		Justification::centredLeft, true);
};

void InputFileList::selectedRowsChanged(int lastRowSelected) {
	sendChangeMessage();
}