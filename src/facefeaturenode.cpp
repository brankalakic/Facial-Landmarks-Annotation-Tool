/*
 * Copyright (C) 2016 Luiz Carlos Vieira (http://www.luiz.vieira.nom.br)
 *
 * This file is part of FLAT.
 *
 * FLAT is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * FLAT is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "facefeaturenode.h"
#include "facewidget.h"
#include "facefeatureedge.h"
#include "application.h"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>

// Radius of the drawn node, in pixels
const int ft::FaceFeatureNode::RADIUS = 4;

// +-----------------------------------------------------------
ft::FaceFeatureNode::FaceFeatureNode(int iID, FaceWidget *pFaceWidget)
{
	m_pFaceWidget = pFaceWidget;

    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
	setFlag(ItemIsSelectable);
    setCacheMode(DeviceCoordinateCache);

	setSelected(false);
	setAcceptHoverEvents(true);

	m_iID = iID;
}

double ft::FaceFeatureNode::getFeatureRadius() const
{
	double scale;
	scale = m_pFaceWidget->getScaleFactor();

	return RADIUS/scale;
}

// +-----------------------------------------------------------
void ft::FaceFeatureNode::addEdge(FaceFeatureEdge *pEdge)
{
	m_lEdges.append(pEdge);
    pEdge->adjust();
}

// +-----------------------------------------------------------
void ft::FaceFeatureNode::removeEdge(FaceFeatureEdge *pEdge)
{
	m_lEdges.removeOne(pEdge);
}

// +-----------------------------------------------------------
QList<ft::FaceFeatureEdge *> ft::FaceFeatureNode::edges() const
{
    return m_lEdges;
}

// +-----------------------------------------------------------
ft::FaceFeatureEdge *ft::FaceFeatureNode::getEdgeTo(const FaceFeatureNode *pNode) const
{
	foreach(FaceFeatureEdge *pEdge, m_lEdges)
	{
		if((pEdge->sourceNode() == this && pEdge->targetNode() == pNode) ||
		   (pEdge->sourceNode() == pNode && pEdge->targetNode() == this))
		{
			return pEdge;
		}
	}
	return NULL;
}

// +-----------------------------------------------------------
QRectF ft::FaceFeatureNode::boundingRect() const
{
	double r = getFeatureRadius();
	if(m_pFaceWidget->displayFeatureIDs())
	{
		QString sID = QString::number(m_iID);
		int iHeight = m_pFaceWidget->fontMetrics().height();
		int iWidth = m_pFaceWidget->fontMetrics().width(sID);
		return QRectF(-(iWidth + r), -(iHeight + r), 2 * r + iWidth, 2 * r + iHeight);
	}
	else
		return QRectF(-r, -r, 2 * r, 2 * r);
}

// +-----------------------------------------------------------
void ft::FaceFeatureNode::paint(QPainter *pPainter, const QStyleOptionGraphicsItem *pOption, QWidget *pWidget)
{
	Q_UNUSED(pOption);
	Q_UNUSED(pWidget);

	QBrush oBrush;
	oBrush.setStyle(Qt::SolidPattern);
	if(isSelected())
	{
	    pPainter->setPen(QPen(Qt::red, 0));
		oBrush.setColor(QColor(Qt::red));
	}
	else
	{
	    pPainter->setPen(QPen(Qt::yellow, 0));
		oBrush.setColor(QColor(Qt::yellow));
	}

	QRectF oBounds;
	if(m_pFaceWidget->displayFeatureIDs())
	{
		QString sID = QString::number(m_iID);
		double r = getFeatureRadius();
		int iHeight = m_pFaceWidget->fontMetrics().height();
		int iWidth = m_pFaceWidget->fontMetrics().width(sID);
		oBounds = QRectF(-(iWidth + r), -(iHeight + r), iWidth, iHeight);
		pPainter->drawText(oBounds, sID);

		oBounds = QRectF(-r, -r, 2 * r, 2 * r);
	}
	else
		oBounds = boundingRect();

    pPainter->setBrush(oBrush);
	pPainter->drawEllipse(oBounds);
}

// +-----------------------------------------------------------
QVariant ft::FaceFeatureNode::itemChange(GraphicsItemChange eChange, const QVariant &oValue)
{
	QString sText;
    switch(eChange)
	{
		case ItemPositionHasChanged:
			foreach(FaceFeatureEdge *pEdge, m_lEdges)
				pEdge->adjust();

			sText = QApplication::translate("FaceFeatureNode", "Node: %1 Position: (%2, %3)").arg(m_iID).arg(QString::number(pos().x(), 'f', 2)).arg(QString::number(pos().y(), 'f', 2));
			FtApplication::instance()->showStatusMessage(sText, 0);

			if(!data(0).toBool()) // This flag is used in ChildWindow::refreshFeaturesInWidget
				m_pFaceWidget->faceFeatureMoved(this);
			break;
	
		default:
			break;
    };

    return QGraphicsItem::itemChange(eChange, oValue);
}

// +-----------------------------------------------------------
void ft::FaceFeatureNode::hoverEnterEvent(QGraphicsSceneHoverEvent *pEvent)
{
	QString sText = QApplication::translate("FaceFeatureNode", "Node: %1 Position: (%2, %3)").arg(m_iID).arg(QString::number(pos().x(), 'f', 2)).arg(QString::number(pos().y(), 'f', 2));
	FtApplication::instance()->showStatusMessage(sText, 0);
	QGraphicsItem::hoverEnterEvent(pEvent);
}

// +-----------------------------------------------------------
void ft::FaceFeatureNode::hoverLeaveEvent(QGraphicsSceneHoverEvent *pEvent)
{
	FtApplication::instance()->showStatusMessage("");
	QGraphicsItem::hoverLeaveEvent(pEvent);
}

// +-----------------------------------------------------------
int ft::FaceFeatureNode::getID() const
{
	return m_iID;
}

// +-----------------------------------------------------------
void ft::FaceFeatureNode::setID(int iID)
{
	m_iID = iID;
}