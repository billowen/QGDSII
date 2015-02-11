/*
* This file is part of GDSII.
*
* pathitem.cpp -- The source file which defines the path item for GDS canvas.
*
* Copyright (c) 2015 Kangpeng Shao <billowen035@gmail.com>
*
* GDSII is free software: you can redistribute it and/or modify it
* under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at you option) any later version.
*
* GDSII is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABLILTY or
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
* for more details.
*
* You should have received a copy of the GNU General Public License
* along with GDSII. If not, see <http://www.gnu.org/licenses/>.
**/

#include <assert.h>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include "GDS/path.h"
#include "utilities.h"
#include "pathitem.h"

namespace QGDSII
{
	PathItem::PathItem(GDS::Path* data, QGraphicsItem* parent)
		: QGraphicsItem(parent)
	{
		assert(data != NULL);
		m_Data = data;
	}
	
	PathItem::~PathItem()
	{}

    QRectF PathItem::boundingRect() const
    {
		QPainterPath path = shape();
		return path.boundingRect();
    }

    QPainterPath PathItem::shape() const
    {
        std::vector<int> x, y;
        m_Data->xy(x, y);
        assert(x.size() >= 2 && x.size() == y.size());
        if (x.size() < 2 || y.size() < 2)
            return QPainterPath();

        int width = m_Data->width();
        width = width < 0 ? -width : width;
        QPainterPath path;
        path.moveTo(x[0], y[0]);
        for (size_t i = 1; i < x.size() && i < y.size(); i++)
        {
            path.lineTo(x[i], y[i]);
        }
        QPainterPathStroker stroker;
        stroker.setJoinStyle(Qt::MiterJoin);
        stroker.setWidth(width);

		// To-do: the path end type

        return stroker.createStroke(path);
    }

    void PathItem::paint(QPainter* painter,
            const QStyleOptionGraphicsItem* option, 
            QWidget* widget)
    {
		initPen(painter, option, m_Data->layer(), m_Data->dataType());
		initBrush(painter, m_Data->layer(), m_Data->dataType());

        painter->drawPath(shape());
    }
}
