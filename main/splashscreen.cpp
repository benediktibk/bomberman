#include "main/splashscreen.h"
#include "ui_splashscreen.h"
#include <QtSvg/QtSvg>
#include <QtCore/QTimer>
#include <QKeyEvent>

using namespace Main;
using namespace Qt;

SplashScreen::SplashScreen() :
	m_ui(new Ui::SplashScreen()),
	m_closeTimer(new QTimer())
{
	m_ui->setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint);
	moveToCenterOfScreen();
	setBackgroundImage();
	setLabelColor();
	connect(m_closeTimer, SIGNAL(timeout()), this, SLOT(timeout()));
	m_closeTimer->start(5000);
}

SplashScreen::~SplashScreen()
{
	delete m_ui;
	m_ui = 0;
	delete m_closeTimer;
	m_closeTimer = 0;
}

void SplashScreen::setBackgroundImage()
{
	QSvgRenderer renderer(QString("resources/graphics/background.svg"));
	QImage image(width(), height(), QImage::Format_ARGB32);
	image.fill(Qt::white);
	QPainter painter(&image);
	renderer.render(&painter);
	QPixmap *pixmap = new QPixmap(QPixmap::fromImage(image));
	QPalette* palette = new QPalette();
	palette->setBrush(QPalette::Background,*(new QBrush(*(pixmap))));
	setPalette(*palette);
}

void SplashScreen::moveToCenterOfScreen()
{
	QDesktopWidget* desktop = QApplication::desktop();
	int screenWidth = desktop->width();
	int screenHeight = desktop->height();
	int ownWidth = width();
	int ownHeight = height();
	int x = screenWidth/2 - ownWidth/2;
	int y = screenHeight/2 - ownHeight/2;
	move(x, y);
}

void SplashScreen::setLabelColor()
{
	QLabel *label = m_ui->label;
	QPalette palette = label->palette();
	palette.setColor(label->backgroundRole(), Qt::red);
	palette.setColor(label->foregroundRole(), Qt::red);
	label->setPalette(palette);
}

void SplashScreen::timeout()
{
	hide();
	emit closed();
}

void SplashScreen::keyPressEvent(QKeyEvent *event)
{
	switch (event->key())
	{
	case Key_Space:
		timeout();
		break;
	default:
		QMainWindow::keyPressEvent(event);
		break;
	}
}
