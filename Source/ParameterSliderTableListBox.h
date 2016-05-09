/*
  ==============================================================================

    ParameterSliderTableListBox.h
    Created: 6 May 2016 1:21:53pm
    Author:  Chris

  ==============================================================================
*/

#ifndef PARAMETERSLIDERTABLELISTBOX_H_INCLUDED
#define PARAMETERSLIDERTABLELISTBOX_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class ParameterSliderTableListBox : public TableListBox, public ChangeListener, public ChangeBroadcaster {
private:
	enum Column {
		name=1,
		slider
	};

	class ParameterSliderTableListBoxModel : public TableListBoxModel, public ChangeBroadcaster, public SliderListener {
	public:
		ParameterSliderTableListBoxModel() {};

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
			else if (columnId == Column::slider) {
				Slider* slider = static_cast<Slider*>(existingComponentToUpdate);

				if (slider == nullptr) {
					slider = new Slider();
					slider->setRange(0.0, 1.0, 0.01);
					slider->addListener(this);
				}

				return slider;
			}
			else {
				jassertfalse;
				return nullptr;
			}
		};

		void sortOrderChanged(int newSortColumnId, bool isForwards) override {
			jassertfalse;
		};

		void selectedRowsChanged(int lastRowSelected) override {};

		void sliderValueChanged(Slider* slider) override {
			sendChangeMessage();
		};

		String getName(int row) const {
			return fileNames[row];
		};

		void updateFileNames(const StringArray& fileNamesNew) {
			fileNames = fileNamesNew;
		};

	private:
		StringArray fileNames;
	};

public:
	ParameterSliderTableListBox(String paramName) {
		setModel(&model);
		setColour(ListBox::outlineColourId, Colours::grey);
		setClickingTogglesRowSelection(true);
		setMultipleSelectionEnabled(false);
		getHeader().addColumn("Name", Column::name, 32, 32, -1, TableHeaderComponent::visible | TableHeaderComponent::resizable);
		getHeader().addColumn(paramName, Column::slider, 32, 32, -1, TableHeaderComponent::visible | TableHeaderComponent::resizable);
		model.addChangeListener(this);
	};

	void changeListenerCallback(ChangeBroadcaster* source) override {
		if (source == &model) {
			sendChangeMessage();
		}
	};

	ParameterSliderTableListBoxModel& getModel() {
		return model;
	}

private:
	ParameterSliderTableListBoxModel model;
};

#endif  // PARAMETERSLIDERTABLELISTBOX_H_INCLUDED