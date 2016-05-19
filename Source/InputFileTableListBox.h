/*
==============================================================================

InputFileTableListBox.h
Created: 6 May 2016 1:21:53pm
Author:  Chris

==============================================================================
*/

#ifndef INPUTFILETABLELISTBOX_H_INCLUDED
#define INPUTFILETABLELISTBOX_H_INCLUDED

#include <algorithm>
#include <vector>
#include <unordered_map>

#include "../JuceLibraryCode/JuceHeader.h"

#include "Sound.h"

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
		path,
		name,
		include,
		pValue,
		rValue
	};

	class InputFileTableListBoxModel : public TableListBoxModel, public ChangeBroadcaster, public ButtonListener, public SliderListener {
	public:
		InputFileTableListBoxModel(InputFileTableListBox& table) : table(table) {};

		int getNumRows() override {
			return table.idToSound.size();
		};

		void paintRowBackground(Graphics& g, int rowNumber, int width, int height, bool rowIsSelected) override {
			if (rowIsSelected)
				g.fillAll(Colours::lightblue);
			else if (rowNumber % 2)
				g.fillAll(Colour(0xffeeeeee));
		};

		void paintCell(Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override {};

		Component* refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component *existingComponentToUpdate) override {
			jassert(rowNumber < table.rowToId.size());

			int id = table.rowToId[rowNumber];
			const Sound* sound = table.idToSound[id];

			if (columnId == Column::id) {
				Label* label = static_cast<Label*>(existingComponentToUpdate);

				if (label == nullptr) {
					label = new Label();
					label->setText(String(id), dontSendNotification);
				}

				return label;
			}
			else if (columnId == Column::path) {
				Label* label = static_cast<Label*>(existingComponentToUpdate);

				if (label == nullptr) {
					label = new Label();
					label->setText(sound->getFilePath(), dontSendNotification);
				}

				return label;
			}
			else if (columnId == Column::name) {
				Label* label = static_cast<Label*>(existingComponentToUpdate);

				if (label == nullptr) {
					label = new Label();
					label->setText(sound->getName(), dontSendNotification);
				}

				return label;
			}
			else if (columnId == Column::include) {
				ToggleButton* toggleButton = static_cast<ToggleButton*>(existingComponentToUpdate);

				if (toggleButton == nullptr) {
					toggleButton = new ToggleButton();
					toggleButton->addListener(this);
				}

				toggleButton->setToggleState(sound->isIncluded(), dontSendNotification);

				return toggleButton;
			}
			else if (columnId == Column::pValue) {
				Slider* slider = static_cast<Slider*>(existingComponentToUpdate);

				if (slider == nullptr) {
					slider = new Slider();
					slider->setRange(0.0, 1.0, 0.01);
					slider->setSliderStyle(Slider::LinearHorizontal);
					slider->setTextBoxStyle(Slider::TextBoxLeft, false, 40, 20);
					slider->addListener(this);
				}

				slider->setValue(sound->getPValue(), dontSendNotification);

				return slider;
			}
			else if (columnId == Column::rValue) {
				Slider* slider = static_cast<Slider*>(existingComponentToUpdate);

				if (slider == nullptr) {
					slider = new Slider();
					slider->setRange(0.0, 1.0, 0.01);
					slider->setSliderStyle(Slider::LinearHorizontal);
					slider->setTextBoxStyle(Slider::TextBoxLeft, false, 40, 20);
					slider->addListener(this);
				}

				slider->setValue(sound->getRValue(), dontSendNotification);

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
	enum PrBehavior {
		independent = 1,
		linked,
		inverse
	};

	friend class InputFileTableListBoxModel;

	InputFileTableListBox(PrBehavior prBehavior) : model(*this), prBehavior(prBehavior) {
		setModel(&model);
		setColour(ListBox::outlineColourId, Colours::grey);
		setClickingTogglesRowSelection(true);
		setMultipleSelectionEnabled(true);
		int flags = TableHeaderComponent::defaultFlags & ~TableHeaderComponent::sortable;
		getHeader().addColumn("ID", Column::id, 32, 32, -1, flags);
		getHeader().addColumn("Name", Column::name, 128, 32, -1, flags);
		getHeader().addColumn("Use", Column::include, 32, 32, -1, flags);
		getHeader().addColumn("P", Column::pValue, 128, 32, -1, flags);
		getHeader().addColumn("R", Column::rValue, 128, 32, -1, flags);
		model.addChangeListener(this);
	};

	void changeListenerCallback(ChangeBroadcaster* source) override {
		if (source == &model) {
			sendChangeMessage();
		}
	};

	void setIdToSound(const std::unordered_map<int, Sound*>& idToSoundNew) {
		idToSound = idToSoundNew;
		std::vector<int> ids;
		for (auto i : idToSound) {
			ids.push_back(i.first);
		}
		std::sort(ids.begin(), ids.end());

		rowToId.clear();
		for (auto it = ids.begin(); it != ids.end(); ++it) {
			int row = std::distance(ids.begin(), it);
			int id = *it;
			rowToId.emplace(row, id);
		}
	};

	void setPrBehavior(PrBehavior prBehaviorNew) {
		prBehavior = prBehaviorNew;
	};

	PrBehavior getPrBehavior() const {
		return prBehavior;
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
	std::unordered_map<int, Sound*> idToSound;
	std::unordered_map<int, int> rowToId;
	PrBehavior prBehavior;
};

#endif  // INPUTFILETABLELISTBOX_H_INCLUDED