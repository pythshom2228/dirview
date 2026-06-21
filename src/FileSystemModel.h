#pragma once

#include <QFileSystemModel>
#include <QHash>

class FileSystemModel : public QFileSystemModel
{
Q_OBJECT

public:
    enum Columns
    {
        NameColumn = 0,
        SizeColumn,
        TypeColumn,
        DateColumn,
        ActionColumn
    };

public:
    explicit FileSystemModel(QObject *parent = nullptr);

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    void updateFolderSize(const QModelIndex &dirIndex);

private:
    int calculateFolderSize(const QString &path);

private:
    QHash<QString, int> m_folderSizes;
};