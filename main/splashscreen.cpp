#include "main/splashscreen.h"
#include "ui_splashscreen.h"
#include <QtSvg/QtSvg>
#include <QtCore/QTimer>
#include <QKeyEvent>
#include <assert.h>

using namespace Main;
using namespace Qt;

SplashScreen::SplashScreen() :
	m_ui(new Ui::SplashScreen()),
	m_closeTimer(new QTimer()),
	m_backgroundImage(0),
	m_backgroundPalette(0)
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
	delete m_backgroundPalette;
	m_backgroundPalette = 0;
	delete m_backgroundImage;
	m_backgroundImage = 0;
}

void SplashScreen::setBackgroundImage()
{
	assert(m_backgroundImage == 0);
	assert(m_backgroundPalette == 0);

	QSvgRenderer renderer(QString("resources/graphics/background.svg"));
	QImage image(width(), height(), QImage::Format_ARGB32);
	image.fill(Qt::white);
	QPainter painter(&image);
	renderer.render(&painter);
	m_backgroundImage = new QPixmap(QPixmap::fromImage(image));
	m_backgroundPalette = new QPalette();
	m_backgroundPalette->setBrush(QPalette::Background,*(new QBrush(*(m_backgroundImage))));
	setPalette(*m_backgroundPalette);
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
	m_closeTimer->stop();
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
