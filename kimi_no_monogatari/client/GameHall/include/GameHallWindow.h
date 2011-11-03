#ifndef _GAME_HALL_WINDOW_H_
#define _GAME_HALL_WINDOW_H_

#include <QMainWindow>

class QAction;
class QMenu;
class QPlainTextEdit;

class GameHallWindow : public QMainWindow
{
public:
	GameHallWindow();

	void setDisplayWindow(QWidget* window);

protected:
	virtual void resizeEvent(QResizeEvent * event);

private:
	QWidget* m_centralWidget;
};

#endif /* _GAME_HALL_WINDOW_H_ */
