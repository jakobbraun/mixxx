/***************************************************************************
                           stardelegate.cpp
                              -------------------
    copyright            : (C) 2010 Tobias Rafreider
	copyright            : (C) 2009 Nokia Corporation

***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include <QtDebug>
#include <QtGui>

#include "stardelegate.h"
#include "stareditor.h"
#include "starrating.h"

/*
 * The function is invoked once for each item, represented by a QModelIndex object from the model.
 * If the data stored in the item is a StarRating, we paint it use a star editor for displaying;
 * otherwise, we let QItemDelegate paint it for us.
 * This ensures that the StarDelegate can handle the most common data types.
 */
void StarDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    // Populate the correct colors based on the styling
    //QStyleOptionViewItem newOption = option;
    //initStyleOption(&newOption, index);

    // Set the palette appropriately based on whether the row is selected or not
    if (option.state & QStyle::State_Selected) {
        painter->fillRect(option.rect, option.palette.highlight());
        painter->setBrush(option.palette.highlightedText());
    } else {
        painter->fillRect(option.rect, option.palette.base());
        painter->setBrush(option.palette.text());
    }

    if (qVariantCanConvert<StarRating>(index.data())) {
        StarRating starRating = qVariantValue<StarRating>(index.data());
        starRating.paint(painter, option.rect, option.palette, StarRating::ReadOnly);
    } else {
        //QStyledItemDelegate::paint(painter, newOption, index);
        QItemDelegate::paint(painter, option, index);
    }
}

QSize StarDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (qVariantCanConvert<StarRating>(index.data())) {
        StarRating starRating = qVariantValue<StarRating>(index.data());
        return starRating.sizeHint();
    } else {
        return QItemDelegate::sizeHint(option, index);
    }
}
/*
 * If the item is a StarRating, we create a StarEditor and connect
 * its editingFinished() signal to our commitAndCloseEditor() slot,
 * so we can update the model when the editor closes.
 */
QWidget *StarDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,const QModelIndex &index) const
{
    // Populate the correct colors based on the styling
    //QStyleOptionViewItem newOption = option;
    //initStyleOption(&newOption, index);

    if (qVariantCanConvert<StarRating>(index.data())) {
        StarEditor *editor = new StarEditor(parent, option);
        connect(editor, SIGNAL(editingFinished()),
        this, SLOT(commitAndCloseEditor()));
        return editor;
    } else {
        return QItemDelegate::createEditor(parent, option, index);
    }
}

void StarDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if (qVariantCanConvert<StarRating>(index.data())) {
        StarRating starRating = qVariantValue<StarRating>(index.data());
        StarEditor *starEditor = qobject_cast<StarEditor *>(editor);
        starEditor->setStarRating(starRating);
    } else {
        QItemDelegate::setEditorData(editor, index);
    }
}

void StarDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if (qVariantCanConvert<StarRating>(index.data())) {
        StarEditor *starEditor = qobject_cast<StarEditor *>(editor);
        model->setData(index, qVariantFromValue(starEditor->starRating()));
    } else {
        QItemDelegate::setModelData(editor, model, index);
    }
}
/*
 * When the user is done editing, we emit commitData() and closeEditor() (both declared in QAbstractItemDelegate),
 * to tell the model that there is edited data and to inform the view that the editor is no longer needed.
 */
void StarDelegate::commitAndCloseEditor()
{
    StarEditor *editor = qobject_cast<StarEditor *>(sender());
    emit commitData(editor);
    emit closeEditor(editor);
}
