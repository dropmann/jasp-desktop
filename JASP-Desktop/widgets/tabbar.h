//
// Copyright (C) 2013-2015 University of Amsterdam
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public
// License along with this program.  If not, see
// <http://www.gnu.org/licenses/>.
//

#ifndef TABBAR_H
#define TABBAR_H

#include <QWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QList>
#include <QPushButton>

class TabBar : public QWidget
{
	Q_OBJECT
public:
	explicit TabBar(QWidget *parent = 0);

	void addTab(QString tabName);
	void removeTab(QString tabName);
	void removeTab(int index);

	void addOptionsTab();
	void addHelpTab();

	int count() const;

signals:
	void currentChanged(int index);
	void helpToggled(bool on);

public slots:
	void setCurrentIndex(int index);

private slots:
	void tabSelectedHandler();
	void helpToggledHandler(bool on);

private:

	QWidget *_background;
	QList<QPushButton *> _tabButtons;
	QGridLayout *_backgroundLayout;
	QHBoxLayout *_layout;

	QPushButton *_optionsTab;
	QPushButton *_helpTab;

};

#endif // TABBAR_H
