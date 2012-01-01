#ifndef _GAME_GL_WIDGET_H_
#define _GAME_GL_WIDGET_H_

#include <QWidget>
#include <QGLWidget>

#include "WidgetListener.h"

#include "SimpleClient.h"

class GameGLWidget : public QGLWidget
{
	Q_OBJECT
public:
	GameGLWidget(WidgetListener* listener);

	void setClient(SimpleClient* client);

	virtual void mousePressEvent(QMouseEvent *);
	virtual void mouseReleaseEvent(QMouseEvent *);
	virtual void mouseDoubleClickEvent(QMouseEvent *);
	virtual void mouseMoveEvent(QMouseEvent *);
#ifndef QT_NO_WHEELEVENT
	virtual void wheelEvent(QWheelEvent *);
#endif
	virtual void keyPressEvent(QKeyEvent *);
	virtual void keyReleaseEvent(QKeyEvent *);

	void recreateFromOgreWindow(WId wid);

protected:
	virtual void initializeGL();
	virtual void resizeGL(int w, int h);
	virtual void paintGL();

private slots:
	void timeout_update();

private:
	WidgetListener* m_listener;
	SimpleClient* m_client;
};

#endif /* _GAME_GL_WIDGET_H_ */
