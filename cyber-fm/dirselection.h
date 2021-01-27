/*
 * Copyright (C) 2020 CyberOS Team.
 *
 * Author:     rekols <revenmartin@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef DIRSELECTION_H
#define DIRSELECTION_H

#include <QObject>
#include "fileitem.h"

class FolderListModel;
class DirSelection : public QObject
{
    Q_OBJECT

public:
    DirSelection(FolderListModel *model, FileItems *fileItems);
    DirSelection(QObject *parent = nullptr);

public slots:
    void setIndex(int index, bool selected);
    void toggleIndex(int index);
    void selectAll();
    void clear();

    QList<int> selectedIndexes() const;

signals:
    void selectionChanged(int);

private:
    FolderListModel *m_model;
    FileItems *m_fileItems;
    int m_selectedCounter;

};

#endif // DIRSELECTION_H
