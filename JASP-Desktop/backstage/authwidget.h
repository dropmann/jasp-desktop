#ifndef AUTHWIDGET_H
#define AUTHWIDGET_H

#include <QWidget>

#include "common.h"

namespace Ui {
class AuthWidget;
}

class AuthWidget : public QWidget
{
	Q_OBJECT

public:
	explicit AuthWidget(QWidget *parent = 0);
	~AuthWidget();
	void clearPassword();

protected:
	bool eventFilter(QObject *object, QEvent *event) OVERRIDE;

private slots:
	void loginSelected();

signals:
	void loginRequested(QString username, QString password);

private:
	Ui::AuthWidget *ui;
};

#endif // AUTHWIDGET_H
