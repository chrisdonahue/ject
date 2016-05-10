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

#include "XmlHelper.h"

class InputFileTableListBox : public TableListBox, public ChangeListener, public ChangeBroadcaster {
private:
	class SelectableLabel : public Label
	{
	public:
		SelectableLabel(InputFileTableListBox& table, int row) :
			table(table), row(row) {
			setColour(textColourId, Colours::black);
		};

		void mouseDown(const MouseEvent& event) override {
			table.selectRowsBasedOnModifierKeys(row, event.mods, false);
			Label::mouseDown(event);
		};

		void setRow(int rowNew) {
			row = rowNew;
		};

	private:
		InputFileTableListBox& table;
		int row;
	};

	class InputFileTableListBoxModel : public TableListBoxModel, public ChangeBroadcaster, public ButtonListener, public SliderListener {
	public:
		InputFileTableListBoxModel(InputFileTableListBox& table) : table(table) {};

		int getNumRows() override {
			return table.fileListData->getNumChildElements();
		};

		void paintRowBackground(Graphics& g, int rowNumber, int width, int height, bool rowIsSelected) override {
			if (rowIsSelected)
				g.fillAll(Colours::lightblue);
			else if (rowNumber % 2)
				g.fillAll(Colour(0xffeeeeee));
		};

		void paintCell(Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override {};

		Component* refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component *existingComponentToUpdate) override {
			XmlElement* fileListData = table.fileListData;

			enum Column {
				id = 1,
				path,
				name,
				include,
				pValue,
				rValue
			};

			if (columnId == XmlHelper::Column::id ||
				columnId == XmlHelper::Column::path ||
				columnId == XmlHelper::Column::name) {
				Label* label = static_cast<Label*>(existingComponentToUpdate);

				if (label == nullptr) {
					label = new Label();
					label->setText(XmlHelper::getStringAttributeForRowColumnId(fileListData, columnId, rowNumber), dontSendNotification);
				}

				return label;
			}
			else if (columnId == XmlHelper::Column::include) {
				ToggleButton* toggleButton = static_cast<ToggleButton*>(existingComponentToUpdate);

				if (toggleButton == nullptr) {
					toggleButton = new ToggleButton();
					toggleButton->addListener(this);
				}

				toggleButton->setEnabled(static_cast<bool>(XmlHelper::getIntAttributeForRowColumnId(fileListData, columnId, rowNumber)));

				return toggleButton;
			}
			else if (columnId == XmlHelper::Column::pValue || XmlHelper::Column::rValue) {
				Slider* slider = static_cast<Slider*>(existingComponentToUpdate);

				if (slider == nullptr) {
					slider = new Slider();
					slider->setRange(0.0, 1.0, 0.01);
					slider->setSliderStyle(Slider::LinearHorizontal);
					slider->setTextBoxStyle(Slider::TextBoxLeft, false, 40, 20);
					slider->addListener(this);
				}

				slider->setValue(XmlHelper::getDoubleAttributeForRowColumnId(fileListData, columnId, rowNumber));

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

		void selectedRowsChanged(int lastRowSelected) override {
			sendChangeMessage();
		};

		void buttonClicked(Button* button) override {
			sendChangeMessage();
		};

		void sliderValueChanged(Slider* slider) override {
			sendChangeMessage();
		};

	private:
		InputFileTableListBox& table;
	};

public:
	friend class InputFileTableListBoxModel;

	InputFileTableListBox(XmlElement* fileListColumns, XmlElement* fileListData) : model(*this), fileListData(fileListData) {
		setModel(&model);
		setColour(ListBox::outlineColourId, Colours::grey);
		setClickingTogglesRowSelection(true);
		setMultipleSelectionEnabled(true);
		forEachXmlChildElement(*fileListColumns, columnXml) {
			getHeader().addColumn(columnXml->getStringAttribute("name"),
				columnXml->getIntAttribute("columnId"),
				columnXml->getIntAttribute("width"),
				50, 400,
				TableHeaderComponent::defaultFlags);
		}
		model.addChangeListener(this);
	};

	void changeListenerCallback(ChangeBroadcaster* source) override {
		if (source == &model) {
			sendChangeMessage();
		}
	};

	void setFileListData(XmlElement* fileListDataNew) {
		fileListData = fileListDataNew;
	};

	/*
	void getSelectedFileIds(std::unordered_set<int>& fileIds) {
		SparseSet<int> selectedRows = getSelectedRows();
		for (int i = 0; i < selectedRows.size(); ++i) {
			int row = selectedRows[i];
			fileIds.insert(model.getFileIdForRow(row));
		}
	};

	InputFileTableListBoxModel& getModel() {
		return model;
	};
	*/

private:
	InputFileTableListBoxModel model;
	XmlElement* fileListData;
};

#endif  // INPUTFILETABLELISTBOX_H_INCLUDED