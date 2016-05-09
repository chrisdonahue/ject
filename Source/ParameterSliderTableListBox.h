/*
  ==============================================================================

	ParameterSliderTableListBox.h
	Created: 6 May 2016 1:21:53pm
	Author:  Chris

  ==============================================================================
*/

#ifndef PARAMETERSLIDERTABLELISTBOX_H_INCLUDED
#define PARAMETERSLIDERTABLELISTBOX_H_INCLUDED

#include <unordered_map>
#include <set>

#include "../JuceLibraryCode/JuceHeader.h"

class ParameterSliderTableListBox : public TableListBox, public ChangeListener, public ChangeBroadcaster {
private:
	enum Column {
		id = 1,
		slider
	};

	class ParameterSliderTableListBoxModel : public TableListBoxModel, public ChangeBroadcaster, public SliderListener {
	public:
		ParameterSliderTableListBoxModel() {};

		int getNumRows() override {
			return fileIds.size();
		};

		void paintRowBackground(Graphics& g, int rowNumber, int width, int height, bool rowIsSelected) override {
			if (rowIsSelected)
				g.fillAll(Colours::lightblue);
			else if (rowNumber % 2)
				g.fillAll(Colour(0xffeeeeee));
		};

		void paintCell(Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override {};

		Component* refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component *existingComponentToUpdate) override {
			if (columnId == Column::id) {
				Label* label = static_cast<Label*>(existingComponentToUpdate);

				if (label == nullptr) {
					label = new Label();
					label->setText(String(rowToFileId[rowNumber]), dontSendNotification);
				}

				return label;
			}
			else if (columnId == Column::slider) {
				Slider* slider = static_cast<Slider*>(existingComponentToUpdate);

				if (slider == nullptr) {
					slider = new Slider();
					slider->setRange(0.0, 1.0, 0.01);
					slider->setSliderStyle(Slider::LinearHorizontal);
					slider->setTextBoxStyle(Slider::TextBoxLeft, false, 40, 20);
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

		int getFileIdForRow(int row) const {
			return rowToFileId.at(row);
		};

		void updateFileIds(const std::set<int>& fileIdsNew) {
			fileIds = fileIdsNew;
			fileIdToRow.clear();
			rowToFileId.clear();
			int row = 0;
			for (auto i : fileIds) {
				fileIdToRow[i] = row;
				rowToFileId[row] = i;
				++row;
			}
		};

	private:
		std::set<int> fileIds;
		std::unordered_map<int, int> fileIdToRow;
		std::unordered_map<int, int> rowToFileId;
	};

public:
	ParameterSliderTableListBox(String paramName) {
		setModel(&model);
		setColour(ListBox::outlineColourId, Colours::grey);
		setClickingTogglesRowSelection(true);
		setMultipleSelectionEnabled(false);
		getHeader().addColumn("ID", Column::id, 32, 32, -1, TableHeaderComponent::visible | TableHeaderComponent::resizable);
		getHeader().addColumn(paramName, Column::slider, 224, 32, -1, TableHeaderComponent::visible | TableHeaderComponent::resizable);
		model.addChangeListener(this);
	};

	void changeListenerCallback(ChangeBroadcaster* source) override {
		if (source == &model) {
			sendChangeMessage();
		}
	};

	void getFileIdToWeight(unordered_map<int, double>& result) {
		int numRows = model.getNumRows();
		for (int row = 0; row < numRows; ++row) {
			int fileId = model.getFileIdForRow(row);
			Slider* slider = static_cast<Slider*>(getCellComponent(Column::slider, row));
			jassert(slider != nullptr);
			result[row] = slider->getValue();
		}
	};

	ParameterSliderTableListBoxModel& getModel() {
		return model;
	};

private:
	ParameterSliderTableListBoxModel model;
};

#endif  // PARAMETERSLIDERTABLELISTBOX_H_INCLUDED