/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Qt Software Information (qt-info@nokia.com)
**
** This file is part of the demonstration applications of the Qt Toolkit.
**
** No Commercial Usage
** This file contains pre-release code and may not be distributed.
** You may use this file in accordance with the terms and conditions
** contained in the either Technology Preview License Agreement or the
** Beta Release License Agreement.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License versions 2.0 or 3.0 as published by the Free
** Software Foundation and appearing in the file LICENSE.GPL included in
** the packaging of this file.  Please review the following information
** to ensure GNU General Public Licensing requirements will be met:
** http://www.fsf.org/licensing/licenses/info/GPLv2.html and
** http://www.gnu.org/copyleft/gpl.html.  In addition, as a special
** exception, Nokia gives you certain additional rights. These rights
** are described in the Nokia Qt GPL Exception version 1.3, included in
** the file GPL_EXCEPTION.txt in this package.
**
** Qt for Windows(R) Licensees
** As a special exception, Nokia, as the sole copyright holder for Qt
** Designer, grants users of the Qt/Eclipse Integration plug-in the
** right for the Qt/Eclipse Integration to link to functionality
** provided by Qt Designer and its related libraries.
**
** If you are unsure which license is appropriate for your use, please
** contact the sales department at qt-sales@nokia.com.
**
****************************************************************************/

#ifndef WEBVIEW_H
#define WEBVIEW_H

#include <QtWebKit/QWebView>

QT_BEGIN_NAMESPACE
class QAuthenticator;
class QMouseEvent;
class QNetworkProxy;
class QNetworkReply;
class QSslError;
QT_END_NAMESPACE

class BrowserMainWindow;
class WebPage : public QWebPage {
    Q_OBJECT

signals:
    void loadingUrl(const QUrl &url);

public:
    WebPage(QObject *parent = 0);
    BrowserMainWindow *mainWindow();

protected:
    bool acceptNavigationRequest(QWebFrame *frame, const QNetworkRequest &request, NavigationType type);
    QWebPage *createWindow(QWebPage::WebWindowType type);
#if !defined(QT_NO_UITOOLS)
    QObject *createPlugin(const QString &classId, const QUrl &url, const QStringList &paramNames, const QStringList &paramValues);
#endif

private slots:
    void handleUnsupportedContent(QNetworkReply *reply);

private:
    friend class WebView;

    // set the webview mousepressedevent
    Qt::KeyboardModifiers m_keyboardModifiers;
    Qt::MouseButtons m_pressedButtons;
    bool m_openInNewTab;
    QUrl m_loadingUrl;
};

class WebView : public QWebView {
    Q_OBJECT

public:
    WebView(QWidget *parent = 0);
    WebPage *webPage() const { return m_page; }

    void loadUrl(const QUrl &url);
    QUrl url() const;

    QString lastStatusBarText() const;
    inline int progress() const { return m_progress; }

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void contextMenuEvent(QContextMenuEvent *event);
    void wheelEvent(QWheelEvent *event);

private slots:
    void setProgress(int progress);
    void loadFinished();
    void setStatusBarText(const QString &string);
    void downloadRequested(const QNetworkRequest &request);
    void openLinkInNewTab();

private:
    QString m_statusBarText;
    QUrl m_initialUrl;
    int m_progress;
    WebPage *m_page;
};

#endif
