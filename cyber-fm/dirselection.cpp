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

#include "dirselection.h"
#include "folderlistmodel.h"

DirSelection::DirSelection(FolderListModel *model, FileItems *fileItems)
    : m_model(model)
    , m_fileItems(fileItems)
{

}

DirSelection::DirSelection(QObject *parent)
    : QObject(parent)
{

}

void DirSelection::setIndex(int index, bool selected)
{
    FileItem *item = m_fileItems->at(index);

    bool change = false;
    if ((change = item->setSelection(selected))) {
        m_model->notifyItemChanged(index);
    }
}

void DirSelection::toggleIndex(int index)
{
    setIndex(index, !m_fileItems->at(index)->isSelected());
}

void DirSelection::selectAll()
{
    for (int i = 0; i < m_model->rowCount(); ++i) {
        if (m_fileItems->at(i)->setSelection(true)) {
            m_model->notifyItemChanged(i);
        }
    }
}

void DirSelection::clear()
{
    for (int i = 0; i < m_model->rowCount(); ++i) {
        if (m_fileItems->at(i)->setSelection(false)) {
            m_model->notifyItemChanged(i);
        }
    }
}

QList<int> DirSelection::selectedIndexes() const
{
    QList<int> result;

    for (int i = 0; i < m_fileItems->size(); ++i) {
        if (m_fileItems->at(i)->isSelected()) {
            result.append(i);
        }
    }

    return result;
}
