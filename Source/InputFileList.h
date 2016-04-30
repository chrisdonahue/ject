/*
  ==============================================================================

    InputFileList.h
    Created: 29 Apr 2016 5:42:23pm
    Author:  Chris

  ==============================================================================
*/

#ifndef INPUTFILELIST_H_INCLUDED
#define INPUTFILELIST_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class InputFileList : public ListBoxModel, public ChangeBroadcaster
{
public:
	InputFileList();

	int getNumRows() override { return 0; }
	void paintListBoxItem(int row, Graphics& g, int w, int h, bool rowIsSelected) override;
	void selectedRowsChanged(int lastRowSelected) override;

private:
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(InputFileList)
};

#endif  // INPUTFILELIST_H_INCLUDED