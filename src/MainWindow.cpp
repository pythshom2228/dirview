#include "MainWindow.h"
#include "FileSystemModel.h"

#include <QTreeView>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QDir>
#include <QSortFilterProxyModel>
#include <QWidget>
#include <QDebug>

MainWindow::MainWindow(const QString& title, size_t width, size_t height, QWidget *parent)
    : QMainWindow(parent)
{
    auto *central = new QWidget(this);
    auto *layout = new QVBoxLayout(central);

    m_filter = new QLineEdit(this);
    m_filter->setPlaceholderText("Фильтр файлов и каталогов...");

    m_tree = new QTreeView(this);

    m_model = new FileSystemModel(this);

    QString homePath = QDir::homePath();

    m_model->setRootPath(homePath);
 
    m_proxy = new QSortFilterProxyModel(this);

    m_proxy->setSourceModel(m_model);
    m_proxy->setRecursiveFilteringEnabled(true);
    m_proxy->setFilterCaseSensitivity(Qt::CaseInsensitive);

    connect(m_filter, &QLineEdit::textChanged, this, &MainWindow::onLineEditTextChanged);

    connect(m_tree, &QTreeView::clicked, this, &MainWindow::onTreeViewClicked);

    m_tree->setModel(m_proxy);

    QModelIndex root = m_model->index(homePath);

    m_tree->setRootIndex(m_proxy->mapFromSource(root));

    m_tree->setSortingEnabled(true);

    for (int i = 0; i < m_model->columnCount(); ++i) {
        m_tree->setColumnWidth(i, width / m_model->columnCount());        
    }

    layout->addWidget(m_filter);
    layout->addWidget(m_tree);

    setCentralWidget(central);

    resize(width, height);
    setWindowTitle(title);
}

void MainWindow::onLineEditTextChanged(const QString &text)
{
    QRegularExpression regex(QRegularExpression::escape(text));
    regex.setPatternOptions(QRegularExpression::CaseInsensitiveOption);
     
    m_proxy->setFilterRegularExpression(regex);

    QModelIndex sourceRoot = m_model->index(QDir::homePath());

    QModelIndex proxyRoot = m_proxy->mapFromSource(sourceRoot);

    if (proxyRoot.isValid()) 
        m_tree->setRootIndex(proxyRoot);
}

void MainWindow::onTreeViewClicked(const QModelIndex &proxyIndex) 
{
    QModelIndex sourceIndex = m_proxy->mapToSource(proxyIndex);

    if (sourceIndex.column() != FileSystemModel::SizeColumn)
        return;

    QModelIndex dirIndex = m_model->index(sourceIndex.row(), 0, sourceIndex.parent());

    if (!m_model->isDir(dirIndex))
        return;
    
    m_model->updateFolderSize(dirIndex);
}
