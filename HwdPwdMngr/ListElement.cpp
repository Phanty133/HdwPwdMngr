#include "ListElement.h"
#include <iostream>

constexpr int COL_PADDING = 2;

ListElement::ListElement(int y, int x, int h, int w, std::vector<ListColumn> cols, std::vector<DataEntry> data)
{
	m_cols = cols;
	m_data = data;
	m_x = x;
	m_y = y;
	m_w = w;
	m_h = h;
	m_counterDigitCount = std::floor(std::log10(c_data.size()) + 1); // Counter format: AA...AA/BB...BB, e.g. 001/100
	m_wTable = w - (m_counterDigitCount * 2 + 3);
	m_win = newwin(c_h, c_w, c_x, c_y);

	for (auto& col : m_cols) {
		m_keyedCols.insert(std::pair<std::string, ListColumn>(col.key, col));
	}

	draw();
}

void ListElement::drawHeaders()
{
	// Calculate default header width based on headers with set width

	int reservedWidth = 0;
	int defaultCols = 0; // Number of default cols

	for (auto& col : c_cols) {
		if (col.width == NULL) {
			defaultCols++;
		} 

		reservedWidth += col.width + COL_PADDING;
	}

	const int defaultWidth = defaultCols != 0 ? (m_wTable - reservedWidth) / defaultCols : 0;

	// Draw each column

	int maxTextHeight = 0;
	int colX0 = 1;

	for (auto& col : c_cols) {
		int colWidth = col.width == NULL ? defaultWidth : col.width;

		int textHeight = wprintInLines(
			m_win,
			col.label,
			colWidth,
			1,
			colX0,
			CENTER,
			false
		);

		ListColumnMetadata colData(colWidth, colX0);
		m_colMetadata.insert(std::pair<std::string, ListColumnMetadata>(col.key, colData));

		colX0 += colWidth + COL_PADDING;

		if (textHeight > maxTextHeight) maxTextHeight = textHeight;
	}

	// Draw header borders

	for (auto& col : c_cols) {
		ListColumnMetadata colData = m_colMetadata.find(col.key)->second;
		std::string msg(colData.width, '-');

		mvwaddstr(m_win, maxTextHeight + 1, colData.x, msg.c_str());
	}

	m_entryStartY = maxTextHeight + 2;
}

void ListElement::drawEntry(DataEntry entry, int y)
{
	for (const auto& col : entry) {
		std::string key = col.first;
		ListColumn writeColumn = m_keyedCols.find(key)->second;
		ListColumnMetadata colData = m_colMetadata.find(key)->second;
		std::string fullLabel = col.second + std::string(colData.width - col.second.length(), ' '); // Set the rest of the field empty to overwrite any preexisting text

		mvwprintw(m_win, y, colData.x + 1, fullLabel.c_str());
	}
}

void ListElement::drawEntries()
{
	int entryY = m_entryStartY;
	int entryIndex0 = std::max(m_cur - m_entryPageSize, 0);

	for (int i = entryIndex0; i <= entryIndex0 + m_entryPageSize; i++) {
		m_entryY.insert(std::pair<int, int>(i, entryY));
		drawEntry(c_data[i], entryY++);
	}
}

void ListElement::drawEntryCounter()
{
	std::string counterText = std::string(m_counterDigitCount - 1, '0') + "1/" + std::to_string(c_data.size());
	mvwaddstr(m_win, 1, m_wTable, counterText.c_str());
}

void ListElement::highlightEntry(int index)
{
	mvwchgat(m_win, m_entryY[index], 1, m_wTable - 2, A_REVERSE, 0, nullptr);
}

void ListElement::unhighlightEntry(int index)
{
	mvwchgat(m_win, m_entryY[index], 1, m_wTable - 2, !A_REVERSE, 0, nullptr);
}

void ListElement::updateEntryCounter()
{
	int posDigitCount = std::floor(std::log10(m_cur + 1) + 1);
	std::string counterText = std::string(m_counterDigitCount - posDigitCount, '0') + std::to_string(m_cur + 1);
	mvwaddstr(m_win, 1, m_wTable, counterText.c_str());
}

void ListElement::selectEntry(int index)
{
	unhighlightEntry(m_cur);
	int prevIndex = m_cur;
	m_cur = std::min(std::max(index, 0), (int) c_data.size() - 1); // Clamp the index

	if (m_cur > m_entryPageSize || prevIndex > m_cur) { // If the current position is off the first page
		drawEntries();
	}

	highlightEntry(m_cur);
	updateEntryCounter();
	wrefresh(m_win);
}

void ListElement::moveUp()
{
	selectEntry(m_cur - 1);
}

void ListElement::moveDown()
{
	selectEntry(m_cur + 1);
}

void ListElement::draw()
{
	wborder(m_win, '|', '|', '-', '-', '+', '+', '+', '+');
	drawEntryCounter();
	drawHeaders();

	m_entryPageSize = m_h - 2 - m_entryStartY;

	drawEntries();
	selectEntry(0);

	wrefresh(m_win);
}
