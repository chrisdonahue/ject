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

class InputFileList : public TableListBoxModel, public ChangeBroadcaster, public ButtonListener
{
public:
	InputFileList();

	int getNumRows() override;
	void paintRowBackground(Graphics& g, int rowNumber, int width, int height, bool rowIsSelected) override;
	void paintCell(Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;
	Component* refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component *existingComponentToUpdate) override;
	void sortOrderChanged(int newSortColumnId, bool isForwards) override;
	void selectedRowsChanged(int lastRowSelected) override;
	void buttonClicked(Button* buttonThatWasClicked) override;

	String getName(int row);
	void updateFileNames(const StringArray& rows);

	enum Column {
		name=1,
		include
	};

private:
	StringArray fileNames;
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(InputFileList)
};

#endif  // INPUTFILELIST_H_INCLUDED