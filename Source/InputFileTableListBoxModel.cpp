/*
  ==============================================================================

    InputFileList.cpp
    Created: 29 Apr 2016 5:42:23pm
    Author:  Chris

  ==============================================================================
*/

#include "InputFileList.h"

InputFileList::InputFileList() {};

int InputFileList::getNumRows() {
	return fileNames.size();
}

void InputFileList::paintRowBackground(Graphics& g, int rowNumber, int width, int height, bool rowIsSelected) {
	if (rowIsSelected)
		g.fillAll(Colours::lightblue);
	else if (rowNumber % 2)
		g.fillAll(Colour(0xffeeeeee));
};



void InputFileList::paintCell(Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected) {
	if (columnId == Column::include) {
		g.drawText(fileNames[rowNumber], 2, 0, width - 4, height, Justification::centredLeft, true);
	}
	/*
	g.setColour(Colours::black);
	//g.setFont(font);

	if (const XmlElement* rowElement = dataList->getChildElement(rowNumber))
	{
		const String text(rowElement->getStringAttribute(getAttributeNameForColumnId(columnId)));

		g.drawText(text, 2, 0, width - 4, height, Justification::centredLeft, true);
	}

	g.setColour(Colours::black.withAlpha(0.2f));
	g.fillRect(width - 1, 0, 1, height);
	*/
}

Component* InputFileList::refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component *existingComponentToUpdate) {
	if (columnId == Column::name) {
		Label* label = static_cast<Label*>(existingComponentToUpdate);

		if (label == nullptr) {
			label = new Label();
			label->setText(fileNames[rowNumber], dontSendNotification);
		}

		return label;
	}
	else if (columnId == Column::include) {
		ToggleButton* toggleButton = static_cast<ToggleButton*>(existingComponentToUpdate);

		if (toggleButton == nullptr) {
			toggleButton = new ToggleButton();
			toggleButton->setToggleState(true, dontSendNotification);
			toggleButton->addListener(this);
		}

		return toggleButton;
	}
	else {
		jassertfalse;
		return nullptr;
	}
}

void InputFileList::sortOrderChanged(int newSortColumnId, bool isForwards) {
	sendChangeMessage();
}

void InputFileList::selectedRowsChanged(int lastRowSelected) {
	sendChangeMessage();
};

void InputFileList::buttonClicked(Button* buttonThatWasClicked) {
	sendChangeMessage();
}

String InputFileList::getName(int row) {
	return fileNames[row];
}

void InputFileList::updateFileNames(const StringArray& fileNamesNew) {
	fileNames = fileNamesNew;
}