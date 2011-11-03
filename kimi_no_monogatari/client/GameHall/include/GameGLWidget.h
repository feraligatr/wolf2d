#ifndef _GAME_GL_WIDGET_H_
#define _GAME_GL_WIDGET_H_

#include <QWidget>
#include <QGLWidget>

#include "WidgetListener.h"

class GameGLWidget : public QGLWidget
{
public:
	GameGLWidget(WidgetListener* listener);
//	virtual void resizeEvent(QResizeEvent* evt);
	virtual void timerEvent(QTimerEvent* evt);
//	virtual void paintEvent(QPaintEvent* evt);

protected:
	virtual void initializeGL();
	virtual void resizeGL(int w, int h);
	virtual void paintGL();

private:
	WidgetListener* m_listener;
	// TODO: Are we need the int m_timerId; to stop it?
};

#endif /* _GAME_GL_WIDGET_H_ */
