/*
* This file is part of GDSCanvas.
*
* boundaryitem.cpp -- The source file which defines the boundary item for GDS canvas.
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
#include "utilities.h"
#include "boundaryitem.h"

namespace QGDSII
{
	BoundaryItem::BoundaryItem(GDS::Boundary* data, QGraphicsItem* parent)
		: QGraphicsItem(parent)
	{
		assert(data != nullptr);

		m_Data = data;
	}

	BoundaryItem::~BoundaryItem()
	{}

	QRectF BoundaryItem::boundingRect() const
	{
		std::vector<int> x, y;
		m_Data->xy(x, y);
		assert(x.size() >= 4 && y.size() >= 4);

		QPolygonF polygon;
		for (size_t i = 0; i < x.size() && i < y.size(); i++)
		{
			polygon << QPoint(x[i], y[i]);
		}

		return polygon.boundingRect();
	}

	QPainterPath BoundaryItem::shape() const
	{
		std::vector<int> x, y;
		m_Data->xy(x, y);
		assert(x.size() >= 4 && y.size() >= 4);

		QPolygonF polygon;
		for (size_t i = 0; i < x.size() && i < y.size(); i++)
		{
			polygon << QPoint(x[i], y[i]);
		}

		QPainterPath path;
		path.addPolygon(polygon);

		return path;
	}

	void BoundaryItem::paint(QPainter* painter,
		const QStyleOptionGraphicsItem* option,
		QWidget* widget)
	{
		
		initPen(painter, option, m_Data->layer(), m_Data->dataType());
		initBrush(painter, m_Data->layer(), m_Data->dataType());
		
		std::vector<int> x, y;
		m_Data->xy(x, y);
		assert(x.size() >= 4 && y.size() >= 4);

		QPolygonF polygon;
		for (size_t i = 0; i < x.size() && i < y.size(); i++)
		{
			polygon << QPoint(x[i], y[i]);
		}
		painter->drawPolygon(polygon);
	}
}
