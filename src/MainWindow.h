#pragma once

#include <QMainWindow>

class FileSystemModel;
class QSortFilterProxyModel;
class QTreeView;
class QLineEdit;

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    MainWindow(
        const QString& title,
        size_t width,
        size_t height,
        QWidget *parent = nullptr
    );

private slots:
    void onLineEditTextChanged(const QString &text);
    
    void onTreeViewClicked(const QModelIndex &proxyIndex);

private:
    FileSystemModel *m_model;
    QSortFilterProxyModel *m_proxy;
    QTreeView *m_tree;
    QLineEdit *m_filter;
};