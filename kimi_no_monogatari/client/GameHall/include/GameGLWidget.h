#ifndef _GAME_GL_WIDGET_H_
#define _GAME_GL_WIDGET_H_

#include <QWidget>
#include <QGLWidget>

#include "WidgetListener.h"

class GameGLWidget : public QGLWidget
{
	Q_OBJECT
public:
	GameGLWidget(WidgetListener* listener);

protected:
	virtual void initializeGL();
	virtual void resizeGL(int w, int h);
	virtual void paintGL();

private slots:
	void timeout_update();

private:
	WidgetListener* m_listener;
};

#endif /* _GAME_GL_WIDGET_H_ */
