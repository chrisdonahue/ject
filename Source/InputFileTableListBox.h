/*
==============================================================================

InputFileTableListBox.h
Created: 6 May 2016 1:21:53pm
Author:  Chris

==============================================================================
*/

#ifndef INPUTFILETABLELISTBOX_H_INCLUDED
#define INPUTFILETABLELISTBOX_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class InputFileTableListBox : public TableListBox, public ChangeListener, public ChangeBroadcaster {
private:
	 class EditableTextCustomComponent  : public Label
    {
    public:
        EditableTextCustomComponent (TableDemoComponent& td)  : owner (td)
        {
            // double click to edit the label text; single click handled below
            setEditable (false, true, false);
            setColour (textColourId, Colours::black);
        }

        void mouseDown (const MouseEvent& event) override
        {
            // single click on the label should simply select the row
            owner.table.selectRowsBasedOnModifierKeys (row, event.mods, false);

            Label::mouseDown (event);
        }

        void textWasEdited() override
        {
            owner.setText (columnId, row, getText());
        }

        // Our demo code will call this when we may need to update our contents
        void setRowAndColumn (const int newRow, const int newColumn)
        {
            row = newRow;
            columnId = newColumn;
            setText (owner.getText(columnId, row), dontSendNotification);
        }

    private:
        TableDemoComponent& owner;
        int row, columnId;
    };

	enum Column {
		name = 1
	};

	class InputFileTableListBoxModel : public TableListBoxModel, public ChangeBroadcaster {
	public:
		InputFileTableListBoxModel() {};

		int getNumRows() override {
			return fileNames.size();
		};

		void paintRowBackground(Graphics& g, int rowNumber, int width, int height, bool rowIsSelected) override {
			if (rowIsSelected)
				g.fillAll(Colours::lightblue);
			else if (rowNumber % 2)
				g.fillAll(Colour(0xffeeeeee));
		};

		void paintCell(Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override {};

		Component* refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component *existingComponentToUpdate) override {
			if (columnId == Column::name) {
				Label* label = static_cast<Label*>(existingComponentToUpdate);

				if (label == nullptr) {
					label = new Label();
					label->setText(fileNames[rowNumber], dontSendNotification);
				}

				return label;
			}
			else {
				jassertfalse;
				return nullptr;
			}
		};

		void sortOrderChanged(int newSortColumnId, bool isForwards) override {
			jassertfalse;
		};

		void selectedRowsChanged(int lastRowSelected) override {
			sendChangeMessage();
		};

		void updateFileNames(const StringArray& fileNamesNew) {
			fileNames = fileNamesNew;
		};

	private:
		StringArray fileNames;
	};

public:
	InputFileTableListBox() {
		setModel(&model);
		setColour(ListBox::outlineColourId, Colours::grey);
		setClickingTogglesRowSelection(true);
		setMultipleSelectionEnabled(true);
		getHeader().addColumn("Name", Column::name, 128, 32, -1, TableHeaderComponent::visible | TableHeaderComponent::resizable);
		model.addChangeListener(this);
	};

	void changeListenerCallback(ChangeBroadcaster* source) override {
		if (source == &model) {
			sendChangeMessage();
		}
	};

	InputFileTableListBoxModel& getModel() {
		return model;
	}

private:
	InputFileTableListBoxModel model;
};

#endif  // INPUTFILETABLELISTBOX_H_INCLUDED