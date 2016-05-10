/*
==============================================================================

InputFileTableListBox.h
Created: 6 May 2016 1:21:53pm
Author:  Chris

==============================================================================
*/

#ifndef INPUTFILETABLELISTBOX_H_INCLUDED
#define INPUTFILETABLELISTBOX_H_INCLUDED

#include <map>
#include <unordered_set>

#include "../JuceLibraryCode/JuceHeader.h"

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

	enum Column {
		id = 1,
		name
	};

	class InputFileTableListBoxModel : public TableListBoxModel, public ChangeBroadcaster {
	public:
		InputFileTableListBoxModel(InputFileTableListBox& table, XmlElement* files) : table(table), files(files) {};

		int getNumRows() override {
			return files->getNumChildElements();
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
					label = new SelectableLabel(table, rowNumber);
					label->setText(file->, dontSendNotification);
				}

				return label;
			}
			else if (columnId == Column::name) {
				Label* label = static_cast<Label*>(existingComponentToUpdate);

				if (label == nullptr) {
					label = new SelectableLabel(table, rowNumber);
					label->setText(fileNames[rowNumber], dontSendNotification);
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

		void selectedRowsChanged(int lastRowSelected) override {
			sendChangeMessage();
		};

		void sliderValueChanged(Slider* slider) override {
			sendChangeMessage();
		};

		int getFileIdForRow(int row) const {
			return rowToFileId.at(row);
		};

		void updateFiles(const std::map<int, String> fileIdsToNamesNew) {
			fileIdsToNames = fileIdsToNamesNew;
			fileIdToRow.clear();
			rowToFileId.clear();
			int row = 0;
			for (auto i : fileIdsToNames) {
				int id = i.first;
				fileIdToRow[id] = row;
				rowToFileId[row] = id;
				++row;
			}
		};

	private:
		InputFileTableListBox& table;
		XmlElement* files;
	};

public:
	InputFileTableListBox(XmlElement* files) : files(files), model(*this, files) {
		setModel(&model);
		setColour(ListBox::outlineColourId, Colours::grey);
		setClickingTogglesRowSelection(true);
		setMultipleSelectionEnabled(true);
		getHeader().addColumn("ID", Column::id, 32, 32, -1, TableHeaderComponent::defaultFlags);
		getHeader().addColumn("Name", Column::name, 160, 32, -1, TableHeaderComponent::defaultFlags);
		model.addChangeListener(this);
	};

	void changeListenerCallback(ChangeBroadcaster* source) override {
		if (source == &model) {
			sendChangeMessage();
		}
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
	XmlElement* files;
	InputFileTableListBoxModel model;
};

#endif  // INPUTFILETABLELISTBOX_H_INCLUDED