/*
  ==============================================================================

    InputFileTableListBox.h
    Created: 6 May 2016 1:37:15pm
    Author:  Chris

  ==============================================================================
*/

#ifndef INPUTFILETABLELISTBOX_H_INCLUDED
#define INPUTFILETABLELISTBOX_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class InputFileTableListBox : public TableListBox, public ChangeListener, public ChangeBroadcaster {
private:
	enum Column {
		name = 1,
		include
	};

	class InputFileTableListBoxModel : public TableListBoxModel, public ChangeBroadcaster, public ButtonListener {
	public:
		InputFileTableListBoxModel() {};

		int getNumRows() override {
			return 0;
		};

		void paintRowBackground(Graphics& g, int rowNumber, int width, int height, bool rowIsSelected) override {
			if (rowIsSelected)
				g.fillAll(Colours::lightblue);
			else if (rowNumber % 2)
				g.fillAll(Colour(0xffeeeeee));
		};

		void paintCell(Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override {

		};

		Component* refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component *existingComponentToUpdate) override {
			if (columnId == Column::name) {
				Label* label = static_cast<Label*>(existingComponentToUpdate);

				if (label == nullptr) {
					label = new Label();
					label->setText("lel", dontSendNotification);
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
		};

		void sortOrderChanged(int newSortColumnId, bool isForwards) override {

		};

		void selectedRowsChanged(int lastRowSelected) override {

		};

		void buttonClicked(Button* buttonThatWasClicked) override {
			sendChangeMessage();
		};
	private:
	};

public:
	InputFileTableListBox() {
		setModel(&model);
		setColour(ListBox::outlineColourId, Colours::grey);
		setClickingTogglesRowSelection(true);
		setMultipleSelectionEnabled(true);
		getHeader().addColumn("Name", Column::name, 32, 32, -1, TableHeaderComponent::visible | TableHeaderComponent::resizable);
		getHeader().addColumn("Use", Column::include, 32, 32, -1, TableHeaderComponent::visible);
		model.addChangeListener(this);
	};

	void changeListenerCallback(ChangeBroadcaster* source) override {
		if (source == &model) {
			sendChangeMessage();
		}
	};

	void resized() override {
		int toggleButtonComponentWidth = 32;
		getHeader().setColumnWidth(Column::name, getWidth() - toggleButtonComponentWidth);
		getHeader().setColumnWidth(Column::include, toggleButtonComponentWidth);
	};

	String getName(int row) {

	};

	void updateFileNames(const StringArray& rows) {

	};

private:
	InputFileTableListBoxModel model;
	StringArray fileNames;
};

/*
int toggleButtonComponentWidth = 32;
inputFileListComponent->getHeader().setColumnWidth(InputFileList::Column::name, inputFileListComponent->getWidth() - toggleButtonComponentWidth);
inputFileListComponent->getHeader().setColumnWidth(InputFileList::Column::include, toggleButtonComponentWidth);
*/
#endif  // INPUTFILETABLELISTBOX_H_INCLUDED