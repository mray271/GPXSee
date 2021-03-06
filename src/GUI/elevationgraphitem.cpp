#include <QLocale>
#include "tooltip.h"
#include "elevationgraphitem.h"


ElevationGraphItem::ElevationGraphItem(const Graph &graph, GraphType type,
  QGraphicsItem *parent) : GraphItem(graph, type, parent)
{
	_ascent = _descent = 0;

	for (int j = 1; j < graph.size(); j++) {
		qreal cur = graph.at(j).y();
		qreal prev = graph.at(j-1).y();

		if (cur > prev)
			_ascent += cur - prev;
		if (cur < prev)
			_descent += prev - cur;
	}

	setToolTip(toolTip(Metric));
}

QString ElevationGraphItem::toolTip(Units units) const
{
	ToolTip tt;
	qreal scale = (units == Metric) ? 1.0 : M2FT;
	QString su = (units == Metric) ? tr("m") : tr("ft");
	QLocale l(QLocale::system());

	tt.insert(tr("Ascent"), l.toString(ascent() * scale, 'f', 0)
	  + UNIT_SPACE + su);
	tt.insert(tr("Descent"), l.toString(descent() * scale, 'f', 0)
	  + UNIT_SPACE + su);
	tt.insert(tr("Maximum"), l.toString(max() * scale, 'f', 0)
	  + UNIT_SPACE + su);
	tt.insert(tr("Minimum"), l.toString(min() * scale, 'f', 0)
	  + UNIT_SPACE + su);

	return tt.toString();
}

void ElevationGraphItem::setUnits(Units units)
{
	setToolTip(toolTip(units));
}
