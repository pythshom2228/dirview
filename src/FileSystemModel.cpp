#include "FileSystemModel.h"

#include <QDirIterator>
#include <QLocale>

#include <cmath>

FileSystemModel::FileSystemModel(QObject *parent) : QFileSystemModel(parent) 
{
    setFilter(QDir::AllEntries | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System);
}

QVariant FileSystemModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::TextAlignmentRole) 
    {
        if(index.column() == SizeColumn || index.column() == DateColumn)
            return Qt::AlignCenter;
    }
    
    if (role == Qt::DisplayRole && index.column() == SizeColumn)
    {
        QModelIndex nameIndex = this->index(index.row(), NameColumn, index.parent());

        auto formatDataSize = [](int size) -> QString
        {
            return QLocale().formattedDataSize(size, 2, QLocale::DataSizeTraditionalFormat);
        };

        if (isDir(nameIndex))
        {
            QString path = filePath(nameIndex);
            if (m_folderSizes.contains(path))
            {
                int bytes = m_folderSizes[path];
                return formatDataSize(bytes);
            }

            return "[Обновить]";
        }
        return formatDataSize(fileInfo(index).size());
    }
    if (role == Qt::DisplayRole && index.column() == TypeColumn)
    {
        if (isDir(index))
            return "Каталог";
        
        return fileInfo(index).suffix() + " файл";
    }
    
    return QFileSystemModel::data(index, role);
}

QVariant FileSystemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
    {
        switch(section)
        {
        case NameColumn:
            return "Имя";
            break;
        case SizeColumn:
            return "Размер";
            break;
        case TypeColumn:
            return "Тип";
            break;
        case DateColumn:
            return "Дата изменения";
            break;
        }
    }
    return QFileSystemModel::headerData(section, orientation, role);
}

void FileSystemModel::updateFolderSize(const QModelIndex &dirIndex)
{
    QString path = filePath(dirIndex);

    int size = calculateFolderSize(path);

    m_folderSizes[path] = size;

    QModelIndex sizeIndex = index(dirIndex.row(), SizeColumn, dirIndex.parent());

    emit dataChanged(sizeIndex, sizeIndex);
}

int FileSystemModel::calculateFolderSize(const QString &path)
{
    int size = 0;

    QDirIterator it(path, QDir::Files, QDirIterator::Subdirectories);

    while (it.hasNext())
    {
        QFileInfo info(it.next());
        size += info.size();
    }

    return size;
}