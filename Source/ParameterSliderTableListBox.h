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
			return 0;
		};

		void paintRowBackground(Graphics& g, int rowNumber, int width, int height, bool rowIsSelected) override {

		};

		void paintCell(Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override {

		};

		Component* refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component *existingComponentToUpdate) override {
			if (columnId == Column::name) {
				Label* label = static_cast<Label*>(existingComponentToUpdate);

				if (label == nullptr) {
					label = new Label();
					label->setText("lol", dontSendNotification);
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

		};

		void selectedRowsChanged(int lastRowSelected) override {

		};

		void sliderValueChanged(Slider* slider) override {
			sendChangeMessage();
		};
	private:
	};

public:
	ParameterSliderTableListBox(String paramName) : model(new ParameterSliderTableListBoxModel()) {
		setModel(model);
		setColour(ListBox::outlineColourId, Colours::grey);
		setClickingTogglesRowSelection(true);
		setMultipleSelectionEnabled(true);
		getHeader().addColumn("Name", Column::name, 32, 32, -1, TableHeaderComponent::visible | TableHeaderComponent::resizable);
		getHeader().addColumn(paramName, Column::slider, 32, 32, -1, TableHeaderComponent::visible | TableHeaderComponent::resizable);
		model->addChangeListener(this);
	};

	void changeListenerCallback(ChangeBroadcaster* source) override {
		if (source == model) {
			sendChangeMessage();
		}
	};

private:
	ScopedPointer<ParameterSliderTableListBoxModel> model;
};

#endif  // PARAMETERSLIDERTABLELISTBOX_H_INCLUDED